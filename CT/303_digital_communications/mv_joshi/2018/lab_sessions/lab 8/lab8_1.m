clc;
clear all;
a=0.01;
tb=0.000001;
ts=0.000000001;
eta=0.000000001;
c=1.26;

%random pulses
for i=1:1000
   x = rand();
   if x > 0.5
      p(i,1:1000) = a; 
   else
       p(i,1:1000) = (-1 * a ); 
   end
end

%pulse
np = p;
%noise power
sigmasqr=(eta*c)/(4*tb);
%adding noise to pulse
for i=1:1000
     xx = sqrt(sigmasqr)*randn(1);
     np(i,:) = np(i,:) + xx ;
end
%convolving with response of RC filter
t = [0:ts:5*tb-ts];
h= (c/tb)*exp((-1) * (t) * c/tb);
for i=1:1000
    w(i,:) = conv(np(i,:),h);
end

%decision making
for i=1:1000
    if w(i,1000)>0
        po(i)=a;
    else
        po(i)=(-1) * a;
    end
end

%error calculation
count=0;
for i=1:1000
    if ~(p(i,1000) == po(i))
        count=count+1;
    end
end

%reshaping pulse into a single line
[m,n] = size(w);
final=reshape(w.',1,m*n);

%display()
ber=count/1000;
display(ber);
plot(final);
%axis([0 2*10^(6) -6*10^(7) 6*10^(7)]);