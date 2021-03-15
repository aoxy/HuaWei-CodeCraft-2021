#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "ProtoServer.h"
#include "ProtoVM.h"
#include "Request.h"
#include "Util.h"
#include "DataCenter.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unordered_map;
using std::vector;

std::unordered_map<std::string, ProtoServer> ServerType; //可以购买的服务器型号
std::unordered_map<std::string, ProtoVM> VMType;		 //支持部署的虚拟机型号
unordered_map<string, ProtoVM> HashmodelVM;				 //每个型号对应一个虚拟机
unordered_map<int, ProtoVM> HashidVM;					 //每个id对应一个虚拟机
vector<vector<Request>> requests;

int main()
{
	// TODO:read standard input
	int N; //整数N(1≤N≤100)，表示可以采购的服务器类型数量
	int M; //整数M(1≤M≤1000)，表示售卖的虚拟机类型数量
	int T; //整数T(1≤T≤1000)，表示题目共会给出 T天的用户请求序列数据

	cin >> N;
	cin.get();
	ProtoServer ps;
	for (int i = 0; i < N; i++)
	{
		cin >> ps;
		ServerType.insert({ps.model(), ps});
	}
	cin >> M;
	cin.get();
	ProtoVM pvm;
	for (int i = 0; i < M; i++)
	{
		cin >> pvm;
		VMType.insert({pvm.model(), pvm});
	}
	// //转化成哈希map
	// for (int i = 0; i < M; i++)
	// {
	// 	HashmodelVM.insert({VMType[i].model(), VMType[i]});
	// }
	cin >> T;
	cin.get();
	requests = *(new vector<vector<Request>>(T));
	vector<int> R(T); //非负整数R表示当天共有R条请求
	for (int i = 0; i < T; i++)
	{
		cin >> R[i];
		cin.get();
		requests[i] = *(new vector<Request>(R[i]));
		for (int j = 0; j < R[i]; j++)
		{
			cin >> requests[i][j];
			// string op = requests[i][j].optype();
			// if (op == "add")
			// {
			// 	HashidVM.insert({requests[i][j].id(), HashmodelVM[requests[i][j].model()]});
			// }
		}
	}

	// TODO:process 现在是为每一个虚拟机单独购买一台最大的服务器
	ProtoServer &maxServer = ServerType.begin()->second;
	for (auto i = ServerType.begin()++; i != ServerType.end(); i++)
		if (i->second.core() > maxServer.core() && i->second.ram() > maxServer.ram())
			maxServer = i->second;
	DataCenter dc(maxServer);
	vector<int> addCount(T);
	for (int i = 0; i < T; i++)
	{
		addCount[i] = 0;
		for (int j = 0; j < R[i]; j++)
		{
			if (requests[i][j].optype() == "add")
			{
				addCount[i]++;
			}
		}
	}
	for (int i = 0; i < T; i++)
	{
		cout << "(purchase, 1)" << endl;
		cout << "(" << maxServer.model() << ", " << addCount[i] << ")" << endl;
		//FIXME:此处有段错误bug
		cout << "(migration, 0)" << endl;
		for (int j = 0; j < R[i]; j++)
		{
			if (requests[i][j].optype() == "add")
			{

				ProtoVM pvm = VMType.find(requests[i][j].model())->second;
				std::pair<int, char> res = dc.add(pvm, requests[i][j].vid());
				if (res.second != 'D')
					cout << "(" << res.first << ", " << res.second << ")" << endl;
				else
					cout << "(" << res.first << ")" << endl;
			}
		}
	}
	// TODO:write standard output

	// TODO:fflush(stdout);
	return 0;
}
