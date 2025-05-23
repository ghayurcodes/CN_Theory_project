#pragma once
#include"tour.h"
#include"accomodation.h"

bool check(long long int cnic);//forwart decleration of function from main

 class package:public tour{
    protected:
    string pkg_name;
    int members;

    public:
    package();
    package(string ,int,string , string ,  string , float,  detail ,int , int, string );
    //member functions
    void menu();
    friend istream& operator>>(istream&,package&);
    void select_pkg();
    void display();
    void update(int,vector<package>&);
    void find(int,vector<package>&);
    //static functions
    static void save(vector<package>&);
    static void load(vector<package>&);
    static void demolish(int,vector<package>&);

        
    
};
package::package():pkg_name(" "),members(0),tour(){};

package::package(string _pkgname,int _members,string _destination, string _departure,  string _date, float _price,  detail _tour_detail,int _id, int _age, string _gender):pkg_name(_pkgname),
members(_members),tour( _destination,  _departure,  _date,  _price, _id, _age, _gender){};

void package::menu(){
        vector<package> vec;
        int opt;
        load(vec);
        while(true){
        cout<<"\nPress 1 to add an Entry.\nPress 2 to view all data.\nPress 3 to find specifiic Entry.\nPress 4 to update.\nPress 5 to delete.\nPress 6 to go back\n";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------\n"; 
        cin>>opt;
        if(opt==1){
            cin>>*this;
            vec.push_back(*this);
            save(vec);  
        }
        else if(opt==2){
             if(vec.size()==0){
                cout<<"\n---File is empty no recordes there---\n";
            }
            else{
                 for (int i = 0; i < vec.size(); i++) {
                vec[i].display();
            }
            } 
        }
        else if(opt==3){
            cout<<"Enter flight number:\n";
            cin>>opt;
            this->find(opt,vec);
        }
        else if(opt==4){
            cout<<"Enter flight number:\n";
            cin>>opt;
            this->update(opt,vec);
        }
        else if(opt==5){
            cout<<"Enter flight number:\n";
            cin>>opt;
            demolish(opt,vec);
        }
        else if(opt==6){
            return;
        }
    }
}

istream& operator>>(istream& in,package &p){
        int id,age;
        string name;
        cout<<"Enter Name:\n";
        getline(in>>ws,name);
        p.tour_detail.setName(name);
        cout<<"Enter cnic:\n";
        in>>ws>>p.cnic;
        while(check(p.cnic)){
        cout<<"Enter cnic:\n";
        in>>p.cnic;
    }
        cout<<"Enter age:\n";
        in>>age;
        p.tour_detail.setAge(age);
        cout<<"Enter Total Passengers:\n";
        in>>p.members;
        p.select_pkg();
        return in;
}


void package::select_pkg(){ 
cout << "\n\nPress 1 for UMRAH PACKAGE:\n";
    cout << "Destination: Mecca and Medina, Saudi Arabia\n";
    cout << "Activities:\n";
    cout << "- Visiting the Masjid al-Haram (Great Mosque of Mecca)\n";
    cout << "- Performing Tawaf (circumambulation) around the Kaaba\n";
    cout << "- Performing Sa'i (walking) between the hills of Safa and Marwa\n";
    cout << "- Visiting the Prophet's Mosque in Medina\n";
    cout << "- Offering prayers at the Rawdah\n";
    cout << "Duration: 10 days\n";
    cout << "Price: $3000 per person\n";
cout << "\nPress 2 for City Exploration Tour Package - Dubai, UAE:\n";
    cout << "Destination: Dubai, United Arab Emirates\n";
    cout << "Activities:\n";
    cout << "- Burj Khalifa Observation Deck Visit\n";
    cout << "- Desert Safari with BBQ Dinner\n";
    cout << "- Dhow Cruise Dinner\n";
    cout << "Duration: 5 days\n";
    cout << "Price: $2000 per person\n";
cout << "\nPress 3 for Historical Tour Package - Cairo, Egypt:\n";
    cout << "Destination: Cairo, Egypt\n";
    cout << "Activities:\n";
    cout << "- Pyramids Tour\n";
    cout << "- Nile Cruise\n";
    cout << "- Egyptian Museum Visit\n";
    cout << "Duration: 5 days\n";
    cout << "Price: $2800 per person\n";
cout << "\nPress 4 for City Exploration Tour Package - Barcelona, Spain:\n";
    cout << "Destination: Barcelona, Spain\n";
    cout << "Activities:\n";
    cout << "- Gaudi Architecture Tour\n";
    cout << "- Tapas Tasting\n";
    cout << "- Flamenco Show\n";
    cout << "Duration: 3 days\n";
    cout << "Price: $1500 per person\n";
    
    int opt;
    cin>>opt;
    switch(opt){
        case 1:
        pkg_name="1";
        price=members*3000;
        date="27-May-2024";
       tour_detail.setId(tour::generate_id()); 
       cout<<"Flight id alloted is: "<<tour_detail.getId();
        break;

        case 2:
        pkg_name="2";
        price=members*2000;
        date="20-april-2024";
        tour_detail.setId(tour::generate_id());
        cout<<"Flight id alloted is: "<<tour_detail.getId();
        break;

        case 3:
        pkg_name="3";
        price=members*2800;
        date="12-August-2024";
        tour_detail.setId(tour::generate_id());
        cout<<"Flight id alloted is: "<<tour_detail.getId();
        break;

        case 4:
        pkg_name="4";
        price=members*1500;
        date="08-May-2024";
        tour_detail.setId(tour::generate_id());
        cout<<"Flight id alloted is: "<<tour_detail.getId();
        break;
        
    }
}

void package::display(){
    cout<<"Flight ID: "<<tour_detail.getId()<<endl;
    cout<<"Age: "<<tour_detail.getAge()<<endl;
    cout<<"CNIC: "<<cnic<<endl;
    cout<<"Name: "<<tour_detail.getName()<<endl;
    cout<<"Departure: "<<departure<<endl;
    cout<<"Destination: "<<destination<<endl;
    cout<<"Price: "<<fixed << setprecision(2) << price<<endl;
    cout<<"Date: "<<date<<endl;
   cout<<"Members: "<<members<<endl;
cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------------------\n";          
}

void package::find(int key,vector<package>& v){
     bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].tour_detail.getId()==key){
            cout<<"\n-----ID found----\n";
            found=true;
            v[i].display();
        }
    }
    if(!found){
        cout<<"\n----Such ID does not Exists.----\n";
    }
}

void package::update(int key,vector<package>& v){
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].tour_detail.getId()==key){
            cout<<"\n----Enter new Details----\n";
            found=true;
            cin>>v[i];
            
        }
    }save(v);
    if(!found){
        cout<<"\n----Such ID does not Exists.----\n";
    }
    
} 

void package::load(vector<package>& v){
        ifstream fin;
    fin.open("package.txt");
    if(fin.fail()){
        cout<<"error opening file\nExiting....";
        return;
    }
    int id,age;
    string name;
    package p;
    
    while(fin>>id){
        fin>>age;
        fin>>p.cnic;
        getline(fin>>ws,name,'\n');
        fin>>p.pkg_name;
        fin>>p.members;
        fin>>p.price;
        fin>>p.date;
        int pkg=stoi(p.pkg_name);
        if(pkg==1){
            p.departure="Pakistan";
            p.destination="Makkah";
        }
        else if(pkg==2){
            p.departure="Pakistan";
            p.destination="Dubai";
        }
        else if(pkg==3){
            p.departure="Pakistan";
            p.destination="Egypt";
        }
        else if(pkg==4){
            p.departure="Pakistan";
            p.destination="Spain";
        }
        p.tour_detail.setAge(age);
        p.tour_detail.setId(id);
        p.tour_detail.setName(name);
        v.push_back(p);
    }
    fin.close();
}

void package::save(vector<package>& v){
        ofstream fout;
        fout.open("package.txt");
        for(int i=0;i<v.size();i++){
        fout<<v[i].tour_detail.getId()<<"\t"<<v[i].tour_detail.getAge()<<"\t"<<v[i].cnic<<"\n"<<v[i].tour_detail.getName()<<"\n"<<v[i].pkg_name<<"\t"<<v[i].members<<"\t"<<v[i].price<<"\t"<<v[i].date<<endl;
        
}
fout.close();
}

void package::demolish(int key,vector<package>& v){
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].tour_detail.getId()==key){
            cout<<"\n----record deleted-----\n";
            v.erase(v.begin()+i);
            found=true;
            
            
        }
    }save(v);
    if(!found){
        cout<<"\n----Such ID does not Exists.----\n";
    }
}