add_library(NetworkLib STATIC
        Body.cpp
        Client.cpp
        IMessage.hpp
        InterfaceNetwork.cpp
        Message.cpp
        PacketComponent.hpp
        Server.cpp
        Tick.cpp
        TSqueue.hpp
        PacketIO.cpp
        PacketIO.hpp
        EndpointGetter.hpp
        EndpointGetter.cpp
)

find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

target_link_libraries(NetworkLib ${Boost_LIBRARIES})
