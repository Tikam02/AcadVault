clc;
clear all;
close all;
u=[1 1 0 1 1];
puterrindex=[12];
lengkh=length(puterrindex);
ff1=0;
ff2=0;
len=length(u);
u(len+1)=0;
u(len+2)=0;
for i=1:len+2
    con1 = mod(u(i)+ff1,2);
    con1 = mod(con1+ff2,2);
    con2 = mod(u(i)+ff2,2);
    ff2=ff1;
    ff1=u(i);
    ed(2*(i-1)+1)=con2;
    ed(2*(i-1)+2)=con1;
end
disp(ed);
for i=1:lengkh
    ed(puterrindex(i))=mod(ed(puterrindex(i))+1,2);
end
disp(ed);
re=ed;
key=[0 1 1 0; 0 0 1 1; 1 0 0 1; 1 1 0 0];
pat=zeros(4,len+2,2);
for i=1:4
    for j=1:len+2
        pat(i,j,1)=9999;
    end
end
for i=1:len+2
    if(i==1)
        pat(4,1,1)=mod(re(2*(i-1)+1)+0,2)+mod(re(2*(i-1)+2)+0,2);
        pat(3,1,1)=mod(re(2*(i-1)+1)+1,2)+mod(re(2*(i-1)+2)+1,2);
        pat(4,1,2)=4;
        pat(3,1,2)=4;
    elseif(i==len+1)
        for j=1:4
           ck1= mod(re(2*(i-1)+1)+key(j,1),2)+mod(re(2*(i-1)+2)+key(j,2),2);
           ck0= mod(re(2*(i-1)+1)+key(j,3),2)+mod(re(2*(i-1)+2)+key(j,4),2);
           if(j==1)
               if (pat(2,i,1)>ck0+pat(1,i-1,1))
                   pat(2,i,1)=ck0+pat(1,i-1,1);
                   pat(2,i,2)=j;
               end
           elseif(j==2)
               if (pat(4,i,1)>ck0+pat(2,i-1,1))
                   pat(4,i,1)=ck0+pat(2,i-1,1);
                   pat(4,i,2)=j;
               end
           elseif(j==3)
               if (pat(2,i,1)>ck0+pat(3,i-1,1))
                   pat(2,i,1)=ck0+pat(3,i-1,1);
                   pat(2,i,2)=j;
               end
           elseif(j==4)
               if (pat(4,i,1)>ck0+pat(4,i-1,1))
                   pat(4,i,1)=ck0+pat(4,i-1,1);
                   pat(4,i,2)=j;
               end
           end
        end
    elseif(i==len+2)
        a=pat(2,len+1,1)+mod(re(2*(i-1)+1)+1,2)+mod(re(2*(i-1)+2)+1,2);
        b=pat(4,len+1,1)+mod(re(2*(i-1)+1)+0,2)+mod(re(2*(i-1)+2)+0,2);
        if(a<=b)
            pat(4,len+2,2)=2;
            pat(4,6,1)=a;
        else
            pat(4,len+2,2)=4;
            pat(4,len+2,1)=b;
        end
    else
        for j=1:4
           ck1= mod(re(2*(i-1)+1)+key(j,1),2)+mod(re(2*(i-1)+2)+key(j,2),2);
           ck0= mod(re(2*(i-1)+1)+key(j,3),2)+mod(re(2*(i-1)+2)+key(j,4),2);
           if(j==1)
               if (pat(1,i,1)>ck1+pat(1,i-1,1))
                   pat(1,i,1)=ck1+pat(1,i-1,1);
                   pat(1,i,2)=j;
               end
               if (pat(2,i,1)>ck0+pat(1,i-1,1))
                   pat(2,i,1)=ck0+pat(1,i-1,1);
                   pat(2,i,2)=j;
               end
           elseif(j==2)
               if (pat(3,i,1)>ck1+pat(2,i-1,1))
                   pat(3,i,1)=ck1+pat(2,i-1,1);
                   pat(3,i,2)=j;
               end
               if (pat(4,i,1)>ck0+pat(2,i-1,1))
                   pat(4,i,1)=ck0+pat(2,i-1,1);
                   pat(4,i,2)=j;
               end
           elseif(j==3)
               if (pat(1,i,1)>ck1+pat(3,i-1,1))
                   pat(1,i,1)=ck1+pat(3,i-1,1);
                   pat(1,i,2)=j;
               end
               if (pat(2,i,1)>ck0+pat(3,i-1,1))
                   pat(2,i,1)=ck0+pat(3,i-1,1);
                   pat(2,i,2)=j;
               end
           elseif(j==4)
               if (pat(3,i,1)>ck1+pat(4,i-1,1))
                   pat(3,i,1)=ck1+pat(4,i-1,1);
                   pat(3,i,2)=j;
               end
               if (pat(4,i,1)>ck0+pat(4,i-1,1))
                   pat(4,i,1)=ck0+pat(4,i-1,1);
                   pat(4,i,2)=j;
               end
           end
        end
    end
end
disp(pat);
k=4;
for i=len+2:-1:1
    tra(i)=pat(k,i,2);
    k=pat(k,i,2);
end
k=4;
for i=1:len
    if(k==4)
        if(tra(i+1)==3)
            fans(i)=1;
        else
            fans(i)=0;
        end
    elseif(k==3)
        if(tra(i+1)==1)
            fans(i)=1;
        else
            fans(i)=0;
        end
    elseif(k==2)
        if(tra(i+1)==3)
            fans(i)=1;
        else
            fans(i)=0;
        end
    elseif(k==1)
        if(tra(i+1)==1)
            fans(i)=1;
        else
            fans(i)=0;
        end
    end
    k=tra(i+1);
end
disp(fans);