#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) // server의 주소를 입력받고있다.
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage : Client <host>" << std::endl;
			return 1;
		}

		tcp::iostream stream(argv[1], std::to_string(int(13))); // 인자[1] = ip주소
		if (!stream)
		{
			std::cout << "Unable to connect: " << stream.error().message() << std::endl;
			return 1;
		}

		// send message to server
		stream << "Hello from client";
		stream << std::endl; // send new-line to end receiver'stream getline

		// receive message from server
		std::string line;
		std::getline(stream, line);
		std::cout << line << std::endl; // 받은내용 출력
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}