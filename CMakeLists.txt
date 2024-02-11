cmake_minimum_required(VERSION 3.22)

project(PC_REMOTE_CTRL)

add_executable(pc_remote_ctrl src/main.cpp include/Server/server.cpp)

# Include directories
target_link_directories(pc_remote_ctrl PUBLIC include)

