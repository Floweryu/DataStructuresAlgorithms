#include<stdio.h>
#include<string.h>
int a[100000],b[100000],c[100000];
int main(){
    int i,j;
    int an,m,n;
    m=0;
    n=0;
    int max,maxa,maxb;
    max=0;
    maxa=0;
    maxb=0;
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    memset(c,0,sizeof(c));
    while(~scanf("%d %d",&n,&m)){
            if(m==-1&&n==-1)
                break;
            if(maxa<m)
                maxa=m;
            a[m]=n;
    }
    while(~scanf("%d%d",&n,&m)){
        if(m==-1&&n==-1)
            break;
        if(maxb<m)
            maxb=m;
        b[m]=n;
    }
    max=maxa+maxb;
    for(i=0;i<=maxa;i++){
        for(j=0;j<=maxb;j++){
            n=a[i]*b[j];
            if(n!=0){
                m=i+j;
                c[m]+=n;
            }
        }
    }
    int flag=1;
    for(i=max;i>=0;i--){
        if(c[i]!=0){
            flag=0;
            printf("%d %d ",c[i],i);
        }
    }
    if(flag)
        printf("0");
    printf("\n");
    return 0;
}
