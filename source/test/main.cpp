#include "helloworld.pb.h" //包含生成的头文件
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char* argv[]) {
    helloworld msg;
    msg.set_id(101);
//    msg.set_str("hello");
    // 序列化消息
    char buff[1024] = {0};
    msg.SerializeToArray(buff, 1024);
    //解析消息
    helloworld msgread;
    msgread.ParseFromArray(buff, 1024);
    cout << msgread.id() << endl;
  //  cout << msgread.str() << endl;
}
