clc;
clear all;
e=input('enter the value');
l=length(e);
c=1;
len=l;
ans=0;
for index=l:-1:1
    ans=ans+(c*e(index));
    c=c*2;
end 
disp(ans);