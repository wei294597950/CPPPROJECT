#include<array>
#include<functional>
#include<iostream>

using namespace std;

#include<boost/asio.hpp>
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;
const int MAX_IP_PACK_SIZE = 65536;
const int HEAD_LEN = 4;

class RWHandler
{
public:
    RWHandler(io_service& ios):m_sock(ios){

    }
    ~RWHandler(){

    }

    void HandleRead(){
        //transfer_at_least收到特定数量的字节会返回
        async_read(m_sock,buffer(m_buff),transfer_at_least(HEAD_LEN),[this](const 
        boost::system::error_code& ec,size_t size)
        {
            if(ec != nullptr){
                HandleError(ec);
                return;
            }
            cout<<m_buff.data()+ HEAD_LEN<<endl;
            HandleRead();

        });
    }

    void HandleWrite(char *data,int len){
        boost::system::error_code ec;
        write(m_sock,buffer(data,len),ec);
        if(ec != nullptr)
            HandleError(ec);
    }
    tcp::socket& GetSocket(){
        return m_sock;
    }

    void CloseSocket(){
        boost::system::error_code ec;
        m_sock.shutdown(tcp::socket::shutdown_send,ec);
        m_sock.close(ec);
    }

    void SetConnId(int connId){
        m_connId = connId;
    }

    int GetConnId() const{
        return m_connId;
    }

    template<typename T>
    void SetCallBackError(T t){
        m_callbackError = t;
    }

private:
    void HandleError(const boost::system::error_code & ec)
    {
        CloseSocket();
        cout<<ec.message()<<endl;
        if(m_callbackError)
            m_callbackError(m_connId);
    }
private:
    tcp::socket m_sock;
    std::array<char,MAX_IP_PACK_SIZE> m_buff;
    int m_connId;
    std::function<void(int)> m_callbackError;//定义函数对象，接受int，返回void
};


//typedef int (*funcP)(int*)   定义funcP为函数指针
//  std::function<int&(void)> fr = std::bind(&A::output,&a,std::placeholders::_1,
//                      std::placeholders::_2);  绑定类成员函数指针  成仿函数