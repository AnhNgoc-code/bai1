#include<stdio.h>
int main(){
    double sum=0;
    int stc=0;
    int tstc=0;
    int diem;
    int n;
    printf("nhap so módfsdfn hoc la :");
    scanf("%d",&n);
    for ( int i = 1; i <= n; i++)
    {
        printf("nhap diem mon %d",i);
        scanf("%d",&diem);
        printf("nhap so tin chi mon %d",i);
        scanf("%d",&stc);
    }
    tstc+=stc;
    sum+=(diem *stc)/tstc;
    printf("tong trung binh gpa cua mon la %lf",sum);
    return 0;
}

