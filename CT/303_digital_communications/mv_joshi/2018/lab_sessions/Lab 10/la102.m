Tb=1;
Ts=10^-3;
fc=1000;
p=zeros(1,10000);
t=0:Ts:10*Tb-Ts;
c=cos(2*pi*2*t);
figure(1);
plot(c);
title('carrier signal');

%generating pulse
for i=1:1000:10000
    temp=rand();
        if(temp<=0.5)
            p(i:i+999)=-1;
        else
            p(i:i+999)=1;
        end
end

figure(2);
plot(p);
title('generated pulse');

ask=(p).*(c);
figure(3);
plot(ask);
title('phase shift keyd signal');

%demodulator
y=ask.*c;
figure(4);
plot(y);
title('demodulated signal');

%detector
for i=1:1000:10000
    sum=0;
    for j=i:i+999
        sum=sum+y(j);
    end
    if(sum>0)
        p(i)=1;
    else
       p(i)=-1; 
    end
    for j=i:i+999
        p(j)=p(i);
    end
end
figure();
plot(p);
title('detected signal');