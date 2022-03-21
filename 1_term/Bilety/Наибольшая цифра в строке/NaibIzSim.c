//Created by SiFi

void func(char* a)
{int i=0,s=0,smax=0,k,n=0;
    while (a[i]){s = 0; k = 0;
        while (a[i] >= '1' && a[i] <= '9' && a[i])
        {s+= (a[i++] - '0');s *= 10;} s /= 10;
        if (s>smax)smax = s;
        if(a[i])i++;}
    printf("%d", smax);}
