Tb=1;
Ts=10^-3;
p=zeros(1,10000);
fsk=zeros(1,10000);
t=0:Ts:10*Tb-Ts;
c1=cos(2*pi*10*t);
c2=cos(2*pi*1*t);
figure();
plot(c1);
figure();
plot(c2);
for i=1:1000:10000
    temp=rand();
    for j=i:i+999
        if(temp<=0.5)
            p(j)=-1;
            fsk(j)=p(j).*c2(j);
        else
            p(j)=1;
            fsk(j)=p(j).*c1(j);
        end;
    end;
end;
figure();
plot(p);

figure();
plot(fsk);

y1=fsk.*c1;
y2=fsk.*c2;
figure();
plot(y1);
figure();
plot(y2);
ans=zeros(1,10000);
for i=1:1000:10000
    sum1=0;
    sum2=0;
    for j=i:i+999
        sum1=sum1+y1(j);
    end;
    for j=i:i+999
        sum2=sum2+y2(j);
    end;
    if(sum1-sum2)>0
        for k=i:i+999
            ans(k)=1;
        end;
    else
        for k=i:i+999
            ans(k)=-1;
        end;
    end;
end;
figure();
plot(ans);