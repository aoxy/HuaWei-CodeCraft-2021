#include <iostream>
#include <vector>
#include <string>
#include<unordered_map>
#include "ProtoServer.h"
#include "ProtoVM.h"
#include "Request.h"
#include "Util.h"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::unordered_map;
using std::string;

vector<ProtoServer> ServerType; //可以购买的服务器型号
vector<ProtoVM> VMType;			//支持部署的虚拟机型号
unordered_map<string,ProtoVM>	HashmodelVM;		//每个型号对应一个虚拟机
unordered_map<int,ProtoVM>	HashidVM;				//每个id对应一个虚拟机
vector<vector<Request>> requests;

int main()
{
	// TODO:read standard input
	int N; //整数N(1≤N≤100)，表示可以采购的服务器类型数量
	int M; //整数M(1≤M≤1000)，表示售卖的虚拟机类型数量
	int T; //整数T(1≤T≤1000)，表示题目共会给出 T天的用户请求序列数据
	cin >> N;
	cin.get();
	ServerType = *(new vector<ProtoServer>(N));
	for (int i = 0; i < N; i++)
		cin >> ServerType[i];
	cin >> M;
	cin.get();
	VMType = *(new vector<ProtoVM>(M));
	for (int i = 0; i < M; i++)
		cin >> VMType[i];

	//转化成哈希map
	for (int i = 0; i < M; i++)
	{
		 HashmodelVM.insert({VMType[i].model(),VMType[i]});
	}
	cin >> T;
	cin.get();
	requests = *(new vector<vector<Request>>(T));
	vector<int> R(T); //非负整数R表示当天共有R条请求
	for (int i = 0; i < T; i++)
	{
		cin >> R[i];
		cin.get();
		requests[i] = *(new vector<Request>(R[i]));
		for (int j = 0; j < R[i]; j++){
			cin >> requests[i][j];
			string op=requests[i][j].optype();
			if(op=="add"){
				HashidVM.insert({requests[i][j].id(),HashmodelVM[requests[i][j].model()]});
			}
		}	
	}
	// TODO:process
	ProtoServer &maxServer = ServerType[0];
	for (int i = 1; i < N; i++)
		if (ServerType[i].core() > maxServer.core() && ServerType[i].ram() > maxServer.ram())
			maxServer = ServerType[i];
	
	for (int i = 0; i < T; i++)
	{
		for (int j = 0; j < R[i]; j++)
			cin >> requests[i][j];
	}
	// TODO:write standard output
	
	// TODO:fflush(stdout);
	return 0;
}
