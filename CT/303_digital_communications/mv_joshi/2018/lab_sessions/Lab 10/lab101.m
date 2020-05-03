clear all;
Tb=1;
Ts=10^-3;
fc=1000;
p=zeros(1,10000);
t=0:Ts:10*Tb-Ts;
c=cos(2*pi*2*t);
figure();
plot(c);

% generate pulse
for i=1:1000:10000
    temp=rand();
    p(i:i+999)=temp>0.5;
end
figure(1);
plot(p);
title('generated pulse');
ask=(p).*(c);
figure(2);
plot(ask);
title('ask modulated signal');

%demodulator
y=ask.*c;
figure(3);
plot(y);
title('demodulated ask signal');

%detector
for i=1:1000:10000
    s=sum(y(i:i+999));
    if(s>0)
        p(i:i+999)=1;
    else
       p(i:i+999)=0; 
    end
end

figure(4);
plot(p);
title('detected signal');