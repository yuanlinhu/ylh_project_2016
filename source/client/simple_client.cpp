
#include <stdio>
using namespace std;

int tcp_connect_server(const char* server_ip, int port)
{
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htos(port);
    int status = inet_aton(server_ip, &server_addr.sin_addr);

    if (status == 0)
    {
        //errno = EINVAL;
        return -1;   
    }

    int sockfd = ::socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        return sockfd;
    }

    status = ::connect(sockfd, (SA*)&server_addr, sizeof(server_addr));

    if(status == -1) 
    {
        ::close(sockfd);
        return -1;
    }
    
    evutil_make_socket_nonblocking(sockfd);
    
    return sockfd;
}

void cmd_msg_cb(int fd, short events, void* arg)
{
 char msg[1024] = { 0 };

    int len = read(fd, msg, sizeof(msg) - 1);
    if(len < 0)
    {
        exit(1);
    }

    std::cout<<"msg = "<<msg<<endl;
}

void socket_read_cb(int fd, short events, void* arg)
{
    char msg[1024] = { 0 };

    int len = read(fd, msg, sizeof(msg) - 1);
    if(len < 0)
    {
        exit(1);
    }

    std::cout<<"msg = "<<msg<<endl;
}






int main(int argc, char** argv)
{
    if(argc < 3)
    {
        std::cout<<"please input 2 parameters "<<endl;
        return -1;
    }

    std::string server_ip = argv[1];
    int server_port = argv[2];
    int sockfd = tcp_connect_server(server_ip, server_port);
    if(sockfd == -1)
    {
        return -1;
    }

    std::cout<<"tcp connect successful!"<<endl;

    event_base* new_event_base = event_base_new();

    event* ev_sockfd = event_new(base, sockfd, 
                                EV_READ | EV_PERSIST,
                                socket_read_cb, 
                                NULL);

    event_add(ev_sockfd, NULL);


    event* ev_cmd = event_new(base, STDIN_FILENO,
                             EV_READ | EV_PERSIST,
                             cmd_msg_cb,
                             (void*)&sock_fd)

    event_add(ev_cmd, NULL);

    event_base_dispatch(base);

    return 0;

}