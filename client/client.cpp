#include <iostream>
#include <asio.hpp>

int main(int ac, char** av)
{
	asio::error_code ec;
	asio::io_context context;
	asio::ip::tcp::endpoint ep(asio::ip::make_address("208.97.177.124", ec), 80);
	asio::ip::tcp::socket socket(context);
	socket.connect(ep, ec);
	if (!ec)
	{
		std::cout << "Connected!" << std::endl;
	}
	else
	{
		std::cout << "Failed to connect to address: " << ec.message() << std::endl;
		return -1;
	}

	if (socket.is_open())
	{
		std::string request =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(request.data(), request.size()), ec);
		socket.wait(socket.wait_read);
		size_t bytes = socket.available();
		std::cout << "Bytes Available: " << bytes << std::endl;

		if (bytes > 0)
		{
			std::vector<char> buffer(bytes);
			socket.read_some(asio::buffer(buffer.data(), buffer.size()), ec);
			for (const auto& c : buffer)
				std::cout << c;
		}
	}
	return 0;
}