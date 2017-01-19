
#ifdef _YLH_SERVER_H_


class YLH_Server
{
public:
    YLH_Server();
    ~YLH_Server();

    int init(int port, int max_client_num);
    void run();


    
private:
    void listener_cb(evconnlistener* listener, evutil_socket_t fd, sockaddr* sock, int socklen, void* arg);
    void socket_read_cb(bufferevent* bev, void* arg);
    void socket_error_cb(bufferevent* bev, void* arg);

private:
    int m_listen_port;  //监听端口
    int m_max_client;   //
    evconnlistener* m_listener;
    event_base* m_event_base;
}

#endif // !_YLH_SERVER_H_
