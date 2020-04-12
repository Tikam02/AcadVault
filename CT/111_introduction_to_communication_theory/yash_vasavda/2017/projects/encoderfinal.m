clc;
close all;
clear all;
%this code is to generate h for product code of different message bits
%eg(4,9),(9,16),(16,25);
m=9;%message bits
ib=[1 0 1 1 1 0 1 0 0];%place the info bits here which yoy want to send to reciver.
r=sqrt(m)+1;
h=zeros(r*r-(m),r*r);
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
conter=1;
c1sum=0;
tem=r+1;
tem=tem*tem;
for i=1:r
    c1sum=0;
    for j=1:tem
        k7=(i-1)*(r+1);
        k8=(i)*(r+1);
        if(j>k7 && j<k8)
           k2=j;
           c1(k2)=ib(conter);
           c1sum=c1sum+ib(conter);
           conter=conter+1;
        elseif(j==k8)
            c1(k8)=mod(c1sum,2);
        end
        disp(c1);
    end
end
for i=r+1:r+r+1
    c1sum=0;
    for j=1:(r*(r+1))+(i-r)
        if(j==(r*(r+1))+(i-r))
            c1(j)=mod(c1sum,2);
        elseif(h(i,j)==1)
            c1sum=c1sum+c1(j);
        end
    end
end
disp(c1);

