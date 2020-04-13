clc;
close all;
clear all;
h=[1 1 1 0 0 0 0 0 0; 0 0 0 1 1 1 0 0 0 ; 1 0 0 1 0 0 1 0 0; 0 1 0 0 1 0 0 1 0; 0 0 1 0 0 1 0 0 1];%here h is key which is provided to us;
c1=[1 1 1 0 1 1 1 1 0];%is the signal comming from BEC(Binary Erase  channel) here 3 indicates the bit which is erased here you can enter any number else 0&1 to show error.
r=size(h,1);%r is the number of rows in h matrix
c=size(h,2);%c is the number of rows in h matrix
sparse=[0 0 0 0 0];
for i=1:5 %here the each row will be visited r times as if there are 2 error in 1 row then we need to visit it again 
    for j=1:r %here each row of h is accessed
        count=0; %this counter is to calculate the number of 1's occuring in that particular row after we multiply that particular row of matrix h with c1
        for k=1:c % here each element of jth row of h is accesed
            if(h(j,k)==1) %here if h at that particular position is one then only we need to see the code of that inded for parity else if it is 0 then that index code is not needed for that number of parity check
                if(c1(k)==1) %here it counts if c is also 1 which will we useful to check the parity
                    count=count+1;
                end
            end
        end
        sparse(j)=mod(count,2);
    end
    sp1=0;
    sp2=0;
    sp3=r;
    flag=0;
    for j=1:r-1
        if(sparse(j)==1 && flag==0)
            sp1=j;
            flag=1;
        elseif(sparse(j)==1)
            sp2=j;
        end
    end
    if(sp1==1)
        for j=1:c
            if(h(sp1,j)==1 && h(sp2,j)==1)
                c1(j)=mod(c1(j)+1,2);
            end
        end
    end
    disp(c1);
    sparse=[0 0 0 0 0];
end
%there are some distinct cases at which this error cannot be corrected for
% 4 and 5 bit error but its max capacity is to correct 5 bit error.