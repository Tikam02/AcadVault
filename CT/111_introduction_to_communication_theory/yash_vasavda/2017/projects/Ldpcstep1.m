clc;
close all;
clear all;
%This is the code for step-1 the 4-to-9 product code;
recived_signal=[3 1 3; 1 3 1; 3 1 1];
for j=1:3
    for i=1:5
        if(i==1)
            count=0;
            ecount=0;
            indexx=0;
            indexy=0;
            if(recived_signal(1,1)~=1 && recived_signal(1,1)~=0)
                ecount=ecount+1;
                indexx=1;
                indexy=1;
            end
            if(recived_signal(1,2)~=1 && recived_signal(1,2)~=0)
                ecount=ecount+1;
                indexx=1;
                indexy=2;
            end
            if(recived_signal(1,3)~=1 && recived_signal(1,3)~=0)
                ecount=ecount+1;
                indexx=1;
                indexy=3;
            end
            if(recived_signal(1,1)==1)
                count=count+1;
            end
            if(recived_signal(1,2)==1)
                count=count+1;
            end
            if(recived_signal(1,3)==1)
                count=count+1;
            end
            if(ecount==1)
                recived_signal(indexx,indexy)=mod(count,2);
            end
        elseif(i==2)
            count=0;
            ecount=0;
            index=0;
            if(recived_signal(2,1)~=1 && recived_signal(2,1)~=0)
                ecount=ecount+1;
                indexx=2;
                indexy=1;
            end
            if(recived_signal(2,2)~=1 && recived_signal(2,2)~=0)
                ecount=ecount+1;
                indexx=2;
                indexy=2;
            end
            if(recived_signal(2,3)~=1 && recived_signal(2,3)~=0)
                ecount=ecount+1;
                indexx=2;
                indexy=3;
            end
            if(recived_signal(2,1)==1)
                count=count+1;
            end
            if(recived_signal(2,2)==1)
                count=count+1;
            end
            if(recived_signal(2,3)==1)
                count=count+1;
            end
            if(ecount==1)
                recived_signal(indexx,indexy)=mod(count,2);
            end
        elseif(i==3)
            count=0;
            ecount=0;
            index=0;
            if(recived_signal(3,1)~=1 && recived_signal(3,1)~=0)
                ecount=ecount+1;
                indexx=3;
                indexy=1;
            end
            if(recived_signal(3,2)~=1 && recived_signal(3,2)~=0)
                ecount=ecount+1;
                indexx=3;
                indexy=2;
            end
            if(recived_signal(3,3)~=1 && recived_signal(3,3)~=0)
                ecount=ecount+1;
                indexx=3;
                indexy=3;
            end
            if(recived_signal(3,1)==1)
                count=count+1;
            end
            if(recived_signal(3,2)==1)
                count=count+1;
            end
            if(recived_signal(3,3)==1)
                count=count+1;
            end
            if(ecount==1)
                recived_signal(indexx,indexy)=mod(count,2);
            end
        elseif(i==4)
            count=0;
            ecount=0;
            index=0;
            if(recived_signal(1,1)~=1 && recived_signal(1,1)~=0)
                ecount=ecount+1;
                indexx=1;
                indexy=1;
            end
            if(recived_signal(2,1)~=1 && recived_signal(2,1)~=0)
                ecount=ecount+1;
                indexx=2;
                indexy=1;
            end
            if(recived_signal(3,1)~=1 && recived_signal(3,1)~=0)
                ecount=ecount+1;
                indexx=3;
                indexy=1;
            end
            if(recived_signal(1,1)==1)
                count=count+1;
            end
            if(recived_signal(2,1)==1)
                count=count+1;
            end
            if(recived_signal(3,1)==1)
                count=count+1;
            end
            if(ecount==1)
                recived_signal(indexx,indexy)=mod(count,2);
            end
        elseif(i==5)
            count=0;
            ecount=0;
            index=0;
            if(recived_signal(1,2)~=1 && recived_signal(1,2)~=0)
                ecount=ecount+1;
                indexx=1;
                indexy=2;
            end
            if(recived_signal(2,2)~=1 && recived_signal(2,2)~=0)
                ecount=ecount+1;
                indexx=2;
                indexy=2;
            end
            if(recived_signal(3,2)~=1 && recived_signal(3,2)~=0)
                ecount=ecount+1;
                indexx=3;
                indexy=2;
            end
            if(recived_signal(1,2)==1)
                count=count+1;
            end
            if(recived_signal(2,2)==1)
                count=count+1;
            end
            if(recived_signal(3,2)==1)
                count=count+1;
            end
            if(ecount==1)
                recived_signal(indexx,indexy)=mod(count,2);
            end
        end
    end
end
disp(recived_signal);