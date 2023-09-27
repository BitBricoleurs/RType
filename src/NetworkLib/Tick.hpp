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

        Tick(size_t tick)
        {
            changeTick(tick);
        }


        void Start() {
                lastWriteTimeMtx.lock();
                auto localLastWriteTime = lastPacketSent;
                lastWriteTimeMtx.unlock();

                auto now = std::chrono::high_resolution_clock::now();
                auto timeSinceLastWrite = now - localLastWriteTime;
                auto timeToWait = std::chrono::milliseconds(_timeToWaitBetweenTick) - timeSinceLastWrite;

                if (timeToWait > std::chrono::milliseconds(0)) {
                    std::this_thread::sleep_for(timeToWait);
                }
                std::unique_lock<std::mutex> lock(_mtx);
                _processIncoming = true;
                _processOutgoing = true;
                lock.unlock();

                _cvIncoming.notify_one();
                _cvOutgoing.notify_one();
                Start();
        }

        size_t _tick;
        size_t _timeToWaitBetweenTick;
        std::condition_variable _cvOutgoing;
        std::condition_variable _cvIncoming;
        std::mutex _mtx;
        bool _processOutgoing = false;
        bool _processIncoming = false;
        std::mutex lastWriteTimeMtx;
        std::chrono::high_resolution_clock::time_point lastPacketSent;

        void changeTick(size_t newTick) {
            _tick = newTick;
            _timeToWaitBetweenTick = 1/_tick;
        }
    };
}
