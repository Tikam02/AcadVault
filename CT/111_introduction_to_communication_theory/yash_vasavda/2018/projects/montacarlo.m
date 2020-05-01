clc;
close all;
clear all;
h=load('Hmatrix2.mat');
h=h.H;%here h is key which is provided to us;
signal=zeros(1,5000);%is the signal comming from BEC(Binary Erase  channel) here 3 indicates the bit which is erased here you can enter any number else 0&1 to show error.
r=size(h,1);%r is the number of rows in h matrix
c=size(h,2);%c is the number of rows in h matrix
efficiency=1:c;
for init=1:c
    efficiency(init)=0;
end
for ru=1:3000
    for ba=1:2
        rush=randperm(c,ru);
        c1=signal;
        for errr=1:ru
            c1(rush(errr))=3;
        end
        erasure=0;
        for i=1:c
            if(c1(i)~=0 && c1(i)~=1)%here it checks how many errors does it has
                erasure=erasure+1;
            end
        end
        e=0;
        while(erasure>0) %here it will ittrate till all errors have not corrected;
            if(e==erasure)%here it compares the error in previous ittretion with current ittretion if number of errors are same then it will terminate the ittretion and says that this code is not decodable
                success=0;% as all errors were not resolved so it will give success as zero
                break;
            end
            e=erasure;
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
                    erasure=erasure-1;
                end
                if(erasure==0)%now if all the errors are succesuflly resolved then it will terminate all ittreation and give the success value 1
                    success=1;
                    break;
                end
            end
        end
        if(success==1)
            efficiency(ru)=efficiency(ru)+1;
        end
    end
end
indk=1:c;
stem(indk,efficiency)