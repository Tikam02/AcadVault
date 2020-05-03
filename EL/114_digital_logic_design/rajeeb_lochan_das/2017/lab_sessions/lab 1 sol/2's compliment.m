
clc;
clear all;
a=input('ENTER BINARY VALUE');
l=length(a);
b=0;
for index=l:-1:1
    if a(index)==1
        for b=(index-1):-1:1
            if a(b)==0
                a(b)=1;
            else
                a(b)=0;
            end 
        end
        break;
    end
end
for index=1:+1:l
disp(a(index));
end

