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

void add(){ //adds elements to file as string
    cout<<"\nNOTE: The program is case sensitive.\nAbc is not the same as abc or ABC.\n";
    ofstream file ("passwords.txt", ios::out | ios::app); //reads file
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
    }
    else{
        cout<<"Unable to access passwords.txt";
    }
}
void view(){ //reads strings from the file, inserts them into a 2d map and prints the map
    ifstream file("passwords.txt");
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
            for(outer=domains.begin(); outer != domains.end(); outer++ ){
                for(inner=outer->second.begin(); inner!=outer->second.end(); inner++){
                    cout<<outer->first<<" : ";
                    cout<<inner->first<<" :: "<<inner->second<<"\n";
                }
            }
        }
        file.close();    
    }   
    else{
        cout<<"Unable to access passwords.txt\n";
    }
}
    

/*void del(){                     //Problem: map::erase not working.
    ifstream file("passwords.txt");
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
        cout<<"Unable to access passwords.txt\n";
    }
}*/

void search(){

    ifstream file("passwords.txt");
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
            string domain,email;
            cout<<"Enter the domain: ";
            cin>>domain;
            outer=domains.find(domain);
            cout<<"Enter the email/username: ";
            cin>>email;
            inner=domains[domain].find(email);
            cout<<outer->first<<" : ";
            cout<<inner->first<<" :: "<<inner->second;
        }
        file.close();    
    }   
    else{
        cout<<"Unable to access passwords.txt\n";
    }
}

int main(){

    int option;
    char a;
    do{
        cout<<"\n1. Add New Password\n2. View Existing Passwords\n3. Search for a specific password.\n4. Exit Program\nPlease enter the desired option number ";
        cin>>option;
        switch(option){
            case 1:
                add();
                break;
            case 2:
                view();
                break;
            case 3:
                search();
                break;
            /*case 3:
                del();
                break;*/
            case 4:
                break;
            default:
                cout<<"Please enter valid option.";
                break;
        }
        if(option==4){
            break;
        }
        while(a!='y' && a!='n'){cout<<"\nThe program has terminated.\nDo you wish to restart?(y/n)";
        cin>>a;
            if(a!='y' && a!='n'){
                cout<<"Invalid input. Please try again.";
            }
        }
    }while(a=='y');

    return 0;
}