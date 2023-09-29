//
// Created by Clément Lagasse on 27/09/2023.
//

#pragma once

#include <cstddef>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <mutex>
#include <condition_variable>

namespace Network {
    struct Tick {

        Tick(size_t tick);


        void Start();
        void updateLastWriteTime();

        size_t _tick;
        size_t _timeToWaitBetweenTick;
        std::condition_variable _cvOutgoing;
        std::condition_variable _cvIncoming;
        std::mutex _mtx;
        bool _processOutgoing = false;
        bool _processIncoming = false;
        std::mutex lastWriteTimeMtx;
        std::chrono::high_resolution_clock::time_point lastPacketSent;

        void changeTick(size_t newTick);
    };
}
