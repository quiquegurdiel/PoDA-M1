%Calculate the control points based on equally spaced points
%Add waiting times when minimum velocity create a problem
%% Load audio
cd('C:\Users\GUR\Documents\SINESAZOR\2.Sinesazor')
[y,Fs] = audioread('Poseidon.wav');

%% Average the channels
y=mean(y,2);

%% Time scale
t=zeros(size(y));
for i=1:length(t)
    t(i)=(i-1)/Fs;
end

%% Sample rate reduction
targetFs=2; %Target sample rate         <-
c=round(Fs/targetFs);

z=abs(y);
figure();
plot(t,z);
title('original')

red=ones(size(z));
for i=1:length(red)
   if i<=floor(c/2)
       red(i)=0;
   elseif length(red)-i<ceil(c/2)
       red(i)=0;
   else
       red(i)=sum(z(i-floor(c/2):i+ceil(c/2)))/(c+1);
   end
end

aux1=linspace(0,red(floor(c/2)+1),floor(c/2)+1);
aux2=linspace(red(end-ceil(c/2)),0,ceil(c/2)+1);

red(1:length(aux1))=aux1;
red(end-length(aux2)+1:end)=aux2;

%% Normalize to the number of steps in 90 degrees
m=max(red);
red=red/max(red)*1955;

figure();
plot(t,red);
title('reduced');

%% Rescale the steps scale to linearise lightness transmission

%Unactive

%% Set the scale of v with vs septs/second

v=[1,2,3,4];
stepSecond=[123.73, 247.16, 363.72, 493.69];

mdl=fitlm(stepSecond,v,'y~x1-1');

%% Discrete point selection

%Dilate time
dilateBy=8; %factor of video speed     <- 
t2=t*dilateBy;

%Use a fixed interval of time
interval=2; %sample selection           <-

aux1=round(interval/(dilateBy/Fs));
aux2=1:length(t2);
aux3=rem(aux2-1,aux1);

I=find(aux3==0);

figure()
plot(t2,red)
hold on
plot(t2(I),red(I),'or')
title('sample points')

%% Calculate a list of orders to the controler
nList=zeros(size(I));
vList=zeros(size(I));
pList=zeros(size(I));

for i=1:length(I)
    if i==length(I)
       auxN=-red(I(i));
       auxV=abs(auxN)/2;
    else
       ti=(I(i+1)-I(i))*(dilateBy/Fs);
       auxN=red(I(i+1))-red(I(i));
       auxV=abs(auxN)/ti;
    end
    nList(i)=round(auxN);
    vList(i)=predict(mdl,auxV);
    pList(i)=red(I(i));
end

figure()
subplot(2,1,1)
plot(nList,'or')
subplot(2,1,2)
plot(vList,'og')

%% Add waiting times
Ierr=find(vList<1 & vList~=0);
iteration=1;

while ~isempty(Ierr)
    display('Correcting positions')
    display(iteration)

    %Adjust positions
    for i=Ierr
        pList(i+1)=pList(i);
    end

    %Recalculate orders
    for i=1:length(I)
        if i==length(I)
           auxN=-red(I(i));
           auxV=abs(auxN)/2;
        else
           ti=(I(i+1)-I(i))*(dilateBy/Fs);
           auxN=pList(i+1)-pList(i);
           auxV=abs(auxN)/ti;
        end
        nList(i)=round(auxN);
        vList(i)=predict(mdl,auxV);
    end
    
    Ierr=find(vList<1 & vList~=0);
    iteration=iteration+1;
end
figure()
subplot(2,1,1)
plot(nList,'or')
subplot(2,1,2)
plot(vList,'og')

figure()
plot(t2,red)
hold on
plot(t2(I),pList,'or')
title('sample points corrected')

%% Create a file with the set of actions
fileID=fopen('instructions.txt','w');
for i=1:length(I)
    fprintf(fileID,'Serial.print("%d");\n',i);
    fprintf(fileID,'Serial.print("\\n");\n');
    if vList(i)==0
        fprintf(fileID,'delay(2000);\n');
    else
        fprintf(fileID,'small_stepper.setSpeed(%1.4f);\n',vList(i));
        fprintf(fileID,'small_stepper.step(%d);\n',nList(i));
    end
    %fprintf(fileID,'delay(10);\n'); 
end
