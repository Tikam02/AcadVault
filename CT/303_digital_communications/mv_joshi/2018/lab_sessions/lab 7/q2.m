close all;
clear all;

n = 10000;
Ap = 1;
meanval = 0;
varianceval = 1;
threshold = 0;
Pm1 = 0.2;
Pm0 = 1 - Pm1;




er = [];
snr = [];

varianceval = 3:(-0.05):0.5;

a0 = (varianceval/(2*Ap))*log(Pm0/Pm1);

n1 = length(varianceval);

er = zeros(n1,1);
snr = zeros(n1,1);
estfn = zeros(n1,1);

for i = 1:n1
    bitarr = rand(n,1) > Pm0;
    insignal = 2*Ap*(bitarr) - Ap;
    noise = sqrt(varianceval(i))*randn(n,1) + meanval;
    outsig = insignal + noise;
    recvbitarr = outsig > a0(i);
    error = sum(recvbitarr ~= bitarr)/n;
    er(i) = error;
    snr(i) = Ap^2/varianceval(i);
    
    estfn(i) = Pm0*qfunc((a0(i) + Ap)/sqrt(varianceval(i)))  + Pm1*qfunc((Ap - a0(i))/sqrt(varianceval(i)));
    
end

plot(snr,er,'k');
hold on;

plot(snr,estfn);

xlabel('SNR \rightarrow');
ylabel('Probability of Error \rightarrow');

grid on;

figure();


plot(snr,abs(estfn - er),'k');
title('Difference between analytic and actual Error probabilities')
grid on;

