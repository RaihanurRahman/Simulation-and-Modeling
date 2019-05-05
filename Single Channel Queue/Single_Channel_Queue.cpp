#include <bits/stdc++.h>
using namespace std;
typedef long long       	ll;
typedef unsigned long   	ul;
typedef unsigned long long  ull;
typedef vector<int>     	vi;
typedef vector<vi>      	vvi;
typedef vector<ll>      	vll;
typedef pair<int,int>   	pii;
typedef pair<ll,ll>     	pll;
#define pb              	push_back
#define ppb             	pop_back
#define MP              	make_pair
#define ff              	first
#define ss              	second
#define sf              	scanf
#define pf              	printf
#define loop(i, y)      	for(int i=0; i<int(y); i++)
#define FOR(i, x, y)    	for(int i=int(x); i<int(y); i++)
#define ROF(i, x, y)    	for(int i=int(x); i>=int(y); i--)
struct Time_Between_Arrival
{
	int arival_time;
	double probability,cum_probability;
	pair<int,int > random_digit;
} dtba[15];
struct Service_time
{
	int service_time;
	double probability, cum_probability;
	pair<int,int> random_digit;
} st[10];
char ch ;
void print_dtba(int n);
void gen_Time_between_arival(){
	int n ;
	printf("number of entry for time between arival:\n");
	cin>>n;
	int t2=100, t1=1;
	printf(" arival_time probability random_digit\n");
	for(int i = 1;i<=n;i++){
    	cin>>dtba[i].arival_time;
    	cin>>dtba[i].probability;
    	dtba[i].cum_probability = dtba[i-1].cum_probability+ dtba[i].probability;
    	cin>>dtba[i].random_digit.first;
    	cin>>ch;
    	cin>>dtba[i].random_digit.second;
	}
	//print_dtba(n);
}
void print_dtba(int n){
	printf("Distribution of time between arival:\n");
	printf("TBA\tPRO\tCPRO\tRD\n");
	for(int i = 1;i<=n;i++){
    	printf("%d\t%.2f\t%.2f\t%d - %d\n",
    	dtba[i].arival_time,dtba[i].probability , dtba[i].cum_probability,dtba[i].random_digit.first,dtba[i].random_digit.second);
	}
	printf("\n");
}
void print_service_time_distribution(int n);
void gen_service_time_distribution(){
	int n;
	printf("number of entry for service_time distribution\n");
	cin>>n;
	printf("service_time probability random_digit");
	int t2=5, t1=1;
	for(int i = 1;i<=n;i++){
    	cin>>st[i].service_time;
    	cin>>st[i].probability;
    	st[i].cum_probability = st[i-1].cum_probability+ st[i].probability;
    	cin>>st[i].random_digit.first ;
    	cin>>ch;
    	cin>>st[i].random_digit.second;
	}
	//print_service_time_distribution(n);
}
void print_service_time_distribution(int n){
	printf("service time distribution:\n");
	printf("ST\tPRO\tCPRO\tRD\n");
	for(int i = 1;i<=n;i++)
    	printf("%d\t%.2f\t%.2f\t%d - %d\n",st[i].service_time,st[i].probability, st[i].cum_probability,st[i].random_digit.first, st[i].random_digit.second );
	printf("\n");
}
struct Customer
{
	int id, arival_time, service_time,random_digit_arival, random_digit_service;
}customer[20];
int get_arival_time(int t){
	for(int i = 1;i<=10;i++){
    	if(dtba[i].random_digit.first<=t && dtba[i].random_digit.second>=t){
        	return dtba[i].arival_time;
    	}
	}
	return -1;
}
int get_service_time(int t){
	for(int i = 1;i<=5;i++){
    	if(st[i].random_digit.first
        	<= t && st[i].random_digit.second>= t)return st[i].service_time;
	}
	return -1;
}
void gen_customer(int n){
	for(int i = 2;i<=n;i++){
    	cin>>customer[i].random_digit_arival,
    	customer[i].arival_time = get_arival_time(customer[i].random_digit_arival);
	}
	for(int i = 1;i<=n;i++){
    	customer[i].id = i;
    	cin>>customer[i].random_digit_service ;
    	customer[i].service_time = get_service_time(customer[i].random_digit_service);
	}
}
void print_customer(int n){
	printf("customer :\n");
	printf("id\tRDA\tAT\tRDS\tST\n");
	for(int i = 1;i<= n;i++)
	printf("%d\t%d\t%d\t%d\t%d\n",customer[i].id , customer[i].random_digit_arival,customer[i].arival_time,customer[i].random_digit_service,customer[i].service_time );
}
int t[10][13];
void simulation(int n)
{
	int clk = 0, q = 0, sys = 0,idle  = 0;
	customer[1].arival_time = 0;
	t[0][2] = 0;
	for(int i = 1; i<=n; i++)
	{
    	t[i][0]=i;///customer id
    	t[i][1] = customer[i].arival_time; ///time_since arival
    	t[i][2] = t[i-1][2]+customer[i].arival_time;
    	t[i][3] = customer[i].service_time;
    	clk = max(clk,t[i][2]);
    	t[i][4] = max(t[i][2],t[i-1][6]);///service time start;
    	t[i][5] = max(0,t[i][4] - t[i][2]); ///waits in queue;
    	t[i][6] = clk+customer[i].service_time;///service end;
    	clk +=customer[i].service_time;
    	t[i][7] = t[i][6]-t[i][2]; ///customer in system;
    	t[i][8]  = max(0,t[i][2]-t[i-1][6]);///idle of server;
	}
}
void Print_Simulation(int n)
{
	double  avg_service_time=0;
	double avg_server = 0;
	double avg_waiting_time = 0,waits = 0;
	printf("  	\t\t\t\t\tSimulation and Modelling\n");
	printf("\t\t\t\t\tSingle Channel Queue\n");
	cout<<"\t\t---------------------------------------------------------------------"<<endl;
	printf("\t\tCNO\tTLA\tAT\tST\tTSB\tTIQ\tTSE\tTCS\tITS\n");
	for(int i = 1; i<=n; i++)
	{
    	cout<<"\t\t";
    	for(int j =0; j<=8; j++)
    	{
        	printf("%d\t", t[i][j]);
    	}
    	printf("\n");
    	cout<<"\t\t---------------------------------------------------------------------"<<endl;
    	avg_service_time += t[i][3];
    	avg_waiting_time+=t[i][5];
    	if(t[i][5])
        	waits++;
    	avg_server+=t[i][7];
	}
	printf("\n\n");
	printf("\t\t\t\tPERFORMANCE OF THE SYSTEM IS AS FOLOWS:\n");
	printf("\t\t\t\tAVG_SERVICE_TIME: %.2f\n",avg_service_time/n);
	printf("\t\t\t\tAVG_WAITING_TIME: %.2f\n",avg_waiting_time/waits);
	printf("\t\t\t\tPROBABILITY OF WAITS: %.2f \n",waits/n);
	printf("\t\t\t\tAVG TIME SPENT BY CUSTOMER IN SYSTEM: %2.f\n",avg_server/n);
}

int main()
{
	system("COLOR F0");
	freopen("C:\\Users\\Raihanur\\Documents\\Sinput.txt","r",stdin);
	freopen("C:\\Users\\Raihanur\\Documents\\Soutput.txt","w",stdout);
	gen_Time_between_arival();
	gen_service_time_distribution();
	printf("Enter number of Customers\n");
	int n;
	cin>>n;
	gen_customer(n);
	//print_customer(n);
	system("cls");
	simulation(n);
	Print_Simulation(n);
}
