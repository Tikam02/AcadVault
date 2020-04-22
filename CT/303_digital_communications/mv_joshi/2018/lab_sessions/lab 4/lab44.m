[y,f]=wavread('a.wav');
fs1=16000;
fs2=800;
f=4000;
n=4;
y1=zeros(fs);
for i=1:fs
    if mod(y(i),n)==0 
        y1(i)=y(i);
    end
end
sound(y1,fs);