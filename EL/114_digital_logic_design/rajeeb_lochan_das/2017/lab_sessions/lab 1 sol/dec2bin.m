clc;
clear all;
e=input('ENTER DECIMAL NUMBER');
ans=0;
a=1;
b=0;
c=0;
while e>0
    b= mod(e,2);
    ans=ans+b*a;
    a=a*10;
    e=floor(e/2);
end
disp(ans);