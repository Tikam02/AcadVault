clear all;

[x,f]=wavread('C:\Users\student\Desktop\speech_waveform_LAB4.wav');
fs = 16000;

n = f/fs;
l = length(x);
j = 1;
plot(x)
xmax= max(x);
xmin= min(x);
a = linspace(xmin,xmax,32);0.

error = x;
temp = x;
y = x;
mu = 255;
for i = 1:length(x)   
        min = abs(x(i) - a(1));
        error(i) = min;
        temp(i) = a(1);
        for k = 1:32
            if abs(x(i)-a(k)) < min
                min = abs(x(i)-a(k));
                error(i) = min;
                temp(i) = a(k);
            end
        end
end

error = x;
sum1 = 0;
for i = 1:length(x)
    error(i) = abs(x(i) - temp(i));
    sum1 = sum1 + error(i)^2;
end

figure();
stem(error);
sum1 = sum1/length(error);
rmse1 = sqrt(sum1)

for i = 1:length(x)
y(i) = sign(x(i))*((log(1 + mu * abs(x(i))/xmax)) / log(1 + mu));    
        min = abs(y(i) - a(1));
        error(i) = min;
        temp(i) = a(1);
        for k = 1:32
            if abs(y(i)-a(k)) < min
                min = abs(y(i)-a(k));
                error(i) = min;
                temp(i) = a(k);
            end
        end
end
    dd
inverse = temp;
for i = 1:length(y)
    inverse(i) = (sign(temp(i))/mu) * ((1 + mu)^abs(temp(i)) - 1);
end

error = x;
sum = 0;
for i = 1:length(x)
    error(i) = abs(x(i) - inverse(i));
    sum = sum + error(i)^2;
end

figure();
stem(error);

sum = sum/length(error);
rmse2 = sqrt(sum)
sound(inverse,fs);