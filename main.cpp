// BK.cpp: определяет точку входа для консольного приложения.
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <locale>
#include <filesystem>
#include <map>
#include <vector>
using namespace std;

class CowBulls{
	public:
	int i,K,B,N;//коровы и быки/ количество попыток
	string in,nums;
	//размер слова временно статичен и равен 5
	//загадываем слово
	//возможность выбрать - числа/слова/цвета

    //конструктор класса
	//CowBulls(){K=0;B=0;N=0;}
        int play(){//добавить srand(что бы при каждом запуске случайные числа рил были случайныи)
		K=0;B=0;N=0;nums="";
		for(int n=0;n<5;n++){
			do{ i=rand()%9;
			}while(nums.find(i+'0')!=-1);
			nums+=i+'0';
		}
		while (B!=5){N++;//if(exit/out/end)
			getline(cin, in);
			if(in=="end"){return 0;}
			K=0;B=0;
			for(int n=0;n<in.size();n++){
				char b=in.at(n);
				if(nums.find(b)==n)B++;
				else if(nums.find(b)!=-1)K++;
			}
			cout<<"Cows_"<<K<<" Bulls_"<<B<<endl;
		}
		return N;
	}
	void start(){
		in="yes";
		while (in.at(0)=='y'){
			cout<<"I create number. Enter your first guess"<<endl;
			N=play();
			if (N!=0)cout<<"YOU WIN!!!\n"<<"In "<<N<<" try."<<endl;
			cout<<"Whanna play again? > ";
			getline(cin, in);
		}
	}
};

struct WAY{
	string name, n;
	int obj;
	void Create(string s){
		//if(s.at(0)=='['){obj=stoi(&s.at(1),0,10);}else{obj==NULL;}

		name=s.substr(0,s.find("(")); 
		n=s.substr(s.find("(")+1);
		n.erase( n.find(")") );
	}
	//void clear(){name="";n="";}
};

class Story{
	public:
		bool obj[2];
	map<string, string> m_story;
	//map<string, vector<string>> m_way;
	map<string, vector<WAY>> m_way;
	Story(){//создает массив истории
		memset(&obj,false,sizeof(obj));
		string s,s_T,s_N;int n;
		//vector<string>ways;
		vector<WAY>ways;WAY W;
		ifstream in("story.txt");
		if(in.is_open()){ 
			while (getline(in, s)){
 				n=s.find("#");
				s_N=s.substr(0,n);//num of scene
				s=s.substr(n+1,s.size()-1);
				n=s.find("#");
				s_T=s.substr(0,n);//text of scene
				s=s.substr(n+1,s.size()-1);
				n=s.find("#");
				m_story.insert(make_pair(s_N,s_T));
				ways.clear();
				while(n!=-1){
					W.Create(s.substr(0,n));
					ways.push_back(W);
					//ways.push_back(s.substr(0,n));
					s=s.substr(n+1, s.size()-1);
					n=s.find("#");
				}
				m_way.insert(make_pair(s_N, ways));
			}
		}
	}
	string show(string s){
		vector<WAY>ways;
		cout<<m_story.at(s)<<endl;
		ways=m_way.at(s);
		s.clear();
  		if(ways.size()==0){ return "end";}
		else if(ways.size()==1){return ways.at(0).n;}
		for(int i=0;i<ways.size();i++){
			s=ways.at(i).name;
			//if(s.at(0)=='[' && !obj[0]){continue;}else
			cout<<i<<" "<<ways.at(i).name<<"/ ";
		}
		cout<<endl;
		getline(cin, s);
		s=ways.at(stoi(s,0,10)).n;
		if(s=="10")obj[0]=true;
		return s;
	}
	void start(){
		string s;
		s="1";
		do{
			s=show(s);
			//getline(cin,s);
		}while(s!="end");
	}
	void goTo(){}
};

class XO{
public:
string pole[9];
string all_pos;
string win[8];
XO(){
win[0]="012";
win[1]="345";
win[2]="678";
win[3]="036";
win[4]="147";
win[5]="258";
win[6]="048";
win[7]="246";
}
void clearPole(){
pole[0]="   |   |   \n";
pole[1]="   |   |   \n";
pole[2]="___|___|___\n";
pole[3]="   |   |   \n";
pole[4]="   |   |   \n";
pole[5]="___|___|___\n";
pole[6]="   |   |   \n";
pole[7]="   |   |   \n";
pole[8]="   |   |   \n";}
void setPos(int i, char fig){
	switch(i){
	case 0:pole[1].at(1)=fig;break;
	case 1:pole[1].at(5)=fig;break;
	case 2:pole[1].at(9)=fig;break;
	case 3:pole[4].at(1)=fig;break;
	case 4:pole[4].at(5)=fig;break;
	case 5:pole[4].at(9)=fig;break;
	case 6:pole[7].at(1)=fig;break;
	case 7:pole[7].at(5)=fig;break;
	case 8:pole[7].at(9)=fig;break;
	}
}
void start(){
	string s="yes";
	while(s.at(0)=='y'){
		clearPole();
		all_pos="012345678";
		cout<<"How many players?(1/2)"<<endl;
		getline(cin,s);
		if(s=="1") onePlr(); else twoPlr();
		cout<<"Whana play again?"<<endl;
		getline(cin,s);/**/
	}
}
void onePlr(){
	string s="";int n;bool m=true,win;
	string moves1="", moves2="";

	while(s!="end"){
		
		system("cls");
		for(int i=0;i<9;i++){
			cout<<pole[i];
		}
		if(all_pos==""){cout<<"No more moves"<<endl;break;}
		cout<<"Enter position: \n0|1|2\n3|4|5\n6|7|8\n";
		getline(cin,s);
		n=all_pos.find(s);
		if(n!=-1)all_pos.erase(n,1); else{ cout<<"You can't put figure there\n";continue;}
		
		if(m){
			setPos(stoi(s,0,10),'X');
			moves1+=s;
			m=0;
			if(chekWin(moves1)){cout<<"congrats, X !! You WIN!!! \n";all_pos="";}
		} else {
			setPos(stoi(s,0,10),'O');
			moves2+=s;
			m=1;
			if(chekWin(moves2)){cout<<"congrats, O !! You WIN!!! \n";all_pos="";}
		}
	}
}
void twoPlr(){
	string s="";bool m=true,win;int n;
	string moves1="", moves2="";
	while(s!="end"){
		
		system("cls");
		for(int i=0;i<9;i++){
			cout<<pole[i];
		}
		if(all_pos==""){cout<<"No more moves"<<endl;break;}
		cout<<"Enter position: \n0|1|2\n3|4|5\n6|7|8\n";
		getline(cin,s);
		n=all_pos.find(s);
		if(n!=-1)all_pos.erase(n,1); else{ cout<<"You can't put figure there\n";continue;}
		
		if(m){
			setPos(stoi(s,0,10),'X');
			moves1+=s;
			m=0;
			if(chekWin(moves1)){cout<<"congrats, X !! You WIN!!! \n";all_pos="";}
		} else {
			setPos(stoi(s,0,10),'O');
			moves2+=s;
			m=1;
			if(chekWin(moves2)){cout<<"congrats, O !! You WIN!!! \n";all_pos="";}
		}
	}
}

bool chekWin(string s){int k=0;
	if(s.size()<3)return false;
	for(int i=0;i<8;i++){
		k=0;
		for(int j=0;j<3;j++){
			if(s.find(win[i].at(j))==-1)break;
			//if(win[i].find(s.at(j))==-1)break;
			else k++;
		}
		if(k==3)return true;
	}
	return false;
}

};

class fifth{
public:
	string pole, blocks[16];//(поле) и (набор цифр) для вывода картинки
	int poss[4][4],right_poss[4][4];//текущие позиции цифр и правильные позиции цифр

	fifth(){
		right_poss[4][4] = ((1,2,3,4),(5,6,7,8),(9,10,11,12),(13,14,15,0));//верная(финальная) последовательность
		blocks[0]="  ";
		for(int i=1;i<16;i++){if(i<10)blocks[i]=" "+to_string(i);else blocks[i]=to_string(i);}
		//blocks[16]={"  "," 1"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10","11","12","13","14","15"};
		clearPole();
	}
	void clearPole(){//очистка и создание стартового поля
		int k,n=0;pole="";
		for(int i=0; i<4;i++){//we create seq of numBlocks
			pole+="|";
			for(int j=0;j<4;j++){
				do{k=rand()%16; }while(chekPos(poss,k));//gener random pole
				poss[i][j]=k;
				pole+=blocks[k]+"|";//create start pole
				if(n==3){n=0; pole+="\n";}else n++;
			}
		}
	}

	bool chekPos(int mas[4][4], int i){
		for(int n=0;n<4;n++){
			for(int m=0;m<4;m++){
				if(mas[n][m]==i)return true;//already have this number
			}
		}
		return false;
	}

	string avblPos(){
		string s=""; bool t=false;int n,m;
		for(n=0;n<4;n++){
			for(m=0;m<4;m++){
				if(poss[n][m]==0){t=true;break;}
			}
			if(t)break;
		}
		if(n!=0)s+=blocks[poss[n-1][m]];// ^
		if(m!=0)s+=blocks[poss[n][m-1]];// <
		if(n!=3)s+=blocks[poss[n+1][m]];// v
		if(m!=3)s+=blocks[poss[n][m+1]];// >
		return s;
	}

	void switchPos(int pos){
		int n0,m0;
		for(int n=0;n<4;n++){
			for(int m=0;m<4;m++){
				if(poss[n][m]==0){n0=n;m0=m;}
				if(poss[n][m]==pos){poss[n][m]=0;}
			}
		}
		poss[n0][m0]=pos;
	}

	void start(){
		string in="yes";
		while(in!="end"){
			system("cls");
			if(poss[4][4]==right_poss[4][4]){cout<<"Great Job!!! You solve the task\n Whanna play again? ";}
			else cout<<pole<<"Moving...";
			getline(cin,in);
			if(in.empty())continue;
			if(in.size()==1)in.insert(0," ");
			play(in);
		}
	}

	void play(string in){
		string s="";
		int i=stoi(in,0,10);
		int n,m;
		s=avblPos();
		if(i>15 || s.find(in)==-1)cout<<"Try another \n";//убирается, почекать как оставить
		else {
			n= pole.find("  ");
			m= pole.find(in);
			pole.replace(n,2,in);
			pole.replace(m,2,"  ");
			switchPos(i);
		}
	}
};

class SeaWar{
	string pole;
	string ships[10];//[0]x4;[1,2]x3;[3:5]x2;[6:9]x1
	int inj_ship[10];
	int wrecks;
	/*поменять местами названия батл и вражеское поле...*/
	int battle[10][10];//my_pole
	string/* [_][x][o]*/enemy_pole[10][10];//угадываем чужое -> попали не попали//+добавить стреляли/не стреляли
	string x,y;
	int _x,_y;
public:
	SeaWar(){
		for(int i=0;i<10;i++)for(int j=0;j<10;j++)enemy_pole[i][j]="_";
		x="abcdefghij"; y="12345678910";
	}
	void putShips(){
		wrecks=0;
		ships[0]="d1:d4";
		ships[1]="h1:j1";
		ships[2]="h3:j3";
		ships[3]="b1:b2";
		ships[4]="b4:b5";
		ships[5]="d10:e10";
		ships[6]="a10";
		ships[7]="d7";
		ships[8]="g6";
		ships[9]="j10";
		string s,l,r;
		memset(battle,0,sizeof(battle));
		for(int i =0;i<10;i++){
			_x=_y=0;
			int n;
			s=ships[i];
			n=s.find(":");
			if (n!=-1){
				l=s.substr(0,n);
				r=s.substr(n+1,s.size()-1);
				if(l.at(0)==r.at(0)){
					_x=x.find(l.at(0));
					_y=y.find(l.substr(1,l.size()));
					n=y.find(r.substr(1,r.size()))-_y;
					for(int j=0;j<n+1;j++) battle[_y+j][_x]=n+1;
				}else {
					_y=y.find(l.substr(1,l.size()));
					_x=x.find(l.at(0));
					n=x.find(r.at(0))-_x;
					for(int j=0;j<n+1;j++) battle[_y][_x+j]=n+1;
				}
			}else {
				_x=x.find(s.at(0));
				_y=y.find(s.substr(1,s.size()));
				n=0;
				battle[_y][_x]=1;
			}
			inj_ship[i]=n+1;
		}
	}

	int check(string in){
		_x=x.find(in.at(0));
		_y=y.find(in.substr(1,in.size()));
		int n=0;
		if (battle[_y][_x]!=0) {
			enemy_pole[_y][_x]="x"; 
			switch(battle[_y][_x]){
			case 4:
				inj_ship[0]--;
				if(inj_ship[0]==0)return 2;
				return 1;
			case 3:
				for(n=1;n<=2;n++){
					if(inj_ship[n]!=0){
						inj_ship[n]--;
						if(inj_ship[n]==0)return 2;
						break;
					}
				}
				return 1;
			case 2:
				for(n=3;n<=5;n++){
					if(inj_ship[n]!=0){
						inj_ship[n]--;
						if(inj_ship[n]==0)return 2;
						break;
					}
				}
				return 1;
			case 1:
				for(n=6;n<=9;n++){
					if(inj_ship[n]!=0){
						inj_ship[n]--;
						if(inj_ship[n]==0)return 2;
						break;
					}
				}
				return 1;
			}
			return 1;
		}else {
			enemy_pole[_y][_x]="o";
			return 0;
		}
	}
	void refreshPole(){
		pole=" a b c d e f g h i j \n";
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				pole+="|"+enemy_pole[i][j]; 
				//pole+="|"+to_string(battle[i][j]);
			}
			pole+="|" + to_string(i+1) + "\n";
		}
		cout<<pole;
	}

	void play(string in){
		int k=check(in);
		if (k==1) cout<< "BOOM!"<<endl; else if (k==2){ wrecks++; cout<< "KILLED!"<<endl;}
		refreshPole();
	}
	void start(){
		cout<<pole;
		string in="0";
		putShips();
		refreshPole();
		while(in!="end"){
		while(in!=""){
			getline(cin,in);
			play(in);
		if(wrecks==10) {cout<<"You Win!!!"<<endl; in="";}
		}
		cout<<"whana play again?"<<endl;
		getline(cin,in);
		}
	}
};
int main(){
	setlocale(LC_ALL, "Russian");
	//open file story.txt
	int n;
	string s;
	CowBulls cow_bul;
	Story story;
	XO xo;
	fifth f;
	SeaWar sw;
	do{
		cout<<"What you wana play?"<<endl<<"(0)CowBulls/(1)Story/(2)XO/(3)15/(4)SeaWar"<<endl;
		getline(cin,s);
		n=stoi(s,0,10);
		switch (n)
		{
		case 0:
			cow_bul.start();
			break;
		case 1:
			s="yes";
			while(s.at(0)=='y'){
				story.start();
				cout<<"Your story is over. Whanna play again?"<<endl;
				getline(cin,s);
			}
			break;
		case 2:
			xo.start();
			break;
		case 3:
			f.start();
			break;
		case 4:
			sw.start();
			//system("cls");
		}
	}while(s!="exit");
	//_getch();
	return 0;
}
