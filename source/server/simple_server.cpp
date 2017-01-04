

void accept_cb(int fd, short event, void* arg)
{

}

void socket_read_cb(int fd, short event, void* arg)
{

}

int tcp_server_init(int port, int listen_num)
{
    
}


int main(int argc, char** argv)
{
    int listener = tcp_server_init(9999, 5);
    if(listener == -1)
    {
        std::cout<<"listener error"<<endl;
        return -1;
    }

    event_base *new_event_base = event_base_new();

    event* ev_listen = event_base(base, listener,
                                 EV_READ | EV_PERSIST,
                                 accept_cb, base);


    event_add(ev_listen, NULL);
    
    event_base_dispatch(new_event_base);

    return 0;
}

