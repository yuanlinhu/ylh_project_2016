
#include "ylh_server.h"

YLH_Server::YLH_Server()
{

}

YLH_Server::~YLH_Server()
{
    
}

int YLH_Server::init(int port, int max_client_num)
:m_listen_port(port)
,m_max_client(max_client_num)
,m_listener(NULL)
,m_event_base(NULL)
{
    sockaddr_in sin;    
    memset(&sin, 0, sizeof(struct sockaddr_in));    
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    m_event_base = event_base_new();

    m_listener = evconnlistener_new_bind(m_event_base, 
                                        listener_cb, 
                                        base, 
                                        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 
                                        m_max_client, 
                                        (sockaddr*)&sin,
                                        sizeof(sockaddr_in)
                                        );

}

void YLH_Server::run()
{
    
}
