#include <iostream>
#include "prolog.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	string filename;
	cout<<" * Enter the filename:"<<endl<<" * ";
	getline(cin,filename);
	cout<<" * File "<<filename<<" loading..."<<endl;
	Prolog p(filename);
	if(p.can_open()) cout<<" * Loaded sucessfully."<<endl;
	else{
		cout<<" * Thanks for using!"<<endl;
		return 0;
	}
	string cmd;
	do{
		cout<<" * Input consult to start."<<endl;
		cout<<" * ";
		getline(cin,cmd);
		if(cmd=="consult") {
			bool legal=p.report_legal();
			if(legal){
				p.saveToFile();
				cout<<" * check for facts! (input halt to stop) "<<endl;
				while(true){
					cout<<"-? ";
					string s;
					getline(cin,s);
					if(s=="halt.") {
						cout<<" * Thanks for using!"<<endl;
						return 0;
					} 
					cout<<p.check(s);
				}
			}
			else{
				cout<<" * Thanks for using!"<<endl;
				return 0;
			}
		} 
		if(cmd=="halt"){
			cout<<" * Thanks for using!"<<endl;
			return 0;
		}
	}while(true);
}
