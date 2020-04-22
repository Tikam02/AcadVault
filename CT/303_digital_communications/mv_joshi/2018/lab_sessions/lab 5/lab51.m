n = [1,2,3,4,5,6,7,8,9,10];
fs = 24000;
Ts = 1/fs;
f = 3000;
T = 1/f;
t = 0:Ts:T;
sig = cos(2*pi*t*f);
plot(sig);

answers = n;
figure();
stem(t,sig);
for j = 1:length(n)
    levels = 2^n(j);
    a = linspace(-1,1,levels);
    signal=sig;
    tempsig = signal;
    errorsig = signal;
    for i = 1:length(signal)
 
        min = abs(signal(i) - a(1));
        if signal(i) < 0
            errorsig(i) = -min;
        else
            errorsig(i) = min;
        end
        tempsig(i) = a(1);
        for k = 1:levels
            if abs(signal(i) - a(k)) < min
                min = abs(signal(i) - a(k));
                if signal(i) < 0
                    errorsig(i) = -min;
                else
                    errorsig(i) = min;
                end
                tempsig(i) = a(k);
            end
        end
    end
    %figure();
    %stem(t,tempsig)
    %figure();
    %stem(t,errorsig)
    sum_signal = 0;
    for i = 1 : length(errorsig)
        sum_signal = sum_signal + (signal(i)*signal(i));
    end
    sum_error = 0;
    for i = 1 : length(errorsig)
        sum_error = sum_error + (errorsig(i) * errorsig(i));
    end
    snr = sum_signal/sum_error;
    db = 10*log10(snr);
    answers(j) = db;
end
figure()
plot(n,answers)

