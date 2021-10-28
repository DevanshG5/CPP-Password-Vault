/*
Password Manager App:

Lets you store your passwords to various websites and apps locally.
*/

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

map <string, map <string, string>> domains;

void encrypt(){
    char ch;
    fstream temptxt, passtxt;
    passtxt.open("passwords.txt", fstream::out);
    temptxt.open("temp.txt", fstream::in);
    while(temptxt>>skipws>>ch){
        ch = ch+100;
        passtxt<<ch;
    }
    temptxt.close();
    passtxt.close();

    temptxt.open("temp.txt", fstream::out | ios::trunc);
    temptxt.close();
}

void decrypt(){
    char ch;
    ifstream passtxt;
    ofstream temptxt;
    temptxt.open("temp.txt");
    passtxt.open("passwords.txt");
    while(passtxt>>skipws>>ch){
        ch = ch-100;
        temptxt<<ch;
    }
    temptxt.close();
    passtxt.close();
}

void add(){ //adds elements to file as string
    cout<<"\nNOTE: The program is case sensitive.\nAbc is not the same as abc or ABC.\n";
    ofstream file ("temp.txt", ios::out | ios::app); //reads file
    if(file.is_open()){
        string domain, email, pass;
        cout<<"\nEnter the website/app or any other domain: ";
        cin>>domain;
        cout<<"Enter the email id/phone number/username: ";
        cin>>email;
        cout<<"Enter the password to be stored: ";
        cin>>pass;
        file<<domain<<":"<<email<<":"<<pass<<"\n";
        file.close();
        encrypt();
    }
    else{
        cout<<"Unable to access temp.txt";
    }
}

void view(){ //reads strings from the file, inserts them into a 2d map and prints the map
    ifstream file("temp.txt");
    if(file.is_open()){
        decrypt();
        string line;
        vector<string> elements;
        while(getline(file, line)) {
            stringstream ss(line);
            string tokens;
            while(getline(ss, tokens, ':')){
                elements.push_back(tokens);
            }
        }
        if(elements.size()==0){
            cout<<"No passwords saved.\n";
        }
        else{
            for(int i=0; i<elements.size()/3; ++i){
                domains.insert(make_pair(elements.at(i*3), map<string, string>()));
                domains[elements.at(i*3)].insert(make_pair(elements.at(i*3+1), elements.at(i*3+2)));
            }
            map <string, map <string, string>>::iterator outer;
            map <string, string>::iterator inner;
            for(outer=domains.begin(); outer != domains.end(); outer++ ){
                for(inner=outer->second.begin(); inner!=outer->second.end(); inner++){
                    cout<<outer->first<<" : ";
                    cout<<inner->first<<" :: "<<inner->second<<"\n";
                }
            }
        }
        file.close();
        encrypt();    
    }   
    else{
        cout<<"Unable to access temp.txt\n";
    }
}
    

/*void del(){                     //Problem: map::erase not working.
    ifstream file("temp.txt");
    if(file.is_open()){
        string line;
        vector<string> elements;
        while(getline(file, line)) {
            stringstream ss(line);
            string tokens;
            while(getline(ss, tokens, ':')){
                elements.push_back(tokens);
            }
        }
        if(elements.size()==0){
            cout<<"No passwords saved.\n";
        }
        else{
            for(int i=0; i<elements.size()/3; ++i){
                domains.insert(make_pair(elements.at(i*3), map<string, string>()));
                domains[elements.at(i*3)].insert(make_pair(elements.at(i*3+1), elements.at(i*3+2)));
            }
            map <string, map <string, string>>::iterator outer;
            map <string, string>::iterator inner;
            int value;
            cout<<"What do you wish to delete\n1. Entire domain\n2. A specific user in a domain\n3. A particular password of a user in a domain\nEnter the desired option: ";
            cin>>value;
            if (value==1){
                string key;
                for(outer=domains.begin(); outer != domains.end(); outer++ ){
                    for(inner=outer->second.begin(); inner!=outer->second.end(); inner++){
                        cout<<outer->first<<":";
                        cout<<inner->first<<" :: "<<inner->second<<"\n";
                    }
                }
                cout<<"\nEnter the domain to be deleted: ";
                cin>>key;
                map <string, map <string, string>>::iterator itr;
                itr=domains.find(key);
                if(itr!=domains.end()){
                    domains.erase(itr);
                }
                else{
                        cout<<"Invalid key";
                }  
                 
            }
        }
        file.close();
    }
    else{
        cout<<"Unable to access temp.txt\n";
    }
}*/

void search(){
    ifstream file("temp.txt");
    if(file.is_open()){
        decrypt();
        string line;
        vector<string> elements;
        while(getline(file, line)) {
            stringstream ss(line);
            string tokens;
            while(getline(ss, tokens, ':')){
                elements.push_back(tokens);
            }
        }
        if(elements.size()==0){
            cout<<"No passwords saved.\n";
        }
        else{
            for(int i=0; i<elements.size()/3; ++i){
                domains.insert(make_pair(elements.at(i*3), map<string, string>()));
                domains[elements.at(i*3)].insert(make_pair(elements.at(i*3+1), elements.at(i*3+2)));
            }
            map <string, map <string, string>>::iterator outer;
            map <string, string>::iterator inner;
            string domain,email;
            cout<<"Enter the domain: ";
            cin>>domain;
            outer=domains.find(domain);
            cout<<"Enter the email/username: ";
            cin>>email;
            inner=domains[domain].find(email);
            cout<<"\n"<<outer->first<<" : ";
            cout<<inner->first<<" :: "<<inner->second<<"\n";
        }
        file.close();
        encrypt();    
    }   
    else{
        cout<<"Unable to access temp.txt\n";
    }
}

void clear(){
    ofstream file("passwords.txt", ios::trunc);
    if(file.is_open()){
        file.close();
    }
    else{
        cout<<"Unable to access passwords.txt";
    }
    ofstream file1("temp.txt", ios::trunc);
    if(file1.is_open()){
        file1.close();
    }
    else{
        cout<<"Unable to access temp.txt";
    }
}

int main(){

    ofstream pass("passwords.txt");
    ofstream temp("temp.txt");
    int option;
    char a;
    do{
        cout<<"\n1. Add New Password\n2. View Existing Passwords\n3. Search for a specific password\n4. Clear Password List\n5. Exit Program\nPlease enter the desired option number ";
        cin>>option;
        switch(option){
            case 1:
                add();
                cout<<"\nPassword added successfully.\n";
                break;
            case 2:
                cout<<"\n";
                view();
                break;
            case 3:
                cout<<"\n";
                search();
                break;
            /*case 4:
                del();
                break;*/
            case 4:
                clear();
                cout<<"\nList cleared.\n";
                break;
            case 5:
                break;
            default:
                cout<<"\nPlease enter valid option.\n";
                break;
        }
        if(cin.fail()){
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }while(option!=5);

    return 0;
}