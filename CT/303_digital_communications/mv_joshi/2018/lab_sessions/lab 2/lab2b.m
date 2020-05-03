fs=1000;
ts=1/fs;
t=[0:ts:0.3-ts];
for i=1:10000
    y(i,:)=randn(1,300);
end
figure(1)
hist(y);
for i =1:300
    m(i,1) = mean(y(:,1).*y(:,i));
end

k=1:1:300;
figure(2)
plot(k,m);
f=linspace(-fs/2,fs/2-(fs/length(t)),length(t));
psd=fft(m);
figure(3);
stem(f,fftshift(abs(psd)));