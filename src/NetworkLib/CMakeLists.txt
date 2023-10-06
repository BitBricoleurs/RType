find_package(Threads REQUIRED)
add_library(NetworkLib STATIC
        Body.cpp
        Client.cpp
        IMessage.hpp
        InterfaceNetwork.cpp
        ../POCEngine/Utils/Message.cpp
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
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    message(STATUS "Boost include directories: ${Boost_INCLUDE_DIRS}")
    target_include_directories(NetworkLib PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(NetworkLib PRIVATE
            ${Boost_LIBRARIES}
            Boost::asio
            )
endif()

target_link_libraries(NetworkLib PRIVATE Threads::Threads)
target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})