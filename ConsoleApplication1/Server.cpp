#include <iostream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_service io_service;

		tcp::endpoint endpoint(tcp::v4(), 13);			// 통신용 양쪽 끝을 endpoint. 13은 port_number
		tcp::acceptor acceptor(io_service, endpoint);	// endpoint에서 io_service를 accept할 acceptor를 생성
		// acceptor와 endpoint가 연결되어있다.
		std::cout << "Server started" << std::endl;

		for (;;) // 무한루프
		{
			const std::string message_to_send = "Hello From Server"; // 서버가 클라이언트 에게 보여줄문장

			boost::asio::ip::tcp::iostream stream;	// 일반 iostream아님. overloading된 iostream

			std::cout << "check 1" << std::endl;

			boost::system::error_code ec;
			acceptor.accept(*stream.rdbuf(), ec);	// 클라이언트 접속해오면, rdbuf를 읽겠다.

			std::cout << "check 2" << std::endl;

			if (!ec) //TODO: How to take care of multiple clients? Multi-threading?
			{	// 클라이언트가 정상 접속
				// receive message from client 
				std::string line;
				std::getline(stream, line);			// 입출력 스트림에서 클라이언트로부터 메세지를 받는다.
				std::cout << line << std::endl;

				// send message to client
				stream << message_to_send;			// message를 stream으로 보냄
				stream << std::endl;				// 클라이언트 입장에서는 여기서 데이터를 읽어야 서버가 보낸다.
			}
		}
	}
	catch (std::exception& e)						// 예외처리
	{
		std::cout << e.what() << std::endl;
	}
 }