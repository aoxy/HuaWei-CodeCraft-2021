// #ifndef SERVER_PURCHASE_H_
// #define SERVER_PURCHASE_H_

// #include <iostream>
// #include <string>
// #include <vector>
// #include<unordered_map>
// #include "Request.h"
// #include "ProtoServer.h"
// #include "ProtoVM.h"
// #include "Util.h"
// using namespace std;

// /*
//     输入：每天的虚拟机申请记录,和所有服务器的种类。
//     输出：在理想情况下能够满足要求的购买服务器的种类和数量
    
//     其中，输出为二维数组，按照平均购买+维护价格从小到大排序。
//     计算公式为：
//     设T为天数，Wi为每种型号的服务器每天的维护价格：
//     则总价格 S=购买服务器总价+(sum_{Wi})*T/2，（后续还可以优化）

// */

// class Server_Purchase
// {
// private:
//     int N;      //最大找出100种购买方式
//     int CAB_num;      //申请的最大的双节点的CPU总数
//     int MAB_num;     //A，B节点申请的内存
//     int CS_num;     //单个节点虚拟机需要的CPU总数
//     int MS_num;     //单个节点内存

//     int MAX_C;
//     int MAX_M;      //最大需求
//     vector<int> CE_value;       //定义每个服务器的性价比
//     vector<vector<Request>> requests;
//     vector<ProtoServer> ServerType; //可以购买的服务器型号
//     vector<int> sort_ServerType;    //经过性价比排序的服务器(序号)
//     unordered_map<int,ProtoVM> HashidVM;         //哈希表
//     vector<vector<pair<int,int>>> Purchase;      //每种购买服务器的购买方式列表          
// public:
//     Server_Purchase(vector<vector<Request>> *prequests, vector<ProtoServer> *pServerType, unordered_map<int,ProtoVM>	*pHashidVM);
//     ~Server_Purchase();

//     void Count_request();       //统计至少需要的cpu和内存
//     void Server_sort();         //服务器根据性价比排序
//     void Get_Purchase();        //获得需要购买的服务器的型号和数量

// };

// Server_Purchase::Server_Purchase(vector<vector<Request>> *prequests, vector<ProtoServer> *pServerType, unordered_map<int,ProtoVM>	*pHashidVM)
// {
//     requests=*prequests;
//     ServerType=*pServerType;
//     HashidVM=*pHashidVM;
//     N=100;
//     CAB_num=0;
//     MAB_num=0;
//     CS_num=0;                         
//     MS_num=0;
//     CE_value=*(new vector<int>(ServerType.size()));
//     sort_ServerType=*(new vector<int>(ServerType.size()));
//     for(int i=0;i<ServerType.size();i++){
//         sort_ServerType[i]=i;
//     }
// }

// Server_Purchase::~Server_Purchase()
// {
// }

// #endif