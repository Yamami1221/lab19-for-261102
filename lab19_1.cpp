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

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source;
    source.open(filename);
    string textline;
    char format[] = "%[^:]: %d %d %d";
    string name;
    char cname[100];
    int score1, score2, score3, scoreSum;
    char grade;
    while (getline(source,textline)){
        sscanf(textline.c_str(),format,cname,&score1,&score2,&score3);
        name = cname;
        scoreSum = score1 + score2 + score3;
        grade = score2grade(scoreSum);
        names.push_back(name);
        scores.push_back(scoreSum);
        grades.push_back(grade);
    }
    source.close();
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    getline(cin,command);
    int i = command.find_first_of(" ");
    key = command.substr(i+1);
    command = command.substr(0,i);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(grades[i] == key[0]){
            cout << names[i] << " (" << scores[i] << ")" << endl;
        }
    }
    cout << "---------------------------------\n";
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
