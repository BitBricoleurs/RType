cmake_minimum_required(VERSION 3.15)

find_package(Threads REQUIRED)

target_sources(${LIBRARY_NAME_NETLIB} PRIVATE
        Body.cpp
        Client.cpp
        IMessage.hpp
        InterfaceNetwork.cpp
        PacketComponent.hpp
        Server.cpp
        Tick.cpp
        TSqueue.hpp
        PacketIO.cpp
        PacketIO.hpp
        EndpointGetter.hpp
        EndpointGetter.cpp
        AMessage.hpp
)

target_link_libraries(${LIBRARY_NAME_NETLIB} PRIVATE Threads::Threads)
target_include_directories(${LIBRARY_NAME_NETLIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})