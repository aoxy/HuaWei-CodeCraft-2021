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
using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

std::unordered_map<std::string, ProtoServer> ServerType; //可以购买的服务器型号
std::unordered_map<std::string, ProtoVM> VMType;		 //支持部署的虚拟机型号
unordered_map<string, ProtoVM> HashmodelVM;				 //每个型号对应一个虚拟机
unordered_map<int, ProtoVM> HashidVM;					 //每个id对应一个虚拟机
vector<vector<Request>> requests;

template <typename T1, typename T2, typename T3>
struct three
{
	T1 first;
	T2 second;
	T3 third;
	three(T1 t1, T2 t2, T3 t3) : first(t1), second(t2), third(t3) {}
	three() {}
};

int main()
{
	// TODO:read standard input
	int N; //整数N(1≤N≤100)，表示可以采购的服务器类型数量
	int M; //整数M(1≤M≤1000)，表示售卖的虚拟机类型数量
	int T; //整数T(1≤T≤1000)，表示题目共会给出 T天的用户请求序列数据
	std::ios::sync_with_stdio(false);
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
		}
	}

	// TODO:process 现在是为每一个虚拟机单独购买一台最大的服务器，可以删除虚拟机
	ProtoServer &maxServer = ServerType.begin()->second;
	for (auto i = ServerType.begin()++; i != ServerType.end(); i++)
		if (i->second.core() > maxServer.core() && i->second.ram() > maxServer.ram())
			maxServer = i->second;
	DataCenter dc(maxServer);

	unordered_map<string, int> sday(T);	  //每天购买的服务器
	vector<pair<int, char>> aday(T >> 2); //每天add的虚拟机
	for (int i = 0; i < T; i++)
	{
		sday.clear();
		aday.clear();
		for (int j = 0; j < R[i]; j++)
		{

			if (requests[i][j].optype() == "add")
			{
				ProtoVM pvm = VMType.find(requests[i][j].model())->second;
				pair<pair<int, char>, string> res = dc.add(pvm, requests[i][j].vid());
				aday.push_back(res.first);
				if (res.second != "")
					sday[res.second]++;
			}
			else
			{
				dc.del(requests[i][j].vid());
			}
		}
		cout << "(purchase, " << sday.size() << ")" << endl;
		for (auto it = sday.begin(); it != sday.end(); it++)
			cout << "(" << it->first << ", " << it->second << ")" << endl;
		cout << "(migration, 0)" << endl;
		for (auto it = aday.begin(); it != aday.end(); it++)
		{
			if (it->second != 'D')
				cout << "(" << it->first << ", " << it->second << ")" << endl;
			else
				cout << "(" << it->first << ")" << endl;
		}
	}

	return 0;
}
