fs=400;
n=0:1:7;
t=n/fs;

y=cos(2*pi*50*t);
stem(y);
a=zeros(1,8);
k=0;
i=0;

for k=0:7
    z=0;
    for i=0:7
        z=z+y(i+1)*exp(-1j*(2*pi*i*k)/8);
        
    end
    a(1,k+1)=z;
   
end
z=linspace(0,fs-fs/length(t),length(t));
    figure(2);
    stem(abs(a));