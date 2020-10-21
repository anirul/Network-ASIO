cmake_minimum_required(VERSION 3.14)

project(NetworkASIO)

if(WIN32)
    add_compile_options("/std:c++latest")
endif(WIN32)
set(CMAKE_CXX_STANDARD 17)

find_package(asio CONFIG REQUIRED)

add_executable(Server
    ${CMAKE_CURRENT_SOURCE_DIR}/server/server.cpp
)

target_link_libraries(Server
  PRIVATE
	asio::asio
)

add_executable(Client
    ${CMAKE_CURRENT_SOURCE_DIR}/client/client.cpp
)

target_link_libraries(Client
  PRIVATE
	asio::asio
)
