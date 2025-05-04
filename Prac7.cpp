#include<iostream>
#include<string.h>
using namespace std;
class flight{
    public:
    int city_count;
    char city_index[10][10];
    int cost[10][10];
    flight(){
        city_count=0;
        for(int i=0;i<city_count;i++){
            for(int j=0;j<10;j++){
                cost[i][j]=0;
            }
        }
    }
        int getCityIndex(char name[])
         {
            for (int i = 0; i < city_count; i++) {
                if (strcmp(city_index[i], name) == 0)
                    return i;
            }
            return -1;
         }
    
    void create(){
        int si,di,j,wt;
        char chi;
        char s[10],d[10];
        do{
        cout<<"Enter source city :";
        cin>>s;
        si = getCityIndex(s);
        if(si==-1){
            if(city_count>=10){
                cout<<"city count rearch..";
                return;
            }
           strcpy(city_index[city_count],s);
           si=city_count;
           city_count++;
        }

        cout<<"Enter destination city : ";
        cin>>d;
        di=getCityIndex(d);
        if(di==-1){
            if(city_count>=10){
                cout<<"city count rearch..";
                return;
            }
           strcpy(city_index[city_count],d);
           di=city_count;
           city_count++;
        }
        cout<<"Enter distance b/w"<<s<<" and "<<d<<" :: ";
        cin>>wt;
        cost[si][di]=wt;
        cout<<"\n\t do you want to add more cities(y\n) : ";
        cin>>chi;
    }while(chi=='y'||chi=='Y');
    
    }
    void display()
    {
        int i,j;
        cout<<"Displaying Adjancey Matrix..."<<endl;
        cout<<"\t";
        for(int i=0;i<city_count;i++){
            cout<<city_index[i]<<"\t";            
        }
        cout<<"\n";
        for(int i=0;i<city_count;i++){
            cout<<city_index[i]<<"\t";            

            for(int j=0;j<city_count;j++){
                cout<<cost[i][j]<<"\t";
            }
            cout<<"\n";
        }
    }
};
int main(){
    flight f;
    int n;
    char ans;
    do{
    cout<<"\n ------MENU--------"<<endl;
    cout<<"1.create "<<endl;
    cout<<"2.display "<<endl;
    cout<<"3.exit "<<endl;
    cout<<"Enter your choice : ";
    cin>>n;
    switch(n){
        case 1:
            f.create();
            break;
        case 2:
            f.display();
            break;
        case 3:
            return 0;
            
        default :
            cout<<"wrong choice";
            
    }
    cout<<"do you want to continue menu....(y/n) :";
    cin>>ans;
    }while(ans=='y'||ans=='Y');
    return 0;
}
