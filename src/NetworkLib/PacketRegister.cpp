//
// Created by Clément Lagasse on 19/10/2023.
//

#include "PacketRegister.hpp"
#include <iostream>

Network::PacketRegister::PacketRegister()
{
    _packetIdRegisterIn = std::unordered_map<unsigned int, std::vector<unsigned int>>();
    _packetRegisterOut = std::unordered_map<unsigned int, std::vector<std::pair<bool, std::shared_ptr<Network::Packet>>>>();
}

void Network::PacketRegister::registerReceivedPacket(unsigned int remoteId, unsigned int packetId)
{
    std::lock_guard<std::mutex> lock(_mutexIn);
    if (_packetIdRegisterIn.find(remoteId) == _packetIdRegisterIn.end())
        _packetIdRegisterIn[remoteId] = std::vector<unsigned int>();

    if (_packetIdRegisterIn[remoteId].size() >= _maxSize)
    {
        _packetIdRegisterIn[remoteId].erase(_packetIdRegisterIn[remoteId].begin());
    }
    _packetIdRegisterIn[remoteId].push_back(packetId);
    _mutexIn.unlock();
}


bool Network::PacketRegister::isPacketRegisteredIn(unsigned int remoteId, unsigned int packetId)
{
    std::lock_guard<std::mutex> lock(_mutexIn);
    if (remoteId == -1)
        return false;
    auto it = _packetIdRegisterIn.find(remoteId);
    if (it != _packetIdRegisterIn.end() && !it->second.empty()) {
        if(it->second.front() > packetId)
            return true;
        return std::find(it->second.begin(), it->second.end(), packetId) != it->second.end();
    }
    return false;
}


uint16_t Network::PacketRegister::getAckMask(unsigned int remoteId)
{
    std::lock_guard<std::mutex> lock(_mutexIn);
    uint16_t mask = 0;
    auto it = _packetIdRegisterIn.find(remoteId);
    if (it != _packetIdRegisterIn.end() && !it->second.empty())
    {
        std::sort(it->second.begin(), it->second.end());

        unsigned int highestPacketId = it->second.back();

        for (unsigned int i = 0; i < 16; ++i)
        {
            for (unsigned int j = 0; j < it->second.size(); ++j)
            {
                if (it->second[j] == highestPacketId - i)
                {
                    mask |= 1 << i;
                    break;
                }
            }
        }
    }
    return mask;
}

void Network::PacketRegister::clear()
{
    std::lock_guard<std::mutex> lock(_mutexOut);
    _packetIdRegisterIn.clear();
}

unsigned int Network::PacketRegister::getLastPacketId(unsigned int remoteId)
{
    std::lock_guard<std::mutex> lock(_mutexOut);
    std::sort(_packetIdRegisterIn[remoteId].begin(), _packetIdRegisterIn[remoteId].end());
    auto it = _packetIdRegisterIn.find(remoteId);
    if (it != _packetIdRegisterIn.end() && !it->second.empty())
        return it->second.back();
    return 0;
}

void Network::PacketRegister::registerSentPacket(unsigned int remoteId,  std::shared_ptr<Network::Packet> packet, bool secure)
{
    std::lock_guard<std::mutex> lock(_mutexOut);
    if (_packetRegisterOut.find(remoteId) == _packetRegisterOut.end())
        _packetRegisterOut[remoteId] = std::vector<std::pair<bool, std::shared_ptr<Network::Packet>>>();

    if (_packetRegisterOut[remoteId].size() >= _maxSize) {
        _packetRegisterOut[remoteId].erase(_packetRegisterOut[remoteId].begin());
    }
    _packetRegisterOut[remoteId].push_back(std::make_pair(secure, packet));
    _mutexOut.unlock();
}

std::shared_ptr<Network::Packet> Network::PacketRegister::getPacket(unsigned int remoteId, unsigned int packetId)
{
    std::lock_guard<std::mutex> lock(_mutexIn);

    auto it = _packetRegisterOut.find(remoteId);
    if (it == _packetRegisterOut.end() || _packetRegisterOut[remoteId].empty())
        return nullptr;
    for (auto& packet : _packetRegisterOut[remoteId]) {
         if (packet.second->header.sequenceNumber == packetId && packet.first)
            return packet.second;
    }
    return nullptr;
}

std::vector<std::shared_ptr<Network::Packet>> Network::PacketRegister::getPacketsToResend(unsigned int remoteId, uint16_t ackMask)
{
    std::vector<std::shared_ptr<Network::Packet>> result;
    std::shared_ptr<Network::Packet> tmpPacket;
    long packetId = 0;
    unsigned int lastPacketId = getLastPacketId(remoteId);

    for (unsigned int i = 0; i < _maxSize ; ++i) {
        if (!(ackMask & (1 << i))) {
            packetId = lastPacketId - i;
            if (packetId >= 0)
                try {
                    tmpPacket = getPacket(remoteId, packetId);
                    if (tmpPacket)
                        result.push_back(tmpPacket);
                } catch (std::exception& e) {
                    std::cout << "Mysery error: " << e.what() << std::endl;
                    return result;
                }
        }
    }
    return result;
}