clc;
close all;
clear all;
h=[1 0 1 1 1 0 0; 0 1 0 1 1 1 0;0 0 1 0 1 1 1];%here h is key which is provided to us;
c1=[3 1 1 0 3 0 3];%is the signal comming from BEC(Binary Erase  channel) here 3 indicates the bit which is erased here you can enter any number else 0&1 to show error.
r=size(h,1);%r is the number of rows in h matrix
c=size(h,2);%c is the number of rows in h matrix
for i=1:r %here the each row will be visited r times as if there are 2 error in 1 row then we need to visit it again 
    for j=1:r %here each row of h is accessed
        count=0; %this counter is to calculate the number of 1's occuring in that particular row after we multiply that particular row of matrix h with c1
        count1=0; %this counter indicated how many error has occured in that message after we multiply with respected row of h;
        index=0; %if the count1==1 then only we use this index means we change the number occuring at index position
        for k=1:c % here each element of jth row of h is accesed
            if(h(j,k)==1) %here if h at that particular position is one then only we need to see the code of that inded for parity else if it is 0 then that index code is not needed for that number of parity check
                if(c1(k)==1) %here it counts if c is also 1 which will we useful to check the parity
                    count=count+1;
                elseif(c1(k)==0) 
                    count=count+0;
                else 
                    count1=count1+1;%here it counts the total number of errors occured in that particular parity check
                    index = k;% it stores the index at which the error has occured it will be useful to correct the code
                end
            end
        end
        if(count1==1)%here it checks that if only one error has occured in that parity than than it will correct that error at place which we calculated in index and overwrites the code and correct the errors
            c1(index)=mod(count,2);
        end
    end
end
%there are some distinct cases at which this error cannot be corrected for
% 4 and 5 bit error but its max capacity is to correct 5 bit error.