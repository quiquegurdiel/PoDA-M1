%Calculate the control points based on equally spaced points
%Add intermediate points when v < 1
%Error function defined
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

%% Set the scale of v vs septs/second
v=[1,2,3,4];
stepSecond=[123.73, 247.16, 363.72, 493.69];

mdl1=fitlm(stepSecond,v,'y~x1-1');
mdl2=fitlm(v,stepSecond,'y~x1-1');

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
       auxV=predict(mdl2,3);
    else
       ti=(I(i+1)-I(i))*(dilateBy/Fs);
       auxN=red(I(i+1))-red(I(i));
       auxV=abs(auxN)/ti;
    end
    nList(i)=round(auxN);
    vList(i)=predict(mdl1,auxV);
    pList(i)=red(I(i));
end

figure()
subplot(2,1,1)
plot(nList,'or')
subplot(2,1,2)
plot(vList,'og')

%% Add intermediate points
Ierr=find(vList<1 & vList~=0);
iteration=1;

if ~isempty(Ierr)
    auxP=[];
    auxN=[];
    auxV=[];
    auxI=[];
    for i=1:length(I)
       if vList(i)>=1
          auxP=[auxP,pList(i)];
          auxN=[auxN,nList(i)];
          auxV=[auxV,vList(i)];
          auxI=[auxI,I(i)];
       else
          %Calculate position and waiting time of new point
          thisT=(I(i+1)-I(i))*(dilateBy/Fs);
          thisN=pList(i+1)-pList(i);
          thisSeconds=abs(thisN)/predict(mdl2,1);
          thisIndex=I(i)+round(thisSeconds*Fs/dilateBy);

          auxP=[auxP,pList(i),pList(i+1)];
          auxN=[auxN,nList(i),0];
          auxV=[auxV,1,0];
          auxI=[auxI,I(i),thisIndex];
       end
    end

    pList=auxP;
    nList=auxN;
    vList=auxV;
    I=auxI;
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

%% Define an error function
aprox=zeros(size(red));

for i=1:length(I)-1
    aprox(I(i):I(i+1))=linspace(pList(i),pList(i+1),I(i+1)-I(i)+1);
end

aprox(I(end):end)=linspace(pList(end),0,length(aprox)-I(end)+1);

err=aprox-red;

figure()
plot(t2,red)
hold on
plot(t2,aprox,'-r')
plot(t2,err,'-g')
grid on
title(['approximation error: ' sprintf('%.3d', sum(abs(err))/length(red) )])

%% Create a file with the set of actions
fileID=fopen('instructions.txt','w');
for i=1:length(I)
%     fprintf(fileID,'Serial.print("%d");\n',i);
%     fprintf(fileID,'Serial.print("\\n");\n');
    if vList(i)==0
        thisStop=round((I(i+1)-I(i))*(dilateBy/Fs)*1000);
        fprintf(fileID,'delay(%d);\n',thisStop);
    else
        fprintf(fileID,'small_stepper.setSpeed(%1.4f);\n',vList(i));
        fprintf(fileID,'small_stepper.step(%d);\n',nList(i));
    end
    %fprintf(fileID,'delay(10);\n'); 
end
