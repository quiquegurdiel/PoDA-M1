%% Load audio
cd('C:\Users\GUR\Documents\REAPER Media\lalaralá')
[y,Fs] = audioread('lalaralá2.mp3');


cd('C:\Users\GUR\Documents\Sound recordings')

name='lalarala';
%% Average the channels
y=mean(y,2);

%% Average mean filtering up to video frequency
target=60;      %<-------------------hz, greater than standard video
[z1,z2] = envelope(y,Fs/target,'peak');

z=max(z1,-z2);
z=max(z,0);

%% Reduce the dimensionality
yp=1:length(y);
zp=1:Fs/target:length(y);
z = interp1(yp,z,zp);

%% Normalize
z=z/max(z);

%% Rescale
maxNoise=50;    %<-------------------
db=max(10*log10(z*maxNoise),0);

%% Convert to positions
nPos=20;        %<-------------------
steps=linspace(0,10*log10(maxNoise),nPos);
pos=zeros(size(db));

for i=1:nPos
   aux=find(db-steps(i)-steps(1)/2<=0&pos==0);
   pos(aux)=i;
end

%% Create animation
frames={};
resx=150;
resy=150;

outputVideo = VideoWriter([name num2str(nPos) num2str(maxNoise) '.avi']);
outputVideo.FrameRate = 60;
open(outputVideo);

for k = 1:length(pos) 
   aux=uint8(ones(resx ,resy,3)*pos(k)*255/nPos);
   frames{k}=aux;
   
   writeVideo(outputVideo,aux)
end

close(outputVideo)

%% Create animation with lightness compression
frames={};

outputVideo = VideoWriter([name 'COMP' num2str(nPos) num2str(maxNoise) '.avi']);
outputVideo.FrameRate = 60;
open(outputVideo);

%Assume L*a*b* scale

for k = 1:length(pos) 
   aux=zeros(resx ,resy,3);
   aux(:,:,1)=ones(resx,resy)*pos(k)*100/nPos;
   frames{k}=min(lab2rgb(aux),1);
   
   writeVideo(outputVideo,frames{k})
end

close(outputVideo)