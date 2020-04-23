clc;
clear all;
decimal1=input('');
decimal2=input('');
b1=[0 0 0 0 0 0 0 0];
b2=[0 0 0 0 0 0 0 0];
carry=0;
t=0;
i=0;
check1=0;
check2=0;
if decimal1<0
   decimal1=decimal1*(-1);
   check1=1;
end

if decimal2<0
   decimal2=decimal2*(-1);
   check2=1;
end
for i=8:-1:1
    b1(i)=mod(decimal1,2);
    decimal1=floor(decimal1/2);
end

for i=8:-1:1
    b2(i)=mod(decimal2,2);
    decimal2=floor(decimal2/2);
end
if check1==1
    for index=8:-1:1
    if b1(index)==1
        for b=(index-1):-1:1
            if b1(b)==0
                b1(b)=1;
            else
                b1(b)=0;
            end 
        end
        break;
    end
end
end

if check2==1
    for index=8:-1:1
    if b2(index)==1
        for b=(index-1):-1:1
            if b2(b)==0
                b2(b)=1;
            else
                b2(b)=0;
            end 
        end
        break;
    end
end
end
ans=[0 0 0 0 0 0 0 0];
for i=8:-1:1
    t=carry+b1(i)+b2(i);
    if t==0
        ans(i)=0;
        carry=0;
    end
    if t==1
        carry=0;
        ans(i)=1;
    end
    if t==2
        carry=1;
        ans(i)=0;
    end
    if t==3
        carry=1;
        ans(i)=1;
    end
end
ans2=0;
multi=1;
for i=8:-1:1
    ans2=ans2+ans(i)*multi;
    multi=multi*2;
end
disp(ans);
if ans2>127
    ans2=ans2-256;
end
disp(ans2);