//
// Created by Clément Lagasse on 27/09/2023.
//

#pragma once

#include <cstddef>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <mutex>
#include <condition_variable>
#include <functional>

namespace Network {
    struct Tick {

        Tick(size_t tick);

         void Start();
         void Stop();
        void updateLastWriteTime();
        void setIncomingFunction(std::function<void()> func);
        void setOutgoingFunction(std::function<void()> func);
        void setTimeoutFunction(std::function<void()> func);

        size_t _tick;
        size_t _timeToWaitBetweenTick;
        std::mutex lastWriteTimeMtx;
        std::chrono::high_resolution_clock::time_point lastPacketSent;

        void changeTick(size_t newTick);

    private:
        std::function<void()> processIncoming;
        std::function<void()> processOutgoing;
        std::function<void()> processTimeout;
        std::atomic_bool _running;
    };
}
