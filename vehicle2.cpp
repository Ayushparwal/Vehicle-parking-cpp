#include<iostream>
#include<stdio.h>
#include<string.h>
#include<iomanip>
#include<fstream>
#include<ctime>
#include<bits/stdc++.h>
using namespace std;

class EarnedMoney{ 
    private:
    int cartype;
    int two_whtype;
    int bustype;
    int trucktype;
    int total;
    public:
    EarnedMoney(){                               
        this->cartype=0;
        this->two_whtype=0;
        this->bustype=0;
        this->trucktype=0;
        this->total=0;
    }
    void setEMoney(int cartype,int two_whtype,int bustype,int trucktype,int total){
        this->cartype=cartype;
        this->two_whtype=two_whtype;
        this->bustype=bustype;
        this->trucktype=trucktype;
        this->total=total;
    }
    void showEMoney(){                               
        cout<<"\n \t\t EARNED MONEY \n";
        cout<<setw(10)<<"car"<<setw(10)<<"2-wheeler"<<setw(10)<<"bus"<<setw(10)<<"truck"<<setw(10)<<"total\n";
        cout<<setw(9)<<this->cartype<<setw(9)<<this->two_whtype<<setw(9)<<this->bustype<<setw(9)<<this->trucktype<<setw(9)<<this->total<<endl;
    }
    void getallmoney();
    friend void addmoney(EarnedMoney,EarnedMoney&);  
};

void EarnedMoney:: getallmoney(){           //to know total money earned 
    // open file in read mode
    ifstream fin;
    fin.open("earnedmoney.txt",ios_base::in|ios_base::binary);
    fin.read((char*)this,sizeof(*this));  
}
void addmoney(EarnedMoney oldmoney, EarnedMoney &newmoney){
    
    newmoney.cartype+=oldmoney.cartype;
    newmoney.two_whtype+=oldmoney.two_whtype;
    newmoney.bustype+=oldmoney.bustype;
    newmoney.trucktype+=oldmoney.trucktype;
    newmoney.total+=oldmoney.total;
}

class vehicleType{     //parent class
    private:
    char VehicleTypeName[50];
    public:
    vehicleType(){    //constrctor
        strcpy(VehicleTypeName,"vehicle");
    }
    void SetVehicleType(EarnedMoney &earnedMoney){  
        int vehicle_type;
        while(1){                                  
            cout<<"\nSelect vehicle type: ";
            cout<<"\n1. car  2. two-wheeler  3. bus  4. truck : ";
            cin>>vehicle_type;
            if(vehicle_type==1){                    
                strcpy(VehicleTypeName,"car");
                earnedMoney.setEMoney(100,0,0,0,100);
                break;
            }
            else if(vehicle_type==2){
                strcpy(VehicleTypeName,"2wheeler");
                earnedMoney.setEMoney(0,50,0,0,50);      
                break;
            }
            else if(vehicle_type==3){
                strcpy(VehicleTypeName,"bus");
                earnedMoney.setEMoney(0,0,150,0,150);
                break;
            }
            else if(vehicle_type==4){
                strcpy(VehicleTypeName,"truck");
                earnedMoney.setEMoney(0,0,0,200,200);
                break;
            }
            else{
                cout<<"\ninvalid choice!!";
            }
        }
    }void ShowVehicleType(){
        cout<<VehicleTypeName<<"  ";
    }
};

class vehicle:public vehicleType{                 
    private:
    int vehicleNo;
    static int parking_slot;                     
    const int max = 20;                          
    char model[60];
    char drivername[50];
    char datetime[50];
    EarnedMoney earnedMoney;                    
    public:
    
    vehicle(){     
        this->vehicleNo=0;
        this->parking_slot=0;
        strcpy(this->model,"not set");
        strcpy(this->drivername,"default");
        time_t tt;                               
        tt=time(NULL);                          
        char *tm=ctime(&tt);                    
        strcpy(datetime,tm);
    }
    static int addparkslot(){               
        return parking_slot++;
    }
    static int delparkslot(){                 
        return parking_slot--;
    }
    void setvehicle(){                  
        if(parking_slot>max){
            cout<<"sorry no parking available!!\n";
        }
        else{
            SetVehicleType(earnedMoney);
            cout<<"\nEnter the vehicle number: ";
            cin>>vehicleNo;
            cin.ignore();
            cout<<"\nEnter the model: ";
            cin.getline(model,60);
            cout<<"\nEnter the driver name: ";
            cin.getline(drivername,50);
            time_t tt;
            tt=time(NULL); 
            char *tm=ctime(&tt);
            strcpy(datetime,tm);
            addparkslot();
        }
    }
    
    void showvehicle(){                                
        cout<<"Type\tno.\tmodel\tname\tslot\tdate\ttime\tyear\n";
        ShowVehicleType();                              
        cout<<"\t"<<vehicleNo<<"\t"<<model<<"\t"<<drivername<<"\t"<<parking_slot<<"\t"<<datetime<<endl;
    }
    void addvehicle();  
    void GetVehicleList();   
    void searchvehicle(int vehicleNo); 
    void deletevehicle(int vehicleNo);
    void updatevehicle(int vehicleNo);

};
int vehicle:: parking_slot=1;    
void vehicle::addvehicle(){
   
    ofstream fout;
    fout.open("addvehicle_data.txt",ios_base::app| ios_base::binary); 
    fout.write((char*)this,sizeof(*this)); 
    fout.close();
    EarnedMoney em;                 
    em.getallmoney();
    addmoney(em,this->earnedMoney);        
    fout.open("earnedmoney.txt",ios_base::out|ios_base::binary);        
    fout.write((char*)(&this->earnedMoney),sizeof(this->earnedMoney)); 
    fout.close();
}
void vehicle::GetVehicleList(){    
    ifstream fin;
    int records=0;
    fin.open("addvehicle_data.txt",ios_base::in| ios_base::binary);
    if(!fin){
        cout<<" \n file not found!!";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){          
            this->showvehicle();
            cout<<endl;
            records++;
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(records==0){
            cout<<"\nfile has no record!! ";
        }
    }
}
void vehicle::searchvehicle(int vehicleNo){
  
    ifstream fin;
    int records=0;
    fin.open("addvehicle_data.txt",ios_base::in| ios_base::binary);
    if(!fin){
        cout<<" \n file not found!!";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){     
            if(this->vehicleNo==vehicleNo){
                this->showvehicle();
                records=1;
                break;
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        if(records==0){
            cout<<"\nrecord not found!! ";
        }
    }
}
void vehicle::deletevehicle(int vehicleNo){
   
    ifstream fin;
    ofstream fout;
    int flag=0;
    fin.open("addvehicle_data.txt",ios_base::in| ios_base::binary);
    if(!fin){
        cout<<" \n file not found!!";
    }
    else{
        fin.read((char*)this,sizeof(*this));
        fout.open("tempaddvehicle_data.txt",ios_base::out| ios_base::binary);
        while(!fin.eof()){    
            if(this->vehicleNo==vehicleNo){
                flag=1;
            }
            else{
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        if(flag==0){
            cout<<"\nrecord not found!! cannot delete \n";
            remove("tempaddvehicle_data.txt");
        }
        else{
            cout<<"record deleted!!\n";
            remove("addvehicle_data.txt");
            rename("tempaddvehicle_data.txt","addvehicle_data.txt");
            delparkslot();
            cout<<"Your vehicle has left the parking area!\n";
        }
    }
}
void vehicle::updatevehicle(int vehicleNo){
    fstream foutin;
    int flag=0;
    foutin.open("addvehicle_data.txt",ios_base::in|ios_base::out|ios_base::ate| ios_base::binary);
                                                            
    foutin.seekg(0);     
    if(!foutin){
        cout<<" \n file not found!!";
    }
    else{
        foutin.read((char*)this,sizeof(*this));
        while(!foutin.eof()){
            if(this->vehicleNo==vehicleNo){
                cout<<" Update the data:- \n";
                cout<<"\nEnter the vehicle number: ";
                cin>>vehicleNo;
                cin.ignore();
                cout<<"\nEnter the model: ";
                cin.getline(model,60);
                cout<<"\nEnter the driver name: ";
                cin.getline(drivername,50);
                time_t tt;
                tt=time(NULL);
                char *tm=ctime(&tt);
                strcpy(datetime,tm);
                foutin.seekp(foutin.tellp()-std::streamoff(sizeof(*this)));     
                foutin.write((char*)this,sizeof(*this));
                cout<<"\nrecord updated!!";

                flag=1;
                break;
            }
            foutin.read((char*)this,sizeof(*this));
        }
        foutin.close();
        if(flag==0){
            cout<<"\nrecord not found!! ";
        }
    }
}

int menu(){
    int ch;
    cout<<"\n 1. Add vehicle ";
    cout<<"\n 2. Search vehicle ";
    cout<<"\n 3. Delete vehicle ";
    cout<<"\n 4. Update vehicle ";
    cout<<"\n 5. List all vehicles ";
    cout<<"\n 6. Check earned money ";
    cout<<"\n 7. Exit ";
    cout<<"\n Enter your choice: ";
    cin>>ch;
    return(ch);
}

int main(){
    vehicle v;
    EarnedMoney em;
    int breakloop=0,vehicleNo;
    
    while(1){
        switch(menu()){
            case 1:
                v.setvehicle();
                v.addvehicle();
                cout<<"\nYour vehicle has been parked!!"<<endl;
                break;
            case 2:
                cout<<"\nEnter vehicle number to find your vehicle:";
                cin>>vehicleNo;
                v.searchvehicle(vehicleNo);
                break;
            case 3:
                cout<<"\nEnter vehicle number to exit the parking area:";
                cin>>vehicleNo;
                v.deletevehicle(vehicleNo);
                break;
            case 4:
                cout<<"\n Enter vehicle number to update your data:";
                cin>>vehicleNo;
                v.updatevehicle(vehicleNo);
                break;
            case 5:
                v.GetVehicleList();
                break;
            case 6:
                em.getallmoney();
                em.showEMoney();
                break;
            case 7:
                breakloop=1;
                break;
            default:
                cout<<"\nInvalid input";
        }
        if (breakloop==1){
            break;
        }
    }

    return 0;
}