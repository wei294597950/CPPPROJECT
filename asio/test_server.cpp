
#include"asio_server.hpp"

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;
using namespace boost;
void TestServer(){
    io_service ios;
    Server server(ios,9900);
    server.Accept();
    ios.run();

}

int main()
{
    TestServer();
    return 0;
}