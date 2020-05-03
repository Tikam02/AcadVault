clc;
clear all;
e=input('enter octal value');
l=length(e);
c=1;
len=l;
ans=0;
for index=l:-1:1
    ans=ans+(c*e(index));
    c=c*8;
end 
b=0;
while ans>0
    b= mod(ans,16);
     switch b
        case 10
            disp('A');
        case 11
            disp('B');
        case 12
            disp('C');
        case 13
            disp('D');
        case 14
            disp('E');
        case 15
            disp('F');
        otherwise
            disp(b);
    end
    
    ans=floor(ans/16);
end