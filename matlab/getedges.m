%nodes=csvread('D:/workspace_cpp/SocialNetWork/SocialNetworkDATA/Flixster-dataset/data/nodes.csv');
%edges=csvread('D:/workspace_cpp/SocialNetWork/SocialNetworkDATA/Flixster-dataset/data/edges.csv');
d=3;
%s=size(edges,1);
s=1049866;
edgeProperty = zeros(s,d);
for i=1:s
    for j=1:d
        edgeProperty(i,j)=unifrnd(0,1);
    end
    if(mod(i,100000)==0)
        i
    end
end

dlmwrite('edgeProperty.txt',edgeProperty,'\t')