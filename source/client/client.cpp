
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>




#include <event2/event.h>
#include <event2/bufferevent.h>
//#include <event2/buffer.h>
//#include <event2/util.h>


using namespace std;

void cmd_msg_cb(int fd, short events, void* arg)
{
}

void read_msg_cb(bufferevent* bev, void* arg)
{
}

void write_msg_cb(bufferevent* bev, void* arg)
{
}

void error_cb(bufferevent* bev, void* arg)
{
}
void init_socket_addr(sockaddr_in* server_addr, const char* ip, int port)
{
        memset(server_addr, 0, sizeof(*server_addr));

        server_addr->sin_family = AF_INET;
        server_addr->sin_port = port;//htos(port);
        inet_aton(ip, &server_addr->sin_addr);


}

int main(int argc, char** argv)
{
        if(argc < 3)
        {
                cout<<"please input 2 parameter"<<endl;
        }

        event_base* base = event_base_new();

        bufferevent* bev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

        event* ev_cmd = event_new(base, STDIN_FILENO, EV_READ | EV_PERSIST, cmd_msg_cb, (void*)bev);

        event_add(ev_cmd, NULL);

        sockaddr_in server_addr;
        const char* ip = argv[1];
        int port = atoi(argv[2]);

        init_socket_addr(&server_addr, ip, port);

        bufferevent_socket_connect(bev, (sockaddr*)&server_addr, sizeof(server_addr));

        bufferevent_setcb(bev, read_msg_cb, write_msg_cb, NULL, (void*)ev_cmd);
        bufferevent_enable(bev, EV_READ | EV_PERSIST);

        event_base_dispatch(base);

       cout<<"finish"<<endl;
       return 0;
                         
                         
}




