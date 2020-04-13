clc;
close all;
clear all;
h=[1 1 1 0 0 0 0 0 0; 0 0 0 1 1 1 0 0 0; 1 0 0 1 0 0 1 0 0; 0 1 0 1 0 0 0 1 0; 0 0 1 0 0 1 0 0 1];%here h is key which is provided to us;
c1=[3 3 1 1 3 0 0 3 3];%is the signal comming from BEC(Binary Erase  channel) here 3 indicates the bit which is erased here you can enter any number else 0&1 to show error.
r=size(h,1);%r is the number of rows in h matrix
c=size(h,2);%c is the number of rows in h matrix
erasure=0;% counter for the total number of errors in code
for i=1:c
    if(c1(i)~=0 && c1(i)~=1)%here it checks how many errors does it has
        erasure=erasure+1;
    end
end
disp(erasure);%displays thetotal number of errors in the recived signal
e=0;
err(1)=erasure;
count0=1;
while(erasure>0) %here it will ittrate till all errors have not corrected;
    if(e==erasure)%here it compares the error in previous ittretion with current ittretion if number of errors are same then it will terminate the ittretion and says that this code is not decodable
        disp("This code cant be resolved as it as errors which cannot be corrected");
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
        count0=count0+1;
        err(count0)=erasure;
        disp(erasure);%it displays the number of remaining errors in the recived signal after each cycle
        if(erasure==0)%now if all the errors are succesuflly resolved then it will terminate all ittreation and give the success value 1
            success=1;
            break;
        end
    end
end
disp("The success of code is: ");
disp(success);%here it display that code was succesfully resolved or not if its valu turn out to be 1 than it is resolved succesfully and it 0 then it is not resolved.
in=0:(count0-1);
stem(in,err);