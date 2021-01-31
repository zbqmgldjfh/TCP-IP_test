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

		tcp::endpoint endpoint(tcp::v4(), 13);			// ��ſ� ���� ���� endpoint. 13�� port_number
		tcp::acceptor acceptor(io_service, endpoint);	// endpoint���� io_service�� accept�� acceptor�� ����
		// acceptor�� endpoint�� ����Ǿ��ִ�.
		std::cout << "Server started" << std::endl;

		for (;;) // ���ѷ���
		{
			const std::string message_to_send = "Hello From Server"; // ������ Ŭ���̾�Ʈ ���� �����ٹ���

			boost::asio::ip::tcp::iostream stream;	// �Ϲ� iostream�ƴ�. overloading�� iostream

			std::cout << "check 1" << std::endl;

			boost::system::error_code ec;
			acceptor.accept(*stream.rdbuf(), ec);	// Ŭ���̾�Ʈ �����ؿ���, rdbuf�� �аڴ�.

			std::cout << "check 2" << std::endl;

			if (!ec) //TODO: How to take care of multiple clients? Multi-threading?
			{	// Ŭ���̾�Ʈ�� ���� ����
				// receive message from client 
				std::string line;
				std::getline(stream, line);			// ����� ��Ʈ������ Ŭ���̾�Ʈ�κ��� �޼����� �޴´�.
				std::cout << line << std::endl;

				// send message to client
				stream << message_to_send;			// message�� stream���� ����
				stream << std::endl;				// Ŭ���̾�Ʈ ���忡���� ���⼭ �����͸� �о�� ������ ������.
			}
		}
	}
	catch (std::exception& e)						// ����ó��
	{
		std::cout << e.what() << std::endl;
	}
 }