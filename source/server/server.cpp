#include <event2/event.h>
#include <stdio>

void cb_func(evutil_socket_t fd, short what, void* arg)
{
        const char * data = (const char*)arg;
        printf("cb_func arg = %s ", data);
}


int main()
{

    event_base* new_event_base = event_base_new();

    evutil_socket_t fd;
    event* event_read = event_new(new_event_base, fd, EV_READ| EV_PERSIST, cb_func, (char*)"");

    event_add(event_read, NULL);

//    bufferevent* sock_buff_event = bufferevent_socket_new(new_event_base, fd, BEV_OPT_CLOSE_ON_FREE);

    event_base_dispatch(new_event_base);

    event_base_free(new_event_base);
    return 0;
}
