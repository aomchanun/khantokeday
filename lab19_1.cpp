#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream data;
    data.open(filename.c_str());
    string s;
    while(getline(data,s))
    {
        const char *text = s.c_str();
        char format[] = "%[^:]: %d %d %d";
        char name[100];
        int a,b,c;
        sscanf(text,format,name,&a,&b,&c);
        int sum = a+b+c;
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
    data.close();
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    string textline;
    getline(cin,textline);
    const char *text = textline.c_str();
    char commandn[100],keyn[100];
    char format[] = "%[^ ] %[abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ. ]";
    sscanf(text,format,commandn,keyn);
    command = commandn;
    key = keyn;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------" << endl;
    for(unsigned int i=0; i<names.size() ;i++)
    {
        if(toUpperStr(names[i]) == key)
        {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------" << endl;

        }
    }
    cout << "Cannot found." << endl;
    
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------" << endl;
    bool found = false;
    for(unsigned int i=0; i<names.size() ;i++)
    {
        if(grades[i] == key.c_str()[0])
        {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            found = true;
            
        }
    }
    if(!found) cout << "Cannot found." << endl;
    cout << "---------------------------------";

}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    

    return 0;
}
