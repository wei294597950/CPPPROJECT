#include<sys/signal.h>
#include<event.h>

void signal_cb(int fd,short event,void *argc){
    struct event_base* base = (event_base*) argc;
    struct timeval delay = {2,0};
    printf("caught an interrupt signal;exiting cleanly in two seconds\n");
    event_base_loopexit(base,&delay);
}

void timeout_cb(int fd,short event,void *argc){
    printf("timeout\n");
}

int main(){
    struct event_base * base = event_init();//相当于一个reactor实例
    struct event* signal_event = evsignal_new(base,SIGINT,signal_cb,base);//创建信号事件处理器   //事件处理器和句柄绑定 
    event_add(signal_event,NULL);
    //将事件处理器添加到注册事件队列中 ，并将该事件处理器对应的事件注册到 事件多路分发器 中                                         

    timeval tv={1,0};
    struct event* timeout_event = evtimer_new(base,timeout_cb,NULL);//创建定时事件处理器，设置他们从属的reactor为event
    event_add(timeout_event,&tv);

    event_base_dispatch(base);//执行事件循环

    event_free(timeout_event);
    event_free(signal_event);
    event_base_free(base);

}
//signal_cb即回调函数，argc是reactor传递给回调函数的参数
