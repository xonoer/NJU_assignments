#include "prolog.h"
using namespace std;

Prolog::Prolog(){
	lines.clear();
	list1.clear();
	list2.clear();
	errors.clear();
	can=false;
	num=0;
}

Prolog::Prolog(string filename){
	lines.clear();
	list1.clear();
	list2.clear();
	errors.clear();
	can=true;
	file=filename;
	num=0;
	FILE* pfile=fopen(filename.c_str(),"r");
	if(pfile==NULL){
		cout<<" * Error! Cannot open the file \""<<filename<<" \"."<<endl;
		can=false;
		return;
	}
	char ch[100];
	while(fgets(ch,100,pfile)){
		int i=0;
		while(ch[i]==' ') i++;
		if(ch[i]=='\0') continue;
		Sentence sen;
		sen.line=++num;
		bool atom_exist=false;
		
		do{
			while(ch[i]==' ') i++;
			// note
			if(ch[i]=='/'&&ch[i+1]=='*'){
				int j;
				bool val=false;
				for(j=i+2;ch[j+1]!='\0';j++){
					if(ch[j]=='*'&&ch[j+1]=='/'){
						val=true;
						break;
					}
				}
				if(val){
					string note;
					for(int k=i;k<=j+1;k++) note+=ch[k];
					Token new1;
					new1.word=note;
					new1.type=Note;
					sen.parts.push_back(new1);
					i=j+2;
					continue;
				}
			}
			// atom or const
			if(ch[i]>='a'&&ch[i]<='z'){
				Token new2;
				int j=i;
				while((ch[j]>='a'&&ch[j]<='z')||(ch[j]>='A'&&ch[j]<='Z')||(ch[j]>='0'&&ch[j]<='9')||ch[j]=='_'){
					j++;
				}
				string word1;
				for(int k=i;k<=j-1;k++) word1+=ch[k];
				new2.word=word1;
				if(atom_exist) new2.type=Const;
				else{
					new2.type=Atom;
					atom_exist=true;
				}
				sen.parts.push_back(new2);
				i=j;
				continue;
			}
			// variable
			if(ch[i]>='A'&&ch[i]<='Z'){
				Token new3;
				int j=i;
				while((ch[j]>='a'&&ch[j]<='z')||(ch[j]>='A'&&ch[j]<='Z')||(ch[j]>='0'&&ch[j]<='9')||ch[j]=='_'){
					j++;
				}
				string word2;
				for(int k=i;k<=j-1;k++) word2+=ch[k];
				new3.word=word2;
				new3.type=Variable;
				sen.parts.push_back(new3);
				i=j;
				continue;
			}
			//symbol
			if(ch[i]=='('||ch[i]==')'||ch[i]==','||ch[i]=='.'){
				Token new4;
				new4.word.clear();
				new4.word+=ch[i];
				new4.type=Symbol;
				sen.parts.push_back(new4);
				if(ch[i]=='(') atom_exist = true;
				if(ch[i]==')') atom_exist = false;
				i++;
				continue;
			}
			if(ch[i]==':'&&ch[i+1]=='-'){
				Token new5;
				new5.word.clear();
				new5.word+=ch[i];
				new5.word+=ch[i+1];
				new5.type=Symbol;
				sen.parts.push_back(new5);
				i+=2;
				atom_exist=false;
				continue;
			}
			//invalid
			else{/*
				int j=i;
				string word3;
				while((ch[j]<'A'||ch[j]>'Z')&&
					(ch[j]<'a'||ch[j]>'z')&&
					(!(ch[j]=='/'&&ch[j+1]=='*'))&&
					ch[j]!='('&&ch[j]!=')'&&ch[j]!=','&&ch[j]!='.'&&ch[j]!='_'&&ch[j]!=' '&&ch[j]!='\0'&&
					(!(ch[j]==':'&&ch[j+1]=='-'))) j++;
				for(int k=i;k<=j-1;k++) word3+=ch[j];
				Token new6;
				new6.word=word3;
				new6.type=None;
				new6.valid=false;
				sen.parts.push_back(new6);
				i=j;
				continue;*/
				Token new6;
				new6.word+=ch[i];
				new6.type=None;
				new6.valid=false;
				if(new6.word!="\0"&&new6.word!="\n"&&new6.word!="\r") 
				sen.parts.push_back(new6);
				i++;
				continue;
			}
		}while(ch[i]!='\0'&&ch[i]!='\n');
		lines.push_back(sen);
	}
} 

bool Prolog::has_error(){
	bool error = false;
	for(int i=0;i<num;i++){
		if(error_check(lines[i])) error=true;
	}
	return error;
} 

bool Prolog::error_check(Sentence a){
	bool error = false;
	bool atom_exist = false;
	bool rule_defined = false;
	int RDposition = -1;
	int line_num = a.line;
	int token_num = a.parts.size();
	string error_type_t = " * Line ";
	error_type_t+=to_string(line_num);
	error_type_t+=": ";
	string error_type;
	//check fact or rule
	for(int i=0;i<token_num;i++){
		if(a.parts[i].word==":-"&&rule_defined){
			error = true;
			error_type += error_type_t;
			error_type += "Cannot use more than one \":-\" in a rule definition.\n";
			RDposition = -1;
		}
		else if(a.parts[i].word==":-"&&(!rule_defined)){
			rule_defined = true;
			RDposition = i;
		}
	}
	//word type error 1 (invalid type of word)
	for(int i=0;i<token_num;i++){
		if(a.parts[i].type==None||a.parts[i].valid==false){
			error = true;
			error_type += error_type_t;
			error_type += "Invalid symbol input: \"";
			error_type += a.parts[i].word;
			error_type += "\".\n";
		}
	}
	//delete invalid symbols and notes
	for(int i=0;i<token_num;i++){
		if(a.parts[i].type==Note||a.parts[i].type==None){
			a.parts.erase(a.parts.begin()+i,a.parts.begin()+i+1);
			i--;
			token_num--;
			 
		}
	}
	if(a.parts.empty()) return error;
	//word type error 2 (variable in the head)
	if(a.parts[0].type!=Atom){
		error = true;
		error_type += error_type_t;
		if(a.parts[0].type==Variable) error_type += "Variable \"";
		else error_type += "Symbol \"";
		error_type += a.parts[0].word;
		error_type += "\" expected to be an atom.\n";
	}
	if(RDposition!=-1){
		if(a.parts[RDposition+1].type!=Atom){
			error = true;
			error_type += error_type_t;
			if(a.parts[RDposition+1].type==Variable) error_type += "Variable \"";
			else error_type += "Symbol \"";
			error_type += a.parts[RDposition+1].word;
			error_type += "\" cannot be put in the title\n";
		}
	}
	//grammer check 1: undefined atoms
	for(int i=0;i<token_num;i++){
		if(a.parts[i].type==Atom){
			if(i+1==token_num||a.parts[i+1].word!="("){
				error = true;
				error_type += error_type_t;
				error_type += "Atom \"";
				error_type += a.parts[i].word;
				error_type += "\" lack of definition.\n";
			}
		}
	}
	//grammer check 2: "(" & ")" and words between () and definitions
	for(int i=0;i<token_num;i++){
		if(a.parts[i].word=="("){
			int j;
			for(j=i+1;j<token_num;j++){
				if(a.parts[j].type==Variable&&!rule_defined){ //Variables in facts
					error = true;
					error_type += error_type_t;
					error_type += "Variable \"";
					error_type += a.parts[j].word;
					error_type += "\" cannot be put in a fact.\n";
				}
				if(a.parts[j].type==Const||a.parts[j].type==Variable){
					if(a.parts[j+1].type==Const||a.parts[j+1].type==Variable){ //lack of ","
						error = true;
						error_type += error_type_t;
						error_type += "Symbol \",\" expected between \"";
						error_type += a.parts[j].word;
						error_type += "\" and \"";
						error_type += a.parts[j+1].word;
						error_type += "\".\n";
					}
				}
				if(a.parts[j].type==Symbol&&a.parts[j].word!=","&&a.parts[j].word!=")"&&a.parts[j].word!="."){ //invalid symbol
					error = true;
					error_type += error_type_t;
					error_type += "Symbol \"";
					error_type += a.parts[j].word;
					error_type += "\" not expected in definition.\n";
				}
				if(a.parts[j].word=="."&&j!=token_num-1){
					error = true;
					error_type += error_type_t;
					error_type += "Symbol \"";
					error_type += a.parts[j].word;
					error_type += "\" not expected in definition.\n";
				}
				if(a.parts[j].word==","){ //seperate two words
					if(a.parts[j+1].type!=Const&&a.parts[j+1].type!=Variable){
						error = true;
						error_type += error_type_t;
						error_type += "Undefined use of Symbol \",\".\n";
					}
				}
				if(a.parts[j].word==")"){ //end of definition
					i=j;
					break;
				}
			}
			if(j==token_num){ //"(" unmatched
				error = true;
				error_type += error_type_t;
				error_type += "Symbol \"(\" is unmatched.\n";
				i=j;
			}
		}
		if(i==token_num) break;
		if(a.parts[i].word==")"&&i+1<token_num-1){
			if(a.parts[i+1].word!=","&&a.parts[i+1].word!=":-"){
				if(a.parts[i+1].type==Atom){
					error = true;
					error_type += error_type_t;
					error_type += "Symbol \",\" expected before the definition of \"";
					error_type += a.parts[i+1].word;
					error_type += "\".\n";
				}
				else{
					error = true;
					error_type += error_type_t;
					error_type += "Undefined use of Symbol \"";
					error_type += a.parts[i+1].word;
					error_type += "\".\n";
				}
			}
			if(a.parts[i+1].word==","&&!rule_defined){
				error = true;
				error_type += error_type_t;
				error_type += "Symbol \",\" expected in definition of rules. Try Symbol \":-\".\n";
			}
		}
		
	}
	//grammer check 3: lack of "."
	if(a.parts[token_num-1].word!="."){
		error = true;
		error_type += error_type_t;
		error_type += "Symbol \".\" expected at the end of the line.\n";
		
	}
	
	if(error){
		errors.push_back(error_type);
		return true;
	}
	else {
		if(!rule_defined){
			Fact f;
			f.name.clear();
			f.atom=a.parts[0].word;
			for(int i=1;i<token_num;i++){
				if(a.parts[i].type==Const){
					Token name;
					name.type=Const;
					name.word=a.parts[i].word;
					f.name.push_back(name);
				}
			}
			list1.push_back(f);
		}
		if(rule_defined){
			Rule r;
			r.def.clear();
			r.atom=a.parts[0].word;
			for(int i=0;i<token_num;i++){
				if(a.parts[i].type==Atom){
					Fact ff;
					ff.atom=a.parts[i].word;
					int j;
					for(j=i+1;j<token_num;j++){
						if(a.parts[j].word==")"){
							r.def.push_back(ff);
							i=j+1;
							break;
						}
						if(a.parts[j].type==Const||a.parts[j].type==Variable){
							Token t;
							t.type=a.parts[j].type;
							t.word=a.parts[j].word;
							ff.name.push_back(t);
						}
					}
				}
			}
			list2.push_back(r);
		}
		return false;
	}
}

bool Prolog::report_legal(){
	bool error = has_error();
	if(num==0) return false;
	if(!error){
		cout<<" * Done!"<<endl;
		return true;
	}
	cout<<" * Failed to interprete \""<<file<<"\"!"<<endl;
	int error_num = errors.size();
	for(int i=0;i<error_num;i++){
		cout<<errors[i];
	}
	return false;
} 

string Prolog::check(string s){
	Fact f;
	int num=s.length();
	string input;
	int i=0;
	while(s[i]==' ') i++;
	if(s[i]<'a'||s[i]>'z'){
		return " * Error! Invalid input! (1)\n";
	}
	//get atom
	for(;i<num;i++){
		if(isLegallyNamed(s[i])) input+=s[i];
		else break;
	}
	if(i==num) return " * Error! Invalid input! (2)\n";
	f.atom=input;
	//cout<<"Atom: "<<input<<endl;//test
	while(s[i]==' ') i++;
	if(s[i]!='('){
		return " * Error! Invalid input! (3)\n";
	}
	else i++;
	//get others 
	do{
		while(s[i]==' ') i++;
		if(s[i]==')') break;
		if(!f.name.empty()){
			if(s[i]!=',') return " * Error! Invalid input! (4)\n";
			else {
				i++;
				while(s[i]==' ') i++;
			}
		}
		while(s[i]==' ') i++;
		if((s[i]<'A'||s[i]>'Z')&&(s[i]<'a'||s[i]>'z')){
			return " * Error! Invalid input! (5)\n";
		}
		input.clear();
		Token t;
		if(s[i]>='A'&&s[i]<='Z') t.type=Variable;
		else t.type=Const;
		while(isLegallyNamed(s[i])) {
			input+=s[i];
			i++;
		}
		//cout<<s[i]<<" "<<i<<endl;
		t.word=input;
		f.name.push_back(t);
	//	cout<<"word: "<<t.word<<"  type:"<<trans_type(t.type)<<endl;
	}while(i<num);
	if(i==num) return " * Error! Invalid input! (6)\n";
	while(s[i]==' ') i++;
	if(s[i]!=')') return " * Error! Invalid input! (7)\n";
	else i++;
	while(s[i]==' ') i++;
	if(s[i]!='.') return " * Error! Invalid input! (8)\n";
	//test

	return search(f);
}

string Prolog::search(Fact f){
	if(!hasVariable(f)){
		bool found = false;
		int num1=list1.size();
		for(int i=0;i<num;i++){
			if(list1[i].name.size()!=f.name.size()) continue;
			if(list1[i].atom!=f.atom) continue;
			int j;
			for(j=0;j<f.name.size();j++){
				if(list1[i].name[j].word!=f.name[j].word) break;
			}
			if(j==f.name.size()) found=true;
		}
		if(found) return "true.\n";
		else return "false.\n";
	} 
	else{
		string result;
		bool found = false;
		int num2=list1.size();
		for(int i=0;i<num;i++){
			if(list1[i].name.size()!=f.name.size()) continue;
			if(list1[i].atom!=f.atom) continue;
			int j;
			for(j=0;j<f.name.size();j++){
				if(f.name[j].type==Const&&f.name[j].word!=list1[i].name[j].word) break;
			}
			if(j==f.name.size()){
				for(int k=0;k<f.name.size();k++){
					if(f.name[k].type==Variable){
						string ans;
						ans+=f.name[k].word;
						ans+=" = ";
						ans+=list1[i].name[k].word;
						ans+=", ";
						result+=ans;
					}
				}
				result+='\n';
				found=true;
			}
		}
		if(found) return result;
		else return "Not Found.\n";
	}
}

void Prolog::test_token(){
	int n=lines.size();
	for(int i=0;i<n;i++){
		Sentence a=lines[i];
		cout<<"line "<<a.line<<endl;
		int m=a.parts.size();
		for(int j=0;j<m;j++){
			Token b=a.parts[j];
			cout<<setw(20)<<b.word<<'\t'<<trans_type(b.type)<<endl;
		}
	}
}

string Prolog::trans_type(Type p){
	switch(p){
		case(None): return "None";
		case(Atom): return "Atom";
		case(Const): return "Const";
		case(Variable): return "Variable";
		case(Symbol): return "Symbol";
		case(Note): return "Note";
		default: return "\0";
	}
}

void Prolog::output1(){
	int num=list1.size();
	for(int i=0;i<num;i++){
		cout<<list1[i].atom<<"(";
		for(int j=0;j<list1[i].name.size();j++){
			cout<<list1[i].name[j].word;
			if(j!=list1[i].name.size()-1) cout<<",";
		}
		cout<<").\n";
	}
}

void Prolog::output2(){
	int num=list2.size();
	for(int i=0;i<num;i++){
		for(int j=0;j<list2[i].def.size();j++){
			cout<<list2[i].def[j].atom<<"(";
			for(int k=0;k<list2[i].def[j].name.size();k++){
				cout<<list2[i].def[j].name[k].word;
				if(k!=list2[i].def[j].name.size()-1) cout<<",";
			}
			cout<<")";
			if(j==0) cout<<":-";
			else if(j<list2[i].def.size()-1) cout<<",";
		}
		cout<<".\n";
		
	}
}

bool Prolog::isLegallyNamed(char s){
	return ((s>='a'&&s<='z')||(s>='A'&&s<='Z')||(s>='0'&&s<='9')||s=='_');
}

bool Prolog::can_open(){
	return can;
}

bool Prolog::hasVariable(Fact f){
	int num=f.name.size();
	for(int i=0;i<num;i++){
		if(f.name[i].type==Variable) return true; 
	} 
	return false;
}

void Prolog::saveToFile(){
	string name="token.txt";
	FILE* pfile = fopen(name.c_str(),"a");
	fputs("----------\n",pfile);
	fputs(file.c_str(),pfile);
	fputs("\n",pfile);
	for(int i=0;i<num;i++){
		string str="*Line ";
		str += to_string(lines[i].line);
		str += "\n";
		fputs(str.c_str(),pfile);
		for(int j=0;j<lines[i].parts.size();j++){
			string strr = " ";
			strr+=lines[i].parts[j].word;
			strr+='\t';
			strr+=trans_type(lines[i].parts[j].type);
			strr+='\n';
			fputs(strr.c_str(),pfile);
		}
	}
	fclose(pfile);
} 

bool Prolog::has_atom(string s){
	for(int i=0;i<list1.size();i++){
		if(list1[i].atom==s) return true;
	}
	return false;
}



Prolog::~Prolog(){
	lines.clear();
	list1.clear();
	list2.clear();
	errors.clear();
	num=0;
}
