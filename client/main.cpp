#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>


using boost::asio::ip::tcp;
using namespace std;


int main() {
    string id, send_to, sign;
    try {
        boost::system::error_code error;
        //auto info = parseINI("info.ini");
        boost::asio::io_context io_context;
        //msg_handler handler{move(info["info"]["send_to"]),move(info["info"]["id"])};

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
        string info = id+"&"+send_to+"$C";
        socket.write_some(boost::asio::buffer(info),error);
        if (error == boost::asio::error::eof) {
            return 0; // 서버가 연결을 정상적으로 종료했습니다.
        }
        else if (error) {
            throw boost::system::system_error(error); // 다른 종류의 오류 처리
        }

        while (true) {


            std::cout<<"입력 :::: ";
            getline(std::cin, sign);

            socket.write_some(boost::asio::buffer(sign),error);
            //데이터 읽기.
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            //접속 종료.
            if (error == boost::asio::error::eof) {
                break; // 서버가 연결을 정상적으로 종료했습니다.
            }
            else if (error) {
                throw boost::system::system_error(error); // 다른 종류의 오류 처리
            }

            std::cout.write(buf.data(), len);
            std::fill(buf.begin(), buf.end(), 0);
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
