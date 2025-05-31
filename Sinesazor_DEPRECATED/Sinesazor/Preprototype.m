n=20; %number of divisions

x=linspace(0,1,n+1);
ang=acos(x.^3)/acos(0);

for i=1:length(ang)-1
   v(i)=ang(i)-ang(i+1);
end

if sum(v)~=1
   warning("v does not sum to 1") 
end

figure;
plot(x,x,'k')
hold on
plot(x,ang,'b')
grid on