cmake_minimum_required(VERSION 3.15)

find_package(Threads REQUIRED)
add_library(NetworkLib STATIC
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

include(FetchContent)
FetchContent_Declare(
        Boost
        URL "https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.xz"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_RUNTIME_LINK static)
set(BOOST_INCLUDE_LIBRARIES
        asio
        assert
        align
        array
        bind
        coroutine
        config
        context
        core
        chrono
        date_time
        exception
        function
        move
        system
        smart_ptr
        throw_exception
        utility
)
FetchContent_MakeAvailable(Boost)

foreach(lib ${BOOST_INCLUDE_LIBRARIES})
    target_link_libraries(
            NetworkLib
            PRIVATE
            Boost::${lib}
    )
    target_include_directories(
            NetworkLib
            PRIVATE
            Boost::${lib}
    )
endforeach()

target_link_libraries(NetworkLib PRIVATE Threads::Threads)
target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})