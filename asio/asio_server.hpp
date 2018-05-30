#include<boost/asio/buffer.hpp>
#include<unordered_map>
#include<numeric>
#include"asio_read_write.hpp"
#include<list>


const int MaxConnectionNum = 65536;
const int MaxRecvSize = 65536;
class Server{
public:
    Server(io_service &ios, short port) : m_ios(ios), m_acceptor(ios,tcp::endpoint(tcp::v4(),port)), m_cnnIdPool(MaxConnectionNum)
    {
        m_cnnIdPool.resize(MaxConnectionNum);
        std::iota(m_cnnIdPool.begin(),m_cnnIdPool.end(),1);//用顺序递增的值赋值指定范围的元素
    }
    ~Server()
    {

    }

    void Accept()
    {
        cout<< "start listening" <<endl;
        std::shared_ptr<RWHandler> handler = CreateHandler();

        m_acceptor.async_accept(handler->GetSocket(),[this,handler](const boost::system::error_code
        & error){
            if(error){
                cout<<error.value()<<" "<<error.message()<<endl;
                HandleAcpError(handler,error);
                return;
            }
        m_handlers.insert(std::make_pair(handler->GetConnId(),handler));
        cout<<"current connect cout:"<<m_handlers.size() <<endl;
        handler->HandleRead();
        Accept();
        });
    }

    private:
        void HandleAcpError(std::shared_ptr<RWHandler> eventHandler, const boost::system::error_code& error)
        {
            cout<<"Erroor ,reason:"<<error.value()<<error.message()<<endl;
            eventHandler->CloseSocket();
            StopAccept();
        }
        void StopAccept()
        {
            boost::system::error_code ec;
            m_acceptor.cancel(ec);
            m_acceptor.close(ec);
            m_ios.stop();
        }

        std::shared_ptr<RWHandler>  CreateHandler()
        {
            int connId = m_cnnIdPool.front();
            m_cnnIdPool.pop_front();
            std::shared_ptr<RWHandler> handler = std::make_shared<RWHandler>(m_ios);
            handler->SetConnId(connId);
            handler->SetCallBackError([this](int connId){
                RecyclConnid(connId);
            });
            return handler;
        }
        void RecyclConnid(int connId){
            auto it = m_handlers.find(connId);
            if(it != m_handlers.end())
                m_handlers.erase(it);
            cout<<"current connect count:" <<m_handlers.size()<<endl;
            m_cnnIdPool.push_back(connId);
        }
    private:
        io_service& m_ios;
        tcp::acceptor m_acceptor;
        std::unordered_map<int,std::shared_ptr<RWHandler>> m_handlers;

        list<int> m_cnnIdPool;
};