d=3;
n=10000;
k=5;

filaname = strcat('samples',int2str(k),'.txt');
data=zeros(n,d);
for i=1:n
    for j=1:d
        data(i,j)=unifrnd(0,1);
    end
end

Idx=kmeans(data,k-2);
Idn=zeros(k-2,1);

m=zeros(k,d);
for i=1:size(data,1)
    m(Idx(i),1)=m(Idx(i),1)+data(i,1);
    m(Idx(i),2)=m(Idx(i),2)+data(i,2);
    m(Idx(i),3)=m(Idx(i),3)+data(i,3);
    Idn(Idx(i))=Idn(Idx(i))+1;
end
for i=1:size(Idn)
    m(i,1)=m(i,1)/Idn(i);
    m(i,2)=m(i,2)/Idn(i);
    m(i,3)=m(i,3)/Idn(i);
end
m(k-1,1)=0;
m(k-1,2)=0;
m(k-1,3)=0;
m(k,1)=1;
m(k,2)=1;
m(k,3)=1;

dlmwrite(filaname,m,'\t')
%dlmwrite('sampledata10000.txt',data,'\t')

plot3(m(:,1),m(:,2),m(:,3),'.')
%scatter3(data(:,1),data(:,2),data(:,3),[],Idx,'.')
%plot3(m(:,1),m(:,2),m(:,3),'.')