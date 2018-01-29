//Yucheng Jiang 525006053
//CSCE 420
//Due: Ocotber 2, 2017
//hw1pr4.cpp 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <queue>
#include <map>
#include <unordered_set>
using namespace std;


vector<int> ans;//ending state
int states=0;
vector<int> input;

class puzzle{ 
    public: 
    string state;  
    string path;  
    int    step;  
    int    h;  
    bool operator < (const puzzle &n) const  
    {  
        return h + step > n.h + n.step;  
    }  
    puzzle(string State, string Path, int Step, int H) {  
        state = State;  
        path  = Path;  
        step  = Step;  
        h     = H;  
    }  
};  
  
string array_to_string(vector<int> data)  
{  
    string str = "123456789abcdef0";  
    for (int i = 0; i < 16; ++ i) {  
        str[i] = data[i] + '0';  
    }  
    return str;  
}  
  
vector<int> target = {15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};  
int get_h(string state)  
{  
    int count = 0, place[16];  
    for (int i = 0; i < 16; ++ i) {  
        place[state[i]-'0'] = i;  
    }  
    for (int i = 0; i < 16; ++ i) {  
        count += abs(place[i]%4 - target[i]%4) + abs(place[i]/4 - target[i]/4);  
    }  
    return count;  
}  
  
int get_zero_index(string state)  
{  
    for (int i = 0; i < 16; ++ i) {  
        if (state[i] == '0') {  
            return i;  
        }  
    }  
    return -1;  
}  
 
void print_path(string s){
	for(char i:s){
		if(i=='L')cout<<"swap the blank left"<<endl;
		else if(i=='U')cout<<"swap the blank up" <<endl;
		else if(i=='R')cout<<"swap the blank right" <<endl;
		else if(i=='D')cout<<"swap the blank down" <<endl;
		
	}
}

 
char move_step[4] = {'D', 'R', 'U', 'L'};  
int  dxy[4][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}};  
int  A_star(vector<int> start, vector<int> over)  
{  
    string s_state = array_to_string(start);  
    string e_state = array_to_string(over);        
    map <string, int> M;  
    M[s_state] = 1;  
      
    priority_queue <puzzle> Q;  
    Q.push(puzzle(s_state, "", 0, get_h(s_state)));   
    while (!Q.empty()) {  
        puzzle now = Q.top(); Q.pop();  
        if (now.step > 50) {  
            continue;  
        }  
        if (now.state == e_state) {  
            print_path(now.path);  
            return 0;  
        }  
        int index = get_zero_index(now.state);  
        int x = index/4, y = index%4;  
        for (int k = 0; k < 4; ++ k) {  
            int xx = x + dxy[k][0];  
            int yy = y + dxy[k][1];  
            if (xx >= 0 && xx < 4 && yy >= 0 && yy < 4) {  
                string new_state = now.state;  
                swap(new_state[index], new_state[xx*4+yy]);  
                if (!M[new_state]) {  
                    M[new_state] = 1;  
					states++;
                    Q.push(puzzle(new_state, now.path + move_step[k], now.step + 1, get_h(new_state)));  
                }  
            }  
        }  
    }  
    return -1;  
}  



/*
void print_path(Puzzle* p){
	cout<<"Solution: "<<endl;
	vector<Puzzle*> v;
	v.push_back(p);
	while(p->prev){
		p=p->prev;
		v.push_back(p);
	}
	for(int i=v.size()-1;i>=0;i--){
		if(v[i]->move=="")cout<<"Start: "<<endl;
		else{
			cout<<"Swap the blank "<<v[i]->move<<":"<<endl;
		}
		v[i]->print();
		
	}
	cout<<"Done! "<<"Generated "<<states<<" states."<<endl;
}

*/
int main(){
	string s,s1;
	cout<<"Enter 15-puzzle starting state by rows, 0 for blank(separate by comma):"<<endl;
	cin>>s;
	cout<<"Enter ending state by rows, 0 for blank(separate by comma):"<<endl;
	cin>>s1;
	stringstream sstr(s);
	int i;

	while(sstr>>i){
		if(i<0||i>15)perror("Invalid input");
		input.push_back(i);
		if (sstr.peek() == ',')
           sstr.ignore();
	}
	int j;

	stringstream sst(s1);
	while(sst>>j){
		if(i<0||i>15)perror("Invalid input");
		ans.push_back(j);
		if (sst.peek() == ',')
           sst.ignore();
	}

//	Puzzle* start=new Puzzle(input);
	
	A_star(input,ans);
	cout<<"Done! Generated "<<states<<" states"<<endl;


}
