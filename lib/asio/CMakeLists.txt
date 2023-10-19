
include(FetchContent)
FetchContent_Declare(
        Boost
        URL "https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.xz"
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(BOOST_RUNTIME_LINK static)

set(BOOST_SHARED_LINK
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

set(BOOSTASIO_INCLUDE_LIBRARIES
        asio
        ${BOOST_SHARED_LINK}
)

FetchContent_MakeAvailable(Boost)

foreach(lib ${BOOSTASIO_INCLUDE_LIBRARIES})
    target_link_libraries(
            ${LIBRARY_NAME_NETLIB}
            PRIVATE
            Boost::${lib}
    )
    target_include_directories(
            ${LIBRARY_NAME_NETLIB}
            PRIVATE
            Boost::${lib}
    )
endforeach()

