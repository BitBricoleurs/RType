//
// Created by Theophilus Homawoo on 25/10/2023.
//

#pragma once

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <string>

namespace GameEngine {
    class TcpConnection : public boost::enable_shared_from_this<TcpConnection> {
    public:
        typedef boost::shared_ptr<TcpConnection> pointer;

        static pointer create(boost::asio::io_service& io_service);

        boost::asio::ip::tcp::socket& socket();

        void sendLog(const std::string& message);

        void receiveMessage();

        void stop();

        TcpConnection(boost::asio::io_service& io_service);
        ~TcpConnection();
            private:

        void handleWrite(const boost::system::error_code& /*error*/, size_t /*bytes_transferred*/);

        boost::asio::ip::tcp::socket socket_;

        void handleRead(const boost::system::error_code& /*error*/, size_t  /*bytes_transferred*/);

        boost::asio::streambuf buffer_;
        std::atomic_bool isRunning = true;
    };
}
