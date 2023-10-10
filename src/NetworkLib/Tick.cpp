//
// Created by Clément Lagasse on 28/09/2023.
//

#include <iostream>
#include <utility>
#include "Tick.hpp"

Network::Tick::Tick(size_t tick)
: _tick(tick), _timeToWaitBetweenTick(1000/_tick)
{
    lastWriteTimeMtx.lock();
    lastPacketSent = std::chrono::high_resolution_clock::now();
    lastWriteTimeMtx.unlock();
}

void Network::Tick::setIncomingFunction(std::function<void()> inFunc)
{
    processIncoming = std::move(inFunc);
}

void Network::Tick::setOutgoingFunction(std::function<void()> outFunc)
{
    processOutgoing = std::move(outFunc);
}

 [[noreturn]] void Network::Tick::Start()
{
    while (1) {
        lastWriteTimeMtx.lock();
        auto localLastWriteTime= lastPacketSent;
        lastWriteTimeMtx.unlock();

        auto now= std::chrono::high_resolution_clock::now();
        auto timeSinceLastWrite= now - localLastWriteTime;
        auto timeToWait = std::chrono::milliseconds(_timeToWaitBetweenTick)
                         - timeSinceLastWrite;

        if ( timeToWait <= std::chrono::milliseconds(0)) {
            timeToWait = std::chrono::milliseconds(_timeToWaitBetweenTick);
        }
        if ( timeToWait > std::chrono::milliseconds(0)) {
            std::this_thread::sleep_for(timeToWait);
        }

        if (processIncoming) {
            processIncoming();
        }
        if (processOutgoing) {
            processOutgoing();
        }
    }
}
void Network::Tick::changeTick(size_t newTick)
{
    _tick = newTick;
    _timeToWaitBetweenTick = 1000/_tick;
}

void Network::Tick::updateLastWriteTime()
{
    lastWriteTimeMtx.lock();
    lastPacketSent = std::chrono::high_resolution_clock::now();
    lastWriteTimeMtx.unlock();
}
