






void socket_read_cb(int fd, short events, void *arg)
{
    char msg[4096] = {0};

    event* ev = (event*)arg;

    int len = read(fd, msg, sizeof(msg) - 1);

    if(len <= 0)
    {
        event_free(ev);
        close(fd);
        return;
    }

    std::cout<<"msg: "<<msg<<endl;


    std::string reply_msg("replay msg");
    write(fd, reply_msg.c_str(), reply_msg.size());
}
  


void accept_cb(int fd, short events, void* arg)
{
    evutil_socket_t sockfd;
    sockaddr_in client;
    socklen_t len = sizeof(client);

    sockfd = ::accept(fd, ()&client, &len);
    evutil_make_socket_nonblocking(sockfd);

    std::cout<<"accept a new client "<<sockfd<<endl;

    event_base base = (event_base*)arg;

    event* ev = event_new(NULL, -1, 0, NULL, NULL);
    event_assign(ev, base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, (void*)ev);
    
    event_add(ev, NULL);
} 



int tcp_server_init(int port, int listen_num)
{
    evutil_socket_t listener = ::socket(AF_INET, SOCK_STREAM, 0);

    evutil_make_listen_socket_reuseable(listener);

    sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(port);

    if(::bind(listener, (SA*)&sin, sizeof(sin)))
    {
        evutil_closesocket(listener);
        return -1;
    }

    if(::listen(listener, listen_num) < 0)
    {
        evutil_closesocket(listener);
        return -1;
    }
    
    evutil_make_socket_nonblocking(listener);

    return listener;
}



int main(int argc, char** argv)  
{  
  
    int listener = tcp_server_init(9999, 10);  
    if( listener == -1 )  
    {  
        perror(" tcp_server_init error ");  
        return -1;  
    }  
  
    struct event_base* base = event_base_new();  
  
    //添加监听客户端请求连接事件  
    struct event* ev_listen = event_new(base, listener, EV_READ | EV_PERSIST,  
                                        accept_cb, base);  
    event_add(ev_listen, NULL);  
  
  
    event_base_dispatch(base);  
  
    return 0;  
} 