#pragma once
#include"tour.h"
#include"accomodation.h"

bool check(long long int cnic);//forwart decleration of function from main
int guide_pick(long long int);

class economy:public tour{
    string job;
    accomodation * for_eco=nullptr;


    public:
    economy();
    economy(string, int, int, string, string, string, string, float, long, bool, bool, int, int,string);
    ~economy();
    
    void menu();
    friend istream& operator>>(istream&,economy&);
    void display();
    void find(int,vector<economy>&);
    void update(int,vector<economy>&);
    
    static void load(vector<economy>&);
    static void save(vector<economy>&);
    static void demolish(int,vector<economy>&);

};

economy::economy():job(" "),tour(){
    for_eco=new accomodation;
}

economy::economy(string _job,int ppl,int room,string _detail,string _destination, string _departure, string _time, float _price,long _cnic,bool inte,bool food,int _id,int _age,string _name):
job(_job),tour(_destination,_departure,_time,_price,_cnic,inte,food,_id,_age,_name){
    for_eco=new accomodation(ppl,room,_detail);
}

economy::~economy(){
    if(for_eco==nullptr){
        delete for_eco;
    }   
}

void economy::menu(){
        vector<economy> vec;
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
            for(int i=0;i<vec.size();i++){
                delete vec[i].for_eco;
            }
            
            return;
        }
    }
}

istream& operator>>(istream& in,economy& e){
    int id,age,ppl=1,room=0;
    string name,instruction;

    cout<<"Enter name:\n";
    getline(in>>ws,name);
    e.tour_detail.setName(name);
    cout<<"Enter cnic:\n";
    in>>e.cnic;
    while(check(e.cnic)){
    cout<<"Enter cnic:\n";
    in>>e.cnic;
    }
    cout<<"Enter age:\n";
    in>>ws>>age;
    e.tour_detail.setAge(age);
    cout<<"Enter Destination:\n";
    getline(in>>ws,e.destination);
    cout<<"Enter Departure location:\n";
    getline(in>>ws,e.departure);
    cout<<"What is your Job:\n";
    getline(cin>>ws,e.job);
    cout<<"Press 1 to apply for accomodation 2 to skip:\n";
    int opt;
    in>>opt;
   
    if (opt == 1) {
        cout<<"Enter no of People:\n";
        in>>ppl;
        e.for_eco->setNoPeople(ppl);
        cout<<"Enter no of rooms required:\n";
        in>>room;
        e.for_eco->setRooms(room);
        cout<<"Any special message:\n";
        getline(cin>>ws,instruction);
        e.for_eco->setDetail(instruction);
    } else if(opt==2 ||opt>2) {
        e.for_eco->setDetail("nil");
        e.for_eco->setNoPeople(ppl);
        e.for_eco->setRooms(room);
    }
    cout<<"Press 1 if you want a tour guide 2 to skip:\n";
    in>>opt;
    if(opt==1){
        e.guide_id=guide_pick(-1);
    }
    else{
         e.guide_id=0;
    }

    e.tour_detail.setId(tour::generate_id());
    cout<<"\n--Flight id alloted is: "<<e.tour_detail.getId();
    e.price=2000;
    if(e.for_eco->getNoPeople()>2){
    e.price*=ppl;
    }
    return in;
   }
 void economy::display() {
         cout << "Name: " << tour_detail.getName() << endl;
        cout << "CNIC: " << cnic << endl;
        cout << "Age: " << tour_detail.getAge() << endl;
        cout << "Price: " << price << endl;
        cout << "ID: " << tour_detail.getId() << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure: " << departure << endl;
        cout << "Job: " << job << endl;
        cout << "Number of People: " << for_eco->getNoPeople()<< endl;
        cout << "Rooms: " << for_eco->getRooms() << endl;
        cout << "Detail: " << for_eco->getDetail() << endl;
        cout<<"\nGuide Registered: "<<guide_pick(guide_id)<<endl;
    cout<<"----------------------------------------------------------------------------------------------------------------------\n";
 }

 void economy::find(int key,vector<economy>& v){
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
void economy::update(int key,vector<economy>& v){
     bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].tour_detail.getId()==key){
            cout<<"\n----Enter new Details----\n";
            found=true;
            cin>>v[i];
            
        }
    }save(v);
    if(!found){
        cout<<"\n-----Such ID does not Exists.----\n";
    }
    
}   

void economy::load(vector<economy>& v) {
    ifstream fin;
    fin.open("economy.txt");
    if (!fin.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    
    string line;
    economy e;
    while (getline(fin, line)) {
        e.tour_detail.setName(line);
        getline(fin, line, '\t');
        e.cnic = stoi(line);
        getline(fin, line, '\t');
        e.tour_detail.setAge(stoi(line));
        getline(fin, line, '\t');
        e.price = stof(line);
        getline(fin, line,'\t');
        e.tour_detail.setId(stoi(line));
        getline(fin, line);
        e.guide_id=stoi(line);
        getline(fin, e.destination);
        getline(fin, e.departure);
        getline(fin, e.job);
        getline(fin, line, '\t');
        int people = stoi(line);
        getline(fin,line);
        int rooms = stoi(line);
        getline(fin, line);
        string detail = line;
        e.for_eco = new accomodation(people, rooms, detail);
        v.push_back(e);  
}  
    fin.close();

}

void economy::save(vector<economy>& v){
        ofstream fout;
        fout.open("economy.txt");
        for(int i=0;i<v.size();i++){
        fout<<v[i].tour_detail.getName()<<"\n"<<v[i].cnic<<"\t"<<v[i].tour_detail.getAge()<<"\t"<<v[i].price<<"\t"<<v[i].tour_detail.getId()<<"\t"<<v[i].guide_id<<"\n"<<v[i].destination<<"\n"<<v[i].departure<<"\n"<<v[i].job
        <<"\n"<<v[i].for_eco->getNoPeople()<<"\t"<<v[i].for_eco->getRooms()<<"\n"<<v[i].for_eco->getDetail()<<endl;
   }
   fout.close();
}

void economy::demolish(int key,vector<economy>& v){
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].tour_detail.getId()==key){
            cout<<"\n-----record deleted----\n";
            v.erase(v.begin()+i);
            found=true;
            
            
        }
    }save(v);
    if(!found){
        cout<<"\n----Such ID does not Exists.------\n";
    }
}