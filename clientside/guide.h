#pragma once
#include"detail.h"




class guide {
private:
    string experience;
    string language;
    float rating;
    detail guide_detail;//compostion

public:
    //constructore
    guide();
    guide(string ,string, float ,int , int, string );
    //setters and getters
    void setExperience(string );
    string getExperience();
    void setLanguage( string _language);
    string getLanguage();
    void setRating(float _rating);
    float getRating();
    string tostring();
    //functions
    static void menu();
    static void load(vector<guide>&);
    friend istream& operator>>(istream& in,guide &g);
    void display();
    void find(vector<guide>&,int);
    static void save(vector<guide>&);
    static void delete_guide(vector<guide>&,int);
    void update(vector<guide>&,int);
    static int select_guide();
    static string get_guide(long long int);
    

     
};

guide::guide() : experience(""), language(""), rating(0),guide_detail() {}

guide::guide(string _experience,string _language, float _rating,int _id, int _age, string _name): experience(_experience), language(_language), rating(_rating),guide_detail(_id,_age,_name) {}
        
void guide::menu() {
    vector<guide> vec;
    guide g;
    int opt;
    g.load(vec);
    while (true) {
        cout << "\n--------------------------------------------------\n";
        cout << "Press 1 to add an Entry.\nPress 2 to view all data.\nPress 3 to find specific Entry.\nPress 4 to update.\nPress 5 to delete.\nPress 6 to go back\n";
        cin >> opt;

        if (opt == 1) {
            cin >> g;
            vec.push_back(g);
            g.save(vec);
        } else if (opt == 2) {
            if(vec.size()==0){
                cout<<"\n---File is empty no recordes there---\n";
            }
            else{
                 for (int i = 0; i < vec.size(); i++) {
                vec[i].display();
            }
            }
           
        } else if (opt == 3) {
            cout << "Enter CNIC number:\n";
            cin >> opt;
            g.find(vec, opt);
        } else if (opt == 4) {
            cout << "Enter CNIC number:\n";
            cin >> opt;
            g.update(vec,opt);
        } else if (opt == 5) {
            cout << "Enter CNIC number:\n";
            cin >> opt;
            g.delete_guide(vec,opt);
        } else if (opt == 6) {
            return;
        }
    }
}


void guide::setExperience(string _experience) {
        experience = _experience;
    }

string guide::getExperience()  {
        return experience;
    }

void guide::setLanguage( string _language) {
        language = _language;
    }

string guide::getLanguage()  {
        return language;
    }

void guide::setRating(float _rating) {
        rating = _rating;
    }

float guide::getRating()  {
        return rating;
    }
string guide::tostring(){
    float rate=rating*10;
    return "NAME: " + guide_detail.getName()+"\tLANGUAGE: " +language+"\tEXPERIENCE: "+experience+"\tRATE: $"+to_string(rate);
}
void guide::save(vector<guide> &v){
        ofstream fout;
        fout.open("guide.txt");
        for(int i=0;i<v.size();i++)
        fout<<v[i].guide_detail.getId()<<"\t"<<v[i].guide_detail.getAge()<<"\n"<<v[i].guide_detail.getName()<<"\n"<<v[i].experience<<"\n"<<v[i].language<<"\n"<<v[i].rating<<endl;
        fout.close();
    }

 istream& operator>>(istream& in,guide &g){
        int id,age;
        string name;
        cout<<"Enter cnic:\n";
        in>>id;
        g.guide_detail.setId(id);
        cout<<"Enter age:\n";
        in>>age;
        g.guide_detail.setAge(age);
        cout<<"Enter Name:\n";
        getline(in>>ws,name);
        g.guide_detail.setName(name);
        cout<<"Enter Experience:\n";
        getline(in,g.experience);
        cout<<"Enter Language:\n";
        getline(in,g.language);
        cout<<"Enter rating:\n";
        in>>g.rating;
        in.ignore();

        cout<<"\nRECORD ADDED\n";
        return in;
    }

  void guide::display() {
    cout << "Name: " << guide_detail.getName() << endl;
        cout << "Age: " <<guide_detail.getAge() << endl;
        cout << "ID: " << guide_detail.getId() << endl;
        cout << "Experience: " << experience << endl;
        cout << "Language: " << language << endl;
        cout << "Rating: " <<rating<< endl;
    cout<<"-----------------------------------------------------\n";
}

void guide::find(vector<guide> &v,int key) {
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].guide_detail.getId()==key){
            cout<<"ID found\n";
            found=true;
            v[i].display();
        }
    }
    if(!found){
        cout<<"Such ID does not Exists.\n";
    }
    }


    void guide::load(vector<guide>& v) {
    ifstream fin("guide.txt");
    if (!fin.is_open()) {
        cout << "Error opening file!" << endl;
        return;
    }
    guide g;
    string name;
    int id, age;
    while (fin >> id >> age) {
        getline(fin>>ws, name);
        getline(fin, g.experience);
        getline(fin, g.language);
        fin >> g.rating;
        

        g.guide_detail.setAge(age);
        g.guide_detail.setId(id);
        g.guide_detail.setName(name);
        v.push_back(g);
    }
    fin.close();
}

void guide::delete_guide(vector<guide>& v,int key){
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].guide_detail.getId()==key){
            cout<<"record deleted\n";
            v.erase(v.begin()+i);
            found=true;
            
            
        }
    }save(v);
    if(!found){
        cout<<"Such ID does not Exists.\n";
    }
}

void guide::update(vector<guide>& v,int key){
    bool found=false;
    for(int i=0;i<v.size();i++){
        if(v[i].guide_detail.getId()==key){
            cout<<"Enter new Details\n";
            found=true;
            cin>>v[i];
            
        }
    }save(v);
    if(!found){
        cout<<"\n---Such ID does not Exists.\n";
    }
}

int guide::select_guide(){
    vector<guide> g;
    load(g);
    int i=1;
    for(int i=0;i<g.size();i++){
        cout<<i+1<<". "<<g[i].tostring()<<endl;
    }
    cout<<"Enter the number of guide person like 1,2 or etc\n";
    cin>>i;
    return g[i-1].guide_detail.getId();
}

string guide::get_guide(long long int id){
    vector<guide> g;
    load(g);
    string guide_detail;
    for(int i=0;i<g.size();i++){
        if(g[i].guide_detail.getId()==id){
            guide_detail=g[i].tostring();
            break;
        }
    }
    
    return guide_detail;
}