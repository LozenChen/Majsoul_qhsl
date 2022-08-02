#include<iostream>
#include<cmath> 
#include<fstream>
#include<iomanip>
#include<windows.h>
#include<ctime>
using namespace std;

// 180*180 , 1020*420 px
char b[7000];
bool ver_now = true; 
string str000 = "000";
string resource_path = "resource\\" ;
string itos(int n){
	str000[2] = (char)(n%10 + 48) ;
	n = n/10 ;
	str000[1] = (char)(n%10 + 48) ;
	n = n/10 ;
	str000[0] = (char)(n%10 + 48) ;
	return str000;
}

struct Pool{
	string name;
	int num;
	int inpool; // 决定此种类在卡池中的拷贝数 . 若为 0 则不出现此种类 . 通过更改此条即可达到调整概率的效果 
};

struct Pool pool[19] = {
{"00_green",8,1},{"01_blue",8,1},{"02_purple",8,1},
{"03_frame",8,1},{"04_hand",3,1},{"05_music",12,1},
{"06_reach_bar",30,1},{"07_reach_effect",28,1},{"08_ron",33,1},
{"09_tablecloth",19,1},{"10_tile",16,1},
{"11_gentleman",19,1},{"12_waifu",41,1},
{"13_call_card",1,1},{"14_gem",8,1},{"15_gift",14,1},
{"16_special",8,1},{"17_background",6,1},
{"18_temp",1,1}
};
// 记得资源更新后修改 num. 

string getname(){
	int sum[20] ;
	sum[0] = 0;
//	sum[i] 是 0 ~ i-1 的求和 
	for (int i= 0 ; i<= 18 ; i++) {
		sum[i+1] = sum[i] + pool[i].num * pool[i].inpool;
	}
	int n = rand()%sum[19]+1;
	for (int i = 18 ; i >=0 ; i--){
		if (n> sum[i]) {
			n = (n-sum[i]-1)%pool[i].num +1;
			return (resource_path + pool[i].name + "\\"+ itos(n) + ".bmp");
		}
	}
	return "unexpected";
} 

void draw(){
	ifstream fin2("resource\\99_Empty\\Empty.bmp",ios::binary);
	ofstream fout("output.bmp",ios::binary);
	for (int i=0;i<54;i++){
		fin2.read(b,1);
		fout.write(b,1);
	}
	fin2.read(b,3060);
	for (int i=0 ; i<20 ; i++){
		fout.write(b,3060);
	}
	fin2.read(b,60);
	for (int i=0 ; i<180 ; i++){
		for (int j = 0 ; j <5 ; j++){
			fout.write(b,60);
			fout.seekp(540L,ios::cur);
		}
		fout.write(b,60);
	}
	fin2.read(b,3060);
	for (int i=0 ; i<20 ; i++){
		fout.write(b,3060);
	}
	fin2.read(b,60);
	for (int i=0 ; i<180 ; i++){
		for (int j = 0 ; j <5 ; j++){
			fout.write(b,60);
			fout.seekp(540L,ios::cur);
		}
		fout.write(b,60);
	}
	fin2.read(b,3060);
	for (int i=0 ; i<20 ; i++){
		fout.write(b,3060);
	}
	
	fin2.close();
	
	srand(time(0));
for (int row =1 ; row <= 2 ; row ++){
	for (int col = 1 ; col <= 5 ; col ++){
		string choice_path = getname();
		cout << choice_path << endl; 
		ifstream fin(choice_path,ios::binary);
		fin.seekg(54L,ios::beg);
		int n = 3 * (18 + (20 + 200 * (row-1)) *1020 + (20 + 200 * (col -1)) );
		fout.seekp(n,ios::beg); 
		for (int i=0;i<180;i++){
			for (int j=0 ; j<180 ; j++){
				fin.read(b,3);
			fout.write(b,3);
			}
		fout.seekp(2520L,ios::cur);
		}
		fin.close();
	}
}

fout.close(); 
cout << "==============================" << endl;
cout << "waiting..." << endl;
} 

int main(){
while (true){
	draw() ;
	cin.get();
}
	return 0;
}
