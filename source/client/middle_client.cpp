

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
    char msg[1024] = {0};

    int ret = read(fd, msg, sizeof(msg));
    if(ret < 0)
    {
        exit(1);
    }   

    bufferevent* bev = (bufferevent*)arg;
    bufferevent_write(bev, msg, ret);
}


void server_msg_cb(bufferevent* bev, void* arg)
{

}

void event_cb(bufferevent* bev, short event, void* arg)
{

}


int main(int argc, char** argv)
{
    if(argc < 3)
    {
        return -1;
    }

    const char* server_ip = argv[1];
    int ip = atoi(argv[2]);

    int sockfd = tcp_connect_server(server_ip, ip);
    if(sockfd == -1)
    {
        return -1;
    }

    std::cout<<"connect to server successful!!"<<endl;

    event_base* base = event_base_new();

    bufferevent* bev = bufferevent_socket_new(base, sockfd, BEV_OPT_CLOSE_ON_FREE);

    event* ev_cmd = event_new(base, STDIN_FILENO, EV_READ| EV_PERSIST, 
                             cmd_msg_cb, (void*)bev);
    event_add(ev_cmd, NULL);

    bufferevent_setcb(bev, server_msg_cb, NULL, event_cb, (void*)ev_cmd);
    bufferevent_enable(bev, EV_READ | EV_PERSIST);


    event_base_dispatch(base);

    return 0;
}