#include <iostream>
#include <boost/asio.hpp>
#include "communication/communication.hpp"
#include "cmd_handler/cmd_handler.hpp"
#include <fstream>
#include <iomanip>
#include <sstream>
#include "communication/log_handler.hpp"
#define PORT 7100

using boost::asio::ip::tcp;
using namespace std;

void logException(const std::string& message) {
    std::ofstream logFile("error.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.close();
    } else {
        std::cerr << "Unable to open log file." << std::endl;
    }
}

int main() {
    communication cmu;
    cmd_handler cmd_hdr {cmu};
    cout << "Server start..." <<endl;
    cout << "Server is listening on port " << PORT <<endl;
    std::ios::sync_with_stdio(false);
    //thread(cmd_handling, &cmu).detach();
    thread(&cmd_handler::running, &cmd_hdr).detach();
    try {
        boost::asio::io_context io_context; //모든 입출력은 관리하는 객체.
        //연결 요청을 수락하는 객체. C언어에서 accept() 함수에 해당.
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));
        //반복문을 수행하면서 연결.
        while(true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            thread(&communication::cmi_start, &cmu, std::move(socket)).detach();
        }
    } catch (std::exception& e) {
        //cerr << "Exception: " << e.what() << "\n";
        auto now_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        auto now_tm = *localtime(&now_time);
        ostringstream ss;
        ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
        string t {ss.str()+" : " + e.what()};
    }

    return 0;
}
