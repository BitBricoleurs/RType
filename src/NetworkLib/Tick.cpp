//
// Created by Clément Lagasse on 28/09/2023.
//

#include "Tick.hpp"

Network::Tick::Tick(size_t tick)
: _tick(tick), _timeToWaitBetweenTick(1/_tick), _processIncoming(false), _processOutgoing(false)
{
}

void Network::Tick::Start()
{
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

void Network::Tick::changeTick(size_t newTick)
{
    _tick = newTick;
    _timeToWaitBetweenTick = 1/_tick;
}
