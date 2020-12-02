cmake_minimum_required(VERSION 3.5)
project(TIFD-2021)

set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

set (COMMON_SRCS network.cc  network.h secret_sharing_efficient_tools.cc  secret_sharing_efficient_tools.h  utils.cc  utils.h timer.h timer.cc)
add_executable(client client_main.cc ${COMMON_SRCS})
add_executable(server server_main.cc ${COMMON_SRCS})
