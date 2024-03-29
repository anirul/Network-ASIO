//
// chat_message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>

class chat_message
{
public:
	const static std::size_t header_length = 4;
	const static std::size_t max_body_length = 512;

	chat_message() : data_(""), body_length_(0) 
	{
		data_.assign(max_body_length + header_length, '\0');
	}

	const char* data() const
	{
		return data_.data();
	}

	char* data()
	{
		return data_.data();
	}

	std::size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_.data() + header_length;
	}

	char* body()
	{
		return data_.data() + header_length;
	}

	std::size_t body_length() const
	{
		return body_length_;
	}

	void body_length(std::size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		std::string header = data_.substr(0, header_length);
		body_length_ = std::atoi(header.c_str());
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	void encode_header()
	{
		std::string header = std::to_string(body_length_);
		std::memcpy(data_.data(), header.data(), header_length);
	}

private:
	std::string data_;
	std::size_t body_length_;
};
