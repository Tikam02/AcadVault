close all;
clear all;

n = 10000;
Ap = 1;
meanval = 0;
threshold = 0;
Pm1 = 0.5;

varianceval = 3:(-0.05):0.5;
n1 = length(varianceval);

er = zeros(n1,1);
snr = zeros(n1,1);

for i = 1:n1
    bitarr = rand(n,1) > Pm1;
    insignal = 2*Ap*(bitarr) - Ap;
    noise = sqrt(varianceval(i))*randn(n,1) + meanval;
    outsig = insignal + noise;
    recvbitarr = outsig > threshold;
    error = sum(recvbitarr ~= bitarr)/n;
    er(i) = error;
    snr(i) = Ap^2 / varianceval(i);
end

plot(snr,er,'k');
hold on;

plot(snr,qfunc(sqrt(snr)));
xlabel('SNR \rightarrow');
ylabel('Probability of Error \rightarrow');

grid on;

figure();


plot(snr,abs(qfunc(sqrt(snr)) - er),'k');
title('Difference between analytic and actual Error probabilities')
grid on;



