p = zeros(1,10000);
for i=1:1000:10000
    p(i)= rand();
    if(p(i)<0.5)
        p(i:i+999) = -1;       
    else
        p(i:i+999) = 1;
    end;
end;
t = 0:10^-3:5 - 10^-3;
c1 = cos(2*pi*2*t);
c2 = sin(2*pi*2*t);
len1 = 1;
len2 = 1;
x1 = zeros(1,5000);
x2 = zeros(1,5000);
for j=0:9
    for i = 1000*j + 1:1000*(j+1)
        if(mod(j,2) == 0)
             x1(len1) = p(i)*c1(len1);
             len1 = len1 + 1;
        else
            x2(len2) = p(i)*c2(len2);
             len2 = len2 + 1;
        end;
    end;
end;
qpsk = zeros(1,5000);
for i=1:5000
    qpsk(i) = x1(i) + x2(i);
end;
figure(1);
plot(p);
figure(2);
plot(qpsk);

y1 = qpsk.*c1;
y2 = qpsk.*c2;
for j=0:4
    sum1 = 0;
    sum2 = 0;
for i=1000*j+1:1000*(j+1)
    sum1 = sum1 + y1(i);
    sum2 = sum2 + y2(i);
end;
if(sum1 >0)
    r1(1000*j+1:1000*(j+1)) = 1;
else
    r1 (1000*j+1:1000*(j+1)) = -1;
end;
    if(sum2 >0)
    r2(1000*j+1:1000*(j+1)) = 1;
    else
    r2 (1000*j+1:1000*(j+1)) = -1;
    end;
end;
j=0;
len1 = 0;
len2 = 0;
for i=0:9
    if(mod(i,2) == 0)
        r(1000*j +1 :1000*(j+1)) = r1(1000*len1 +1:1000*(len1+1));
        j = j+1;
        len1 = len1 + 1;
    else
        r(1000*j +1 :1000*(j+1)) = r2(1000*len2 +1:1000*(len2+1));
        j = j+1;
        len2 = len2 + 1;
    end;
end;
figure(3);
plot(r);