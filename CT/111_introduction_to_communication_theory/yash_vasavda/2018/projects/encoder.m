clc;
close all;
clear all;
%this code is to generate h for product code of different message bits
%eg(4,9),(9,16),(16,25);
m=9;%message bits
r=sqrt(m)+1;
h=zeros(r*r-(m++1),r*r);
r=r-1;
for i=1:r
    for j=1:r+1
        k=i-1;
        k=(r+1)*k+j;
        h(i,k)=1;
    end
end
for i=r+1:r+r+1
    for j=1:r+1
        k=j-1;
        k=(r+1)*k+i-r;
        h(i,k)=1;
    end
end
disp(h);