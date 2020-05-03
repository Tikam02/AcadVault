a=10;
w=2*pi*10;
fs=1000;
ts=1/fs;
t=[0:ts:0.3-ts];
y=zeros(1000,300);
for i=1:1000
    theta=rand()*2*pi;
    y(i,:)=a*cos(w*t + theta);
end

sum1 = mean(y(:,5))
sum2 = mean(y(:,1))
z=zeros(300,1);
for i=1:300
    z(i)=mean(y(:,1).*y(:,i));
end
figure(1)
plot(t,z);
x=fft(z);
f=linspace(-fs/2,fs/2-(fs/length(t)),length(t));
figure(2)
stem(f,fftshift(abs(x)));

