#include <bits/stdc++.h>
using namespace std;

/// Typedef
typedef long long           ll;
typedef unsigned long       ul;
typedef unsigned long long  ull;
typedef vector<int>         vi;
typedef vector<vi>          vvi;
typedef vector<ll>          vll;
typedef pair<int,int>       pii;
typedef pair<ll,ll>         pll;

#define pb                  push_back
#define ppb                 pop_back
#define MP                  make_pair
#define ff                  first
#define ss                  second
#define sf                  scanf
#define pf                  printf
#define loop(i, y)          for(int i=0; i<int(y); i++)
#define FOR(i, x, y)        for(int i=int(x); i<int(y); i++)
#define ROF(i, x, y)        for(int i=int(x); i>=int(y); i--)

#define MAX 100005
int cars,TIQ,TA,TB,cu;
vector<int>ASE,BSE;
vector<int> TBA (MAX), AS(MAX),BS(MAX),RDFA(MAX),RDFS(MAX);
vector<double> pro (MAX),AP(MAX),BP(MAX);
vector<pii> RDC (MAX),RDA(MAX),RDB(MAX);
int check(int RD){
    FOR(i,0,cars){
        if(RD>=RDC[i].ff && RD<=RDC[i].ss)
            return TBA[i];
    }
}
pair<int,pair<int,int> > checkA(int clc,int RD){
    pair<int,pair<int,int> > temp;
    temp.ff = clc;
    FOR(i,0,cars){
        if(RD>=RDA[i].ff && RD<=RDA[i].ss)
        {
            temp.ss.ff = AS[i];
            break;
        }
    }
    temp.ss.ss = temp.ff + temp.ss.ff;
    return temp;
}
pair<int,pair<int,int> > checkB(int clc,int RD){
    pair<int,pair<int,int> > temp;
    temp.ff = clc;
    FOR(i,0,cars){
        if(RD>=RDB[i].ff && RD<=RDB[i].ss)
        {
            temp.ss.ff = BS[i];
            break;
        }
    }
    temp.ss.ss = temp.ff+temp.ss.ff;
    return temp;
}
int main(){
    system("COLOR F0");

    freopen("C:\\Users\\Raihanur\\Documents\\Dinput.txt", "r", stdin);
    freopen("C:\\Users\\Raihanur\\Documents\\Doutput.txt", "w", stdout);


    printf("Carhop Problem\n");
    printf("Able and baker are two Carhop here\n");
    printf("Now for your knowledge Able is batter then baker\n");
    printf("Enter The number of Cars/\n");
    scanf("%d",&cars);
    printf("Enter input for Interarrival Distribution of Cars/\n");
    printf("TBA\t\tPro.\tRD\n");
    FOR(i,0,cars){
        cin>>TBA[i]>>pro[i];char c;
        scanf("%d %c%d",&RDC[i].ff,&c,&RDC[i].ss);
    }
    printf("Enter the service Distribution for Abel\n");
    printf("ST\t\tPro.\tRD\n");
    FOR(i,0,cars){
        cin>>AS[i]>>AP[i];char c;
        scanf("%d %c%d",&RDA[i].ff,&c,&RDA[i].ss);
    }
    printf("Enter the service Distribution for Baker\n");
    printf("ST\t\tPro.\tRD\n");
    FOR(i,0,cars){
        cin>>BS[i]>>BP[i];char c;
        scanf("%d %c%d",&RDB[i].ff,&c,&RDB[i].ss);
    }
    FOR(i,0,cars){

        cout<<AS[i]<<" "<<BS[i]<<endl;
    }
    printf("Enter the number of customers\n");
    scanf("%d",&cu);
    printf("Enter Random Digit for Arrival\n");
    RDFA.pb(-1);
    FOR(i,2,cu+1)cin>>RDFA[i];
    printf("Enter Random Digit for Service\n");
    FOR(i,1,cu+1)cin>>RDFS[i];
    system("cls");
    printf("      \t\t\t\t\tSimulation and Modelling\n");
    printf("\t\t\t\t\tDouble Channel Queue\n");
    cout<<"-------------------------------------------------------------------------------------------"<<endl;
    printf("   \t\t\t\t\t\tABEL \t\t\tBaker\t\n");
    printf("   \t\t\t\t\t____________________\t____________________\n");
    printf("CNO\tRDA\tTBA\tCTA\tRDS\tTSB\tST \tTBE\tTSB\tST \tTBE\tTIQ\n");
    int clc=0;TA=0,TB=0;
    int a=0,b=0,ab=0,ba=0,cus=0;
    BSE.pb(0);
    FOR(i,1,cu+1){
        TIQ=0;
        printf("% 2d\t",i);
        if(i==1){
            printf(" -\t");
            printf(" -\t");
            printf("% 2d\t",0);
            int RD = RDFS[i];///generate RD for first customer
            pair<int,pair<int,int> > temp;
            temp = checkA(clc,RD);
            printf("% 2d\t",RD);
            printf("% 2d\t",0);
            printf("% 2d\t",temp.ss.ff);
            printf("% 2d\t",temp.ss.ss);
            printf("\t\t\t");
            printf("% 2d\n",0);
            TA=temp.ss.ss;
            ASE.pb(temp.ss.ss);
            a++;ab+=temp.ss.ff;
        }
        else
        {
            int RD1 = RDFA[i];
            int tba = check(RD1);
            printf("% 2d\t",RD1);
            //cout<<tba <<" clock "<<clc<<endl;
            printf("% 2d\t",tba);clc+=tba;
            printf("% 2d\t",clc);
            int RD2 = RDFS[i];
            printf("% 2d\t",RD2);
            if(clc>=TA){
                pair<int,pair<int,int> > temp;
                temp = checkA(clc,RD2);
                printf("% 2d\t",max(temp.ff,ASE[a-1]));
                printf("% 2d\t",temp.ss.ff);
                printf("% 2d\t",temp.ss.ss);
                printf("\t\t\t");cus+=max(0,ASE[a-1]-clc);
                printf("% 2d\n",max(0,ASE[a-1]-clc));a++;
                TA=temp.ss.ss;
                ASE.pb(temp.ss.ss);ab+=temp.ss.ff;
            }
            else if(clc>=TB)
            {
                printf("\t\t\t");
                pair<int,pair<int,int> > temp;
                temp = checkB(clc,RD2);
                printf("% 2d\t",max(temp.ff,BSE[b-1]));
                printf("% 2d\t",temp.ss.ff);
                printf("% 2d\t",temp.ss.ss);cus +=max(0,BSE[b] - (BSE[b]==0?BSE[b]:clc) );
                printf("% 2d\n",max(0,max(0,BSE[b]-(BSE[b]==0?BSE[b]:clc))));b++;
                TB=temp.ss.ss;
                BSE.pb(temp.ss.ss);ba+=temp.ss.ff;
            }
            else if(TA==TB)
            {
                pair<int,pair<int,int> > temp;
                temp = checkA(max(clc,TA),RD2);
                printf("% 2d\t",max(temp.ff,ASE[a-1]));
                printf("% 2d\t",temp.ss.ff);
                printf("% 2d\t",temp.ss.ss);
                printf("\t\t\t");cus+=max(0,ASE[a-1]-clc);
                printf("% 2d\n",max(0,ASE[a-1]-clc));a++;
                TA=temp.ss.ss;
                ASE.pb(temp.ss.ss);ab+=temp.ss.ff;
            }
            else if(TA>TB){
                printf("\t\t\t");
                pair<int,pair<int,int> > temp;
                temp = checkB(max(clc,TB),RD2);
                printf("% 2d\t",max(temp.ff,BSE[b]));
                printf("% 2d\t",temp.ss.ff);
                printf("% 2d\t",temp.ss.ss);cus +=max(0,BSE[b]-(BSE[b]==0?BSE[b]:clc));
                printf("% 2d\n",max(0,BSE[b]-(BSE[b]==0?BSE[b]:clc)));b++;
                TB=temp.ss.ss;
                BSE.pb(temp.ss.ss);ba+=temp.ss.ff;
            }
            else
            {
                pair<int,pair<int,int> > temp;
                temp = checkA(max(clc,TA),RD2);
                printf("% 2d\t",max(temp.ff,ASE[a-1]));
                printf("% 2d\t",temp.ss.ff);
                printf("% 2d\t",temp.ss.ss);
                printf("\t\t\t");cus+=max(0,ASE[a-1]-clc);
                printf("% 2d\n",max(0,ASE[a-1]-clc));a++;
                TA=temp.ss.ss;
                ASE.pb(temp.ss.ss);ab+=temp.ss.ff;
            }
        }
        cout<<"-------------------------------------------------------------------------------------------"<<endl;
    }
    printf("\n\n");
    printf("\t\t\t\tPERFORMANCE OF THE SYSTEM IS AS FOLOWS:\n");
    printf("\t\t\t\tAVERAGE SERVICE TIME OF ABEL: %.2f\n",(double)ab/a);
    printf("\t\t\t\tAVERAGE SERVICE TIME OF BAKER: %.2f\n",(double)ba/b);
    printf("\t\t\t\tAVERAGE WAITING TIME OF CUSTOMERS: %.2f\n",(double)cus/cu);

    return 0;
}
