// #include"Server_Purchase.h"


// void Server_Purchase::Count_request(){
//     int CAB=0,MAB=0,CS=0,MS=0;
//     for(auto x: requests){
//         for(auto R:x){
//             int id=R.id();
//             string op=R.optype();
//             if(op=="add"){
//                 if(HashidVM[id].node()==1){
//                     CAB+=HashidVM[id].core();
//                     MAB+=HashidVM[id].ram();
//                     CAB_num=max(CAB,CAB_num);
//                     MAB_num=max(MAB,MAB_num);
//                 }
//                 else{
//                     CS+=HashidVM[id].core();
//                     MS+=HashidVM[id].ram();
//                     CS_num=max(CS,CS_num);
//                     MS_num=max(MS,MS_num);
//                 }
//             }

//         }
//     }
//     MAX_C=2*(CAB_num)+CS_num;
//     MAX_M=2*MAB_num+MS_num;
// }