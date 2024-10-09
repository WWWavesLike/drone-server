#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>



using boost::asio::ip::tcp;
using namespace std;


int main() {
    string id, send_to;
    try {
        boost::system::error_code error;
        boost::asio::io_context io_context;


        //const std::string server = "lflk.myds.me";  // 서버 주소
        const std::string server = "127.0.0.1";  // 서버 주소
        const std::string port = "7100";

        //서버에 연결하기 위한 endpoint 생성.
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(server, port);

        //소켓 생성.
        tcp::socket socket(io_context);
        //서버 연결.
        boost::asio::connect(socket, endpoints);

        boost::array<char, 1024> buf;

        cout<<"ID 입력 ::::";
        cin>>id;
        cout<<"송신 대상 ID 입력 ::::";
        cin>>send_to;
        string info = send_to+"&"+id+"$R";
        socket.write_some(boost::asio::buffer(info),error);
        if (error == boost::asio::error::eof) {
            return 0; // 서버가 연결을 정상적으로 종료했습니다.
        }
        else if (error) {
            throw boost::system::system_error(error); // 다른 종류의 오류 처리
        }

        while (true) {
            socket.read_some(boost::asio::buffer(buf), error);
            //접속 종료.
            if (error == boost::asio::error::eof) {
                break; // 서버가 연결을 정상적으로 종료했습니다.
            }
            else if (error) {
                throw boost::system::system_error(error); // 다른 종류의 오류 처리
            }
            string msg = buf.data();
            if(!msg.empty())cout<<msg<<endl;
            std::fill(buf.begin(), buf.end(), 0);
        }
        socket.close();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
