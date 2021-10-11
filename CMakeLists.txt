# A version I use this one because of pi.
cmake_minimum_required(VERSION 3.14)

# Now we can use C++20 as a standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(networkasio)

if(WIN32)
    # Standard MSVC flags.
    add_compile_options("/std:c++latest")
    add_compile_options("/D _WIN32_WINNT=0x0A00")
    # This is there to link static in case there is a -static in the variable.
    if(${VCPKG_TARGET_TRIPLET} MATCHES "-static")
        string(REPLACE 
            "/MD"
            "/MT" 
            CMAKE_CXX_FLAGS 
            ${CMAKE_CXX_FLAGS})
        string(REPLACE 
            "/MD"
            "/MT" 
            CMAKE_CXX_FLAGS_DEBUG 
            ${CMAKE_CXX_FLAGS_DEBUG})
        string(REPLACE 
            "/MD"
            "/MT" 
            CMAKE_CXX_FLAGS_RELEASE 
            ${CMAKE_CXX_FLAGS_RELEASE})
        string(REPLACE 
            "/MD"
            "/MT" 
            CMAKE_CXX_FLAGS_MINSIZEREL 
            ${CMAKE_CXX_FLAGS_MINSIZEREL})
        string(REPLACE 
            "/MD"
            "/MT" 
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
            ${CMAKE_CXX_FLAGS_RELWITHDEBINFO})
    endif(${VCPKG_TARGET_TRIPLET} MATCHES "-static")
endif(WIN32)

find_package(asio CONFIG REQUIRED)

add_executable(Server
    ${CMAKE_CURRENT_SOURCE_DIR}/server/server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/message.h
)

target_link_libraries(Server
  PRIVATE
	asio::asio
)

add_executable(Client
    ${CMAKE_CURRENT_SOURCE_DIR}/client/client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/common/message.h
)

target_link_libraries(Client
  PRIVATE
	asio::asio
)
