cmake_minimum_required(VERSION 3.20)
project(Projekt)

set(CMAKE_CXX_STANDARD 17)


add_executable(Projekt main.cpp Klasy/ClassWithIdAndName.cpp Klasy/ClassWithIdAndName.h Klasy/PrivateMessage.cpp Klasy/PrivateMessage.h Klasy/GroupMessage.cpp Klasy/GroupMessage.h Klasy/Connection.cpp Klasy/Connection.h Klasy/DatabaseConnection.cpp Klasy/DatabaseConnection.h Klasy/ReceiveAndResend.cpp Klasy/ReceiveAndResend.h)
target_link_libraries(Projekt mysqlcppconn)
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pthread ")
