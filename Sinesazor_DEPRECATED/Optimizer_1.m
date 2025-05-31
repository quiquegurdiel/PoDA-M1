function [ out ] = Optimizer_1( red, dilateBy, Fs, mdl, I )
%Optimizer_2 Direct application of Proto2 estrategy in optimization 

%% Sort indices
I=sort(I);

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

%% Add waiting times
Ierr=find(vList<1 & vList~=0);
iteration=1;

while ~isempty(Ierr)
%     display('Correcting positions')
%     display(iteration)

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

%% Define an error function
aprox=zeros(size(red));

for i=1:length(I)-1
    aprox(I(i):I(i+1))=linspace(pList(i),pList(i+1),I(i+1)-I(i)+1);
end

aprox(I(end):end)=linspace(pList(end),0,length(aprox)-I(end)+1);

err=aprox-red;

out=sum(abs(err))/length(red);

end

