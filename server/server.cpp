#include <iostream>
#include <asio.hpp>

int main(int ac, char** av)
{
	asio::io_context context;
	asio::ip::tcp::socket socket(context);
	asio::ip::tcp::resolver resolver(context);
	asio::ip::tcp::resolver::query query("0.0.0.0", "42000");
	asio::ip::tcp::resolver::iterator endpoint_iterator = 
		resolver.resolve(query);
	asio::connect(socket, endpoint_iterator);
	context.run();
	std::cout << "the end." << std::endl;
	return 0;
}
