# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
#imports and cwd
import numpy as np
from cv2 import cv2
import os
import matplotlib.pyplot as plt
import pickle
import scipy.interpolate as inter
import scipy.optimize as opt
import scipy.stats as sts
import pandas as pd
import math

os.chdir("\\\\DESKTOP-6VFOUOH\\Users\\GUR\\Code\\PoDA-M0\\Calibration")


# %%
#*************************************************************
#Position calibration
#*************************************************************


# %%
#Load video and get average frame color (RGB)
vidcap = cv2.VideoCapture('./1800BackAndForth.MOV')
success,image = vidcap.read()
count = 0
meanBGR=np.zeros([1,1,3],dtype='uint8')
aux=np.zeros([1,1,3],dtype='uint8')
while success :
    for i in range(3):
        aux[0,0,i]=np.mean(image[:,:,i].flatten())
    meanBGR=np.append(meanBGR,aux,1)
    success,image = vidcap.read()
    if cv2.waitKey(10) == 27:                     # exit if Escape is hit
        break
    count += 1
meanBGR=meanBGR[:,1:count+1,:]


# %%
#Show lightness component (La*b*)
meanLAB=cv2.cvtColor(meanBGR, cv2.COLOR_BGR2LAB)
measured=meanLAB[:,:,0].flatten()

plt.plot(measured)

#knowing the motor has moved 1800 steps back and forth at a constant speed
#and that the periodicity of the lightnes corresponds to a 180º movement
#we estimate 0.1713 as the angle to step ratio (MANUALLY - pen and paper)


# %%
#Get same measurement using a numerical optimization
startPoints=[48,380,707,1039,1369,1699,2029,2358]
endPoints=[373,702,1032,1360,1692,2019,2351,2679]
numberOfSteps=1800

def sinPower(vector,w=0.03,phi=0,p=1.5,a=125,z=125):
    out=np.linspace(0,len(vector)-1,len(vector))
    out=np.sin(w*out+phi)/2+0.5
    out=np.power(out,p)*a+z
    return out

def cost(x,measured):
    pred=sinPower(measured,x[0],x[1],x[2],x[3],x[4])
    return sum(np.power(measured-pred,2))

response=np.empty(0)
run=np.empty(0,dtype="int64")
ind=np.empty(0,dtype="int64")
l=np.zeros_like(startPoints,dtype='float')
w=np.zeros_like(startPoints,dtype='float')
phi=np.zeros_like(startPoints,dtype='float')
p=np.zeros_like(startPoints,dtype='float')
a=np.zeros_like(startPoints,dtype='float')
z=np.zeros_like(startPoints,dtype='float')
estimations=np.zeros_like(startPoints,dtype='float')

x0=[0.03,0.5,1,90,85]
bou=[(0.01,0.5),(0,2*np.pi),(0,5),(75,110),(75,100)]
for i in range(len(startPoints)):
    thisStart=startPoints[i]
    thisEnd=endPoints[i]
    thisMeasured=measured[thisStart:thisEnd+1]

    res=opt.minimize(
        cost,
        x0,
        args=(thisMeasured,),
        method='Nelder-Mead',
        tol=1e-6,
        bounds=bou
    )
    
    response=np.append(response,thisMeasured)
    run=np.append(run,np.ones_like(thisMeasured)*i)
    ind=np.append(ind,range(len(thisMeasured)))
    l[i]=len(thisMeasured)
    w[i]=res.x[0]
    phi[i]=res.x[1]
    p[i]=res.x[2]
    a[i]=res.x[3]
    z[i]=res.x[4]
    estimations[i]=w[i]*90/np.pi*l[i]/numberOfSteps

    plt.plot(thisMeasured)
    plt.plot(sinPower(thisMeasured,res.x[0],res.x[1],res.x[2],res.x[3],res.x[4]))
    plt.show()

#even though we are not able to get a good approximation to the exact shape
#the calculation of the frequency is fantastic


# %%
#define the step equivalent, seq
seq=np.mean(estimations) #step equivalent
err=np.std(estimations) #standard error aproximation (overestimated)
seq=round(seq,ndigits=abs( math.floor(math.log10(abs(err))) ))

print("step equivalent (º/step):")
print(seq)
print("error estimation:")
print(err)


# %%
#optimal variables
optimal=pd.DataFrame({
    'run': range(0,8),
    'l': l,
    'w': w,
    'phi': phi,
    'p': p,
    'a': a,
    'z': z
    })

optimal


# %%
#organise the data from all the runs with corresponding optimal parameters
myData=pd.DataFrame({
    'run': run,
    'ind': ind,
    'response': response
})

#create the full data frame
myData=myData.merge(optimal,on='run',how='left')
#create phase column
myData['phase']=myData.apply(lambda row: row.phi+row.w*row.ind,axis=1)
#adapt to negative amplitudes: sin(a)=-sin(a+pi)
myData.loc[myData.a<0, "phase"] = (myData['phase']+np.pi)
#phase module 2pi
myData['phase']=myData.apply(lambda row: row.phase%(2*np.pi),axis=1)
#create angle column,
#keep in mind phase is not radians, 2pi is the periodicity, in this case 180º
myData['angle']=myData.apply(lambda row: row.phase/(2*np.pi)*180,axis=1)

myData


# %%
#average the runs to obtain the position equivalent of lightness
maxAngle=300
count=100
position=np.linspace(0,maxAngle,count,endpoint=False)
value=np.zeros_like(position)
halfWindow=1.2

for i in range(len(position)):
    pos=position[i]
    thisData=myData.copy()
    thisData['angle']=thisData.apply(lambda row: (row.angle-pos)%180,axis=1)
    thisData=thisData.loc[(thisData['angle']>180-halfWindow)|(thisData['angle']<halfWindow)]
    value[i]=thisData['response'].mean()

value=value-np.min(value)
value=value/np.max(value)

plt.plot(position,value,marker='x',linestyle='')

#next vectors should not have consecutive numbers, if not increase halfWindow
print(np.where(value==np.max(value)))
print(np.where(value==np.min(value)))
#next value should be exactly 90º, if not modify maxAngle and count
print(np.abs(position[np.where(value==np.min(value))[0][0]]-position[np.where(value==np.max(value))[0][0]]))


# %%
#show the result
origin=np.where(value==np.max(value))[0][0]
end=np.where(value==np.min(value))[0][0]

decre=np.linspace(0,90,end-origin+1)/90
cresc=np.linspace(90,0,end-origin+1)/90
final=value[origin:(end+1)]

plt.plot(cresc*90,final,marker='x',linestyle='')
plt.plot(decre*90,final,marker='x',linestyle='')


# %%
#interpolate to a continuous function, signal to position
signal2cresc=inter.interp1d(final,cresc,kind='slinear')
signal2decre=inter.interp1d(final,decre,kind='slinear')

x=np.linspace(0,1,10000)
y1=signal2cresc(x)
y2=signal2decre(x)
plt.plot(x,y1)
plt.plot(x,y2)


# %%
#interpolate to a continuous function, position to signal
cresc2signal=inter.interp1d(cresc,final,kind='slinear')
decre2signal=inter.interp1d(decre,final,kind='slinear')

x=np.linspace(0,1,10000)
y1=cresc2signal(x)
y2=decre2signal(x)
plt.plot(x,y1)
plt.plot(x,y2)


# %%
#*************************************************************
#Speed calibration
#*************************************************************


# %%
#Load video and get average frame color (RGB)
vidcap = cv2.VideoCapture('./632IncreasingSpeed.MOV')
success,image = vidcap.read()
count = 0
meanBGR=np.zeros([1,1,3],dtype='uint8')
aux=np.zeros([1,1,3],dtype='uint8')
while success :
    for i in range(3):
        aux[0,0,i]=np.mean(image[:,:,i].flatten())
    meanBGR=np.append(meanBGR,aux,1)
    success,image = vidcap.read()
    if cv2.waitKey(10) == 27:                     # exit if Escape is hit
        break
    count += 1
meanBGR=meanBGR[:,1:count+1,:]


# %%
#Show lightness component (La*b*)
meanLAB=cv2.cvtColor(meanBGR, cv2.COLOR_BGR2LAB)
measured=meanLAB[:,:,0].flatten()

plt.plot(measured)

print("angular equivalent")
print(seq)
print("number of steps for 90º")
print(90/seq)

#the intention was to restrict themovement to 90º but there was a miscalculation of the number of steps
#anyway we can still use this data for a first fit of speed


# %%
#translate to angular position (using crescent) and time (using fps)
fps=vidcap.get(cv2.CAP_PROP_FPS)
time=np.linspace(1,len(measured)-1,len(measured),dtype=int)/25
#normalise response first
pos=signal2cresc((measured-np.min(measured))/np.max(measured))*90

plt.plot(time,pos)

#we can see quite nice straight lines in each of the movements, as expected from a constant speed


# %%
#separate manualy each range of constant speed input
startTimes=[7 ,26,32.5,39.5,43,  47.5,49.5, 53,54.4, 57,  58.3,60.5,61.5,63.3]
endTimes=  [14,30,35  ,42,  44.5,49,  50.75,54,55.3, 57.8,59,  61.1,62.25,63.9]

startInd=np.zeros_like(startTimes,dtype='int')
endInd=np.zeros_like(startTimes,dtype='int')
for i in range(len(startTimes)):
    aux=abs(time-startTimes[i])
    startInd[i]=aux.argmin()
    aux=abs(time-endTimes[i])
    endInd[i]=aux.argmin()

plt.plot(pos)
plt.plot(startInd,pos[startInd],marker='x',linestyle='',color="green")
plt.plot(endInd,pos[endInd],marker='x',linestyle='',color='red')


# %%
#fit a straight line for each speed input
inputs=np.array([1,-2,3,-4,5,-6,7,-8,9,-10,11,-12,13,-14])
speeds=np.zeros_like(inputs,dtype="float64")

fits=[]
for i in range(14):
    thisPos=pos[startInd[i]:endInd[i]]
    thisTime=time[startInd[i]:endInd[i]]
    fits.append(sts.linregress(thisTime,thisPos))
    speeds[i]=fits[i].slope

    plt.plot(thisTime, fits[i].intercept + fits[i].slope*thisTime)
    plt.plot(thisTime,thisPos,marker='x',linestyle='')
    plt.show()

#nice fits, there is some noise but we can't ask for much more


# %%
#define the input equivalent, ieq
def onlySlope(x,a):
    return x*a

out=opt.curve_fit(onlySlope,inputs,speeds)
ieq=out[0][0]
err=out[1][0][0] #variance of the fit
ieq=round(ieq,ndigits=abs(math.floor(math.log10(abs(err))))-1)

print("input equivalent (º/s/input):")
print(ieq)
print("error estimation:")
print(err)


# %%
#compare to a parabolic function with no intercept
def order2NoInterc(x,a,b):
    return np.power(x,2)*a+b*x

out2=opt.curve_fit(order2NoInterc,inputs,speeds)

aux=np.linspace(-14,14,1000)
plt.plot(aux,onlySlope(aux,out[0][0]))
plt.plot(aux,order2NoInterc(aux,out2[0][0],out2[0][1]),linestyle=':')
plt.plot(inputs,speeds,marker='x',linestyle='')

#it shows a tiny decrease on speed for large (absolut) input with respect to the linear fit
#it can be a real effect, or due to accelerations, or due to the manual selection of points, no clear
#we go with the linear fit, it seems precise enough


# %%
#*************************************************************
#Calibration File (.cal)
#*************************************************************


# %%
#save a calibration file
model='M0'
sourcePositionVideo='1800BackAndForth.MOV'
sourceSpeedVideo='632IncreasingSpeed.MOV'
cFile=open('M0.cal','wb')
pickle.dump([ieq,seq,signal2cresc,signal2decre,cresc2signal,decre2signal,model,sourcePositionVideo,sourceSpeedVideo],cFile)
cFile.close()

del(ieq,seq,signal2cresc,signal2decre,cresc2signal,decre2signal,model,sourcePositionVideo,sourceSpeedVideo)


# %%
#test calibration file opening
cFile = open('M0.cal', 'rb')
[ieq,seq,signal2cresc,signal2decre,cresc2signal,decre2signal,model,sourcePositionVideo,sourceSpeedVideo] = pickle.load(cFile)
cFile.close()

ieq


# %%



