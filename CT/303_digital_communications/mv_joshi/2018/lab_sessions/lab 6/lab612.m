
fs = 16000;
ts = 1/fs;
n = 1:1:32;
k = n - 1;
t = 5*k*ts;
xn = sin(2*pi*50*t);
figure;
stem(n,xn);
lev = 32;
pcm = zeros(1,32);
%assigning values to levels - partition
for i=-16:15
    array(i+17) = ((2*i)+1)/32;
end
%applying pcm using partition values
pcm = quantiz(xn,array);
error=0;
sum=0;
for i=1:32  
        if(pcm(i) == 32)
            pcm(i) = 31;
        end
        qn(i) = array(pcm(i)+1);
        error=error+(xn(i)-qn(i))^2;
        sum=sum+xn(i)^2;
end
snr=10*log10(sum/error)