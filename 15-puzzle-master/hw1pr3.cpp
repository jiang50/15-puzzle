//Yucheng Jiang 525006053
//CSCE 420
//Due: Ocotber 2, 2017
//hw1pr3.cpp 
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <queue>
#include <unordered_set>
using namespace std;


vector<int> ed;//ending state
int states=0;

class Puzzle{
	public:
	Puzzle(vector<int> v):pz(v),prev(NULL),move(""){
		int index=0;
		for(int i:v){
			if(v[i]==0){
				zero=i;
				break;
			}
		}
	}
	vector<int> pz;
	Puzzle *prev;
	string move;
	int zero;
	void print();
	Puzzle* up();
	Puzzle* down();
	Puzzle* left();
	Puzzle* right();
	bool finish();
	Puzzle* search();
};

void Puzzle::print(){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cout<<pz[i*4+j]<<"\t";
		}
		cout<<endl;
	}
	cout<<endl;
}


Puzzle* Puzzle::up(){
	if(zero<=3)return NULL;
	vector<int> v=pz;
	v[zero]=v[zero-4];
	v[zero-4]=0;
	Puzzle* p=new Puzzle(v);
	p->prev=this;
	p->move="up";
	return p;
}

Puzzle* Puzzle::down(){
	if(zero>=12)return NULL;
	vector<int> v=pz;
	v[zero]=v[zero+4];
	v[zero+4]=0;
	Puzzle* p=new Puzzle(v);
	p->prev=this;
	p->move="down";
	return p;
}

Puzzle* Puzzle::left(){
	if(zero%4==0)return NULL;
	vector<int> v=pz;
	v[zero]=v[zero-1];
	v[zero-1]=0;
	Puzzle* p=new Puzzle(v);
	p->prev=this;
	p->move="left";
	return p;
}

Puzzle* Puzzle::right(){
	if(zero&4==3)return NULL;
	vector<int> v=pz;
	v[zero]=v[zero+1];
	v[zero+1]=0;
	Puzzle* p=new Puzzle(v);
	p->prev=this;
	p->move="right";
	return p;
}

bool Puzzle::finish(){
	for(int i=0;i<pz.size();i++){
		if(pz[i]!=ed[i])return false;
	}
	return true;
}

string make_key(vector<int> p){
	string result;
	for(int i:p){
		string temp=to_string(i);
		result+=i;
		result+=" ";
	}
	return result;
}

Puzzle* search(Puzzle* start){        //BFS
	queue<Puzzle*>q;
	unordered_set<std::string> myset;
	q.push(start);
	states++;
	myset.insert(make_key(start->pz));
	while(!q.empty()){
		int sz=q.size();
		for(int i=0;i<sz;i++){
			Puzzle* p=q.front();
			q.pop();
			Puzzle* left=p->left();
			if(left&&myset.count(make_key(left->pz))==0){				
				if(left->finish())return left;
				q.push(left);
				myset.insert(make_key(left->pz));
				states++;
				
			}
			Puzzle* right=p->right();
			if(right&&myset.count(make_key(right->pz))==0){				
				if(right->finish())return right;
				q.push(right);
				myset.insert(make_key(right->pz));
				states++;
			}
			Puzzle* up=p->up();
			if(up&&myset.count(make_key(up->pz))==0){				
				if(up->finish())return up;
				q.push(up);
				myset.insert(make_key(up->pz));
 				states++;
			}
			Puzzle* down=p->down();
			if(down&&myset.count(make_key(down->pz))==0){				
				if(down->finish())return down;
				q.push(down);
				myset.insert(make_key(down->pz));
				states++;
			}
		}
	}
	
}

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


int main(){
	string s,s1;
	cout<<"Enter 15-puzzle starting state by rows, 0 for blank(separate by comma):"<<endl;
	cin>>s;
	cout<<"Enter ending state by rows, 0 for blank(separate by comma):"<<endl;
	cin>>s1;
	stringstream sstr(s);
	int i;
	vector<int> v;
	while(sstr>>i){
		if(i<0||i>15)perror("Invalid input");
		v.push_back(i);
		if (sstr.peek() == ',')
           sstr.ignore();
	}
	int j;

	stringstream sst(s1);
	while(sst>>j){
		if(i<0||i>15)perror("Invalid input");
		ed.push_back(j);
		if (sst.peek() == ',')
           sst.ignore();
	}

	Puzzle* start=new Puzzle(v);
//	start->print();
//	if(start->finish())cout<<"success!"<<endl;
	if(start->left()->prev->finish())cout<<"success"<<endl;
	Puzzle* ending=search(start);
//	ending->print();
//	ending->prev->print();
//	cout<<ending->move<<endl;
	print_path(ending);
}



