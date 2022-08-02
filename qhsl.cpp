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

void get_resource(){
//	这个是从拉克丝机器人发的照片扒资源的程序
//  需在同目录放置 resource.bmp 
//  如果拉克丝没有此资源, 考虑从萌娘百科上获取 256*256 的透明底 png 文件. 然后用画图 3D 将之叠在黑底上, 再用 ps 缩小为 180*180 导出.
//      萌娘百科上的部分素材并不与实际抽卡见到的相吻合, 此时建议自行 裁剪 出 180*180 像素 (虽然还是与实际抽卡不符) 
//  其余素材也是裁剪出后, 用 ps 缩放为 180*180 (因为要抗锯齿缩放) 
//  仓库里的素材点击放大后, 可以获得 214*214 尺寸的 (在 steam 端的大小下)(为去除边框选择 212*212 裁剪) 
	cout << "请确认 bool_ver 无误后使用!" << endl; 
	int local_global_num = 0;
	while(true){
	
		ifstream fin("resource.bmp",ios::binary);
		for (int row =1 ; row <= 2 ; row ++){
			for (int col = 1 ; col <= 5 ; col ++){
				cout << row << " , " << col << endl;
				time_t now = time(0);
			
				string str = resource_path + itos(now) + itos(local_global_num) + ".bmp";
				local_global_num ++; 
//				cout << str << endl;
				ifstream fin2("resource\\99_Empty\\Empty2.bmp",ios::binary);
				ofstream fout(str,ios::binary);
				for (int i=0;i<54+180*180*3;i++){
					fin2.read(b,1);
					fout.write(b,1);
				}
				fin2.close();
			
				if (ver_now) {
					int n = 3 * (18 + (20 + 200 * (row-1)) *1020 + (20 + 200 * (col -1)) );
					fin.seekg(n,ios::beg);
					fout.seekp(54L,ios::beg); // 根据实际需要再偏移 
					for (int i=0;i<180;i++){
						for (int j=0 ; j<180 ; j++){
							fin.read(b,3);
						fout.write(b,3);
						}
						fin.seekg(2520L,ios::cur);
					}
				} else{
					int n = 3 * (18 + (40 + 200 * (row-1)) *1040 + (20 + 200 * (col -1)) );
					fin.seekg(n,ios::beg);
					fout.seekp(54L,ios::beg); // 根据实际需要再偏移 
					for (int i=0;i<180;i++){
						for (int j=0 ; j<180 ; j++){
							fin.read(b,3);
							fout.write(b,3);
						}
						fin.seekg(2580L,ios::cur);
					}
				}
				fout.close(); 
			}
		}
		
		fin.close();
		cout << "waiting..." << endl;
		cin.get();
	}
} 

int main(){
//	get_resource();
while (true){
	draw() ;
	cin.get();
}
	return 0;
}
