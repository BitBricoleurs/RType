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
)

find_path(ASIO_INCLUDE_DIR NAMES asio.hpp PATHS /usr/local/include /opt/local/include)
include_directories(${ASIO_INCLUDE_DIR})

target_link_libraries(NetworkLib ${ASIO_LIBRARY})
