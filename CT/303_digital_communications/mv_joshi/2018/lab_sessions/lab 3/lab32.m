arr=zeros(1,90000);
brr=zeros(1,90000);
a=zeros(1,9);
mat=zeros(1000,1000);
k=0;
A=zeros(1,2);
l=zeros(2000,2000);

a=randi(2,1,8);
    for i=1:8
       % display('hii');
        if a(1,i)==2
         a(1,i)=-1;
        end
        p=i*5; 
       arr(1,p)=a(1,i);
      
       for k=1:1000
           arr(1,i*5+k)=arr(1,i*5);
          % display(arr(1,i*5+k));
           
       end
       
       
    end
    
    a(1,9)=0;
    
    for  k=1:10
           arr(1,9*10+k)=a(1,9);
           
    end
       
   % plot(a);
 for i=1:1000
   
x=randi([1,80]);   
for j=1:1000

    d=randi([0,10]);
   % display(d);
   
    l(i,j)=d;
   for k=1:80
           brr(1,k+d)=arr(1,k);
           
   end
   
mat(j,i)=brr(1,x);        
    
end

 end
 
 
 sum1=mean(mat(:,1));
sum2=mean(mat(:,2));
display(sum1);
display(sum2);
z=zeros(1000,1);
for i=1:999
    z(i)=mean(mat(:,1).*mat(:,i+1));
end
 fs=1/5;
 x=fft(z);
f=linspace(-fs/2,fs/2-(fs/1000),1000);
plot(f,fftshift(abs(x)));
h=fft(f);
g=linspace(-fs/2,fs/2-(fs/1000),1000);
plot(g,fftshift(abs(h)));