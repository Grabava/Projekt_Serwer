cmake_minimum_required(VERSION 3.20)
project(Projekt)

set(CMAKE_CXX_STANDARD 17)


add_executable(Projekt main.cpp Klasy/user.cpp Klasy/user.h Klasy/group.cpp Klasy/group.h Klasy/Private_Message.cpp Klasy/Private_Message.h Klasy/Group_Message.cpp Klasy/Group_Message.h Klasy/Connection.cpp Klasy/Connection.h Klasy/DatabaseConnection.cpp Klasy/DatabaseConnection.h Klasy/ReceiveAndResend.cpp Klasy/ReceiveAndResend.h)
target_link_libraries(Projekt mysqlcppconn)
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread ")
