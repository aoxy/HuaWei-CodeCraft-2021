#include <iostream>
#include <vector>
#include "ProtoServer.h"
#include "ProtoVM.h"
#include "Request.h"
#include "Util.h"
using std::cin;
using std::cout;
using std::endl;
using std::vector;
int main()
{
	// TODO:read standard input
	int N; //整数N(1≤N≤100)，表示可以采购的服务器类型数量
	int M; //整数M(1≤M≤1000)，表示售卖的虚拟机类型数量
	int T; //整数T(1≤T≤1000)，表示题目共会给出 T天的用户请求序列数据
	cin >> N;
	cin.get();
	vector<ProtoServer> servers(N);
	for (int i = 0; i < N; i++)
	{
		cin >> servers[i];
	}
	cin >> M;
	cin.get();
	vector<ProtoVM> vms(M);
	for (int i = 0; i < M; i++)
	{
		cin >> vms[i];
	}
	cin >> T;
	cin.get();
	vector<vector<Request>> opseq(T);
	vector<int> R(T); //非负整数R表示当天共有R条请求
	for (int i = 0; i < T; i++)
	{
		cin >> R[i];
		cin.get();
		opseq[i] = vector<Request>(R[i]);
		for (int j = 0; j < R[i]; j++)
		{
			cin >> opseq[i][j];
		}
	}

	// TODO:process
	// TODO:write standard output
	// TODO:fflush(stdout);
	return 0;
}
