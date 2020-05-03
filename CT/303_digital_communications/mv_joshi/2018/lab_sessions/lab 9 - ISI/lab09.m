clc;clear all;close all;
%generating random pulses
TB=[];
for i=1:1000:10000
    TB(i)=randi([0 1]);
    if TB(i) == 0
        TB(i:i+999)=-1;
    else
        TB(i:i+999)=1;
    end;
end;

%no ISI, no noise
t = 0:10^(-9):10*(10^(-6))-(10^(-9));
figure(1);
plot(t,TB);
title('no ISI and no Noise');

%impulse response of channel
r=1.8;
c=10^(-6);
rc=r*c;
irc=1/rc;
ht=irc*(exp((-1)*t*irc));
ans=conv(TB,ht);
figure();
plot(ans);

%no noise and ISI
ht = [];
rc = 0.000001/1.26;
irc = 1/rc;
ht = irc*(exp((-1)*t*irc));
sig = 10^(-9)*conv(TB,ht);
figure(2);
plot(sig);
title('No noise and ISI')

%noise and no ISI
n=[];
N=10^(-9);
si = sqrt(0.2);
n = normrnd(0,si,1,50);
sig1=[];
for i=1:10
    for j=((i-1)*1000)+1:1:(i*1000)
        sig1(j)=TB(j)+n(i);
    end;
end;
figure();
plot(t,sig1);
title('Noise and no ISI');

%noise and ISI
sig3 = 10^(-9)*conv(sig1,ht);
figure();
plot(sig3);
title('Noise and ISI');

%error calculation

%error for no noise and isi
err1=0;
for i=1:1:10000
    if sig(i)*TB(i)<0
        err1=err1+1;
    end;
end;
%error for noise
err2=0;
for i=1:1:10000
    if sig1(i)*TB(i)<0
        err2=err2+1;
    end;
end;
%error for ISI and noise
err3=0;
for i=1:1:10000
    if sig3(i)*TB(i)<0
        err3=err3+1;
    end;
end;

disp(err1/10000);
disp(err2/10000);
disp(err3/10000);
