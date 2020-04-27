clc;
clear all;
close all;
a=0;
b=1;
n=2;
x=zeros(n,n);
h=[1 1 1 0 0 0 0 0 0; 0 0 0 1 1 1 0 0 0; 1 0 0 1 0 0 1 0 0; 0 1 0 0 1 0 0 1 0; 0 0 1 0 0 1 0 0 1];
for i=1:2
    for j=1:2
        x(i,j)=randi([0,1]);
    end
end
y=zeros(3,3);
y(1,1)=x(1,1);
y(1,2)=x(1,2);
y(2,1)=x(2,1);
y(2,2)=x(2,2);
parity=[0 0 0 0 0];
for j=1:5
    i1=0;
    i2=0;
    for i=1:9
        if(i1==0 && h(j,i)==1)
            i1=i;
        elseif(i2==0 && h(j,i)==1)
            i2=i;
        end
    end
    x1=ceil(i1/3);
    y1=mod(i1,3);
    x2=ceil(i2/3);
    y2=mod(i2,3);
    if(y1==0 || y2==0)
        s=parity(1)+parity(2);
    else
        s=x(x1,y1)+x(x2,y2);
    end
    parity(j)=mod(s,2);
end
disp(x);
disp(parity);
y(1,3)=parity(1);
y(2,3)=parity(2);
y(3,1)=parity(3);
y(3,2)=parity(4);
y(3,3)=parity(5);
disp(y);