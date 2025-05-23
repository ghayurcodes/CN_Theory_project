#pragma once
#include"tour.h"
#include"accomodation.h"

bool check(long long int cnic);//forwart decleration of function from main
int guide_pick(long long int);

class business:public tour{
    string comapny_name;
    string business_type;
    accomodation *for_business=nullptr;


    public:
    business();
    business(string, string, int, int, string, string, string, string, float, long, bool, bool, int, int,string);
    ~business();
    //member functions
    void menu();
    friend istream& operator>>(istream&,business&);
    void display();
    void find(int,vector<business>&);
    void update(int,vector<business>&);
    //static functions
    static void load(vector<business>&);
    static void save(vector<business>&);
    static void demolish(int,vector<business>&);

    
};

business::business():comapny_name(" "),business_type(" "),tour(){
    for_business=new accomodation();
};

business::business(string comp,string type,int ppl,int room,string _detail,string _destination, string _departure, string _time, float _price,long _cnic,bool inte,bool food,int _id,int _age,string _name):
comapny_name(comp),business_type(type),tour(_destination,_departure,_time,_price,_cnic,inte,food,_id,_age,_name){
    for_business=new accomodation(ppl,room,_detail);
};

business::~business() {
    if (for_business == nullptr) {
        delete for_business;
    }
}


void business::menu(){
        vector<business> vec;
        int opt;
        load(vec);
        while(true){
        cout<<"\n--------------------------------------------------\n";
        cout<<"Press 1 to add an Entry.\nPress 2 to view all data.\nPress 3 to find specifiic Entry.\nPress 4 to update.\nPress 5 to delete.\nPress 6 to go back\n";
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
            find(opt,vec);
        }
        else if(opt==4){
            cout<<"Enter flight number:\n";
            cin>>opt;
            update(opt,vec);
        }
        else if(opt==5){
            cout<<"Enter flight number:\n";
            cin>>opt;
            demolish(opt,vec);
        }
        else if(opt==6){
            for(int i=0;i<vec.size();i++){
                delete vec[i].for_business;
            }
            
            return;
        }
    }
}
        

istream& operator>>(istream& in,business&b){
    int id,age,ppl=1,room=0;
    string name,instruction;

    cout<<"Enter name:\n";
    getline(in>>ws,name);
    b.tour_detail.setName(name);
    cout<<"Enter cnic:\n";
    in>>b.cnic;
    while(check(b.cnic)){
    cout<<"Enter cnic:\n";
    in>>b.cnic;
    }
    cout<<"Enter age:\n";
    in>>ws>>age;
    b.tour_detail.setAge(age);
    cout<<"Enter Destination:\n";
    getline(in>>ws,b.destination);
    cout<<"Enter Departure location:\n";
    getline(in>>ws,b.departure);
    cout<<"Enter Company Nmae:\n";
    getline(cin>>ws,b.comapny_name);
    cout<<"Enter Business type:\n";
    getline(cin>>ws,b.business_type);
    cout<<"Press 1 to apply for accomodation 2 to skip:\n";
    int opt;
    in>>opt;

    if (opt == 1) {
        cout<<"Enter no of People:\n";
        in>>ppl;
        b.for_business->setNoPeople(ppl);
        cout<<"Enter no of rooms required:\n";
        in>>room;
        b.for_business->setRooms(room);
        cout<<"Any special message:\n";
        getline(cin>>ws,instruction);
        b.for_business->setDetail(instruction);
    } else if(opt==2 ||opt>2) {
        b.for_business->setDetail("nil");
        b.for_business->setNoPeople(ppl);
        b.for_business->setRooms(room);
    }
    cout<<"Press 1 if you want a tour guide 2 to skip:\n";
    in>>opt;
    if(opt==1){
        b.guide_id=guide_pick(-1);
    }
    else{
         b.guide_id=0;
    }
    
    b.tour_detail.setId(tour::generate_id());
    cout<<"\n--Flight id alloted is: "<<b.tour_detail.getId();
    b.price=2000;
    if(b.for_business->getNoPeople()>2){
    b.price*=ppl;
    }
    return in;
   }

void business::display() {
        cout << "\nName: " << tour_detail.getName() << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Age: " << tour_detail.getAge() << endl;
        cout << "Price: " << price << endl;
        cout << "ID: " << tour_detail.getId() << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure: " << departure << endl;
        cout << "Company Name: " << comapny_name << endl;
        cout << "Business Type: " << business_type << endl;
        cout << "Number of People: " << for_business->getNoPeople()<< endl;
        cout << "Rooms: " << for_business->getRooms() << endl;
        cout << "Detail: " << for_business->getDetail() << endl;
        cout<<"\nGuide Registered: "<<guide_pick(guide_id)<<endl;
        cout<<"----------------------------------------------------------------------------------------------------------------------\n"; 
        
        
}

void business::find(int key,vector<business>& v){
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].tour_detail.getId()==key){
            cout<<"\n----ID found----\n";
            found=true;
            v[i].display();
        }
    }
    if(!found){
        cout<<"\n----Such ID does not Exists.----\n";
    }
    
}

void business::update(int key,vector<business>& v){
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

void business::save(vector<business>& v){
        ofstream fout;
        fout.open("business.txt");
        for(int i=0;i<v.size();i++){
        fout<<v[i].tour_detail.getName()<<"\n"<<v[i].cnic<<"\t"<<v[i].tour_detail.getAge()<<"\t"<<v[i].price<<"\t"<<v[i].tour_detail.getId()<<"\t"<<v[i].guide_id<<"\n"<<v[i].destination<<"\n"<<v[i].departure<<"\n"<<v[i].comapny_name<<"\n"<<v[i].business_type
        <<"\n"<<v[i].for_business->getNoPeople()<<"\t"<<v[i].for_business->getRooms()<<"\n"<<v[i].for_business->getDetail()<<endl;  
        }
    fout.close();
   }


void business::load(vector<business>& v) {
    ifstream fin;
    fin.open("business.txt");
    if (!fin.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    string line;
    while (getline(fin, line)) {
        business b;
        b.tour_detail.setName(line);
        getline(fin, line, '\t');
        b.cnic = stoi(line);
        getline(fin, line, '\t');
        b.tour_detail.setAge(stoi(line));
        getline(fin, line, '\t');
        b.price = stof(line);
        getline(fin, line,'\t');
        b.tour_detail.setId(stoi(line));
        getline(fin, line);
        b.guide_id=stoi(line);
        getline(fin, b.destination);
        getline(fin, b.departure);
        getline(fin, b.comapny_name);
        getline(fin, b.business_type);
        getline(fin, line, '\t');
        int people = stoi(line);
        getline(fin,line);
        int rooms = stoi(line);
        getline(fin, line);
        string detail = line;
        b.for_business = new accomodation(people, rooms, detail);
        v.push_back(b);   
    }  
    fin.close();
      
}


void business::demolish(int key,vector<business>& v){
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].tour_detail.getId()==key){
            cout<<"\n----record deleted----\n";
            v.erase(v.begin()+i);
            found=true;
        }
    }save(v);
    if(!found){
        cout<<"\n----Such ID does not Exists.----\n";
    }
}

