//
// Created by Clément Lagasse on 19/10/2023.
//

#include "PacketRegister.hpp"

Network::PacketRegister::PacketRegister()
{
    _packetIdRegisterIn = std::unordered_map<unsigned int, std::vector<unsigned int>>();
    _packetRegisterOut = std::unordered_map<unsigned int, std::vector<Network::Packet>>();
}

void Network::PacketRegister::registerReceivedPacket(unsigned int remoteId, unsigned int packetId)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_packetIdRegisterIn.find(remoteId) == _packetIdRegisterIn.end())
        _packetIdRegisterIn[remoteId] = std::vector<unsigned int>();

    if (_packetIdRegisterIn[remoteId].size() >= _maxSize)
    {
        _packetIdRegisterIn[remoteId].erase(_packetIdRegisterIn[remoteId].begin());
    }
    _packetIdRegisterIn[remoteId].push_back(packetId);
    _mutex.unlock();
}


bool Network::PacketRegister::isPacketRegisteredIn(unsigned int remoteId, unsigned int packetId)
{
    std::lock_guard<std::mutex> lock(_mutex);
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
    std::lock_guard<std::mutex> lock(_mutex);
    uint16_t mask = 0;
    auto it = _packetIdRegisterIn.find(remoteId);
    if (it != _packetIdRegisterIn.end() && !it->second.empty())
    {
        std::sort(it->second.begin(), it->second.end());

        unsigned int highestPacketId = it->second.back();

        for (unsigned int i = 0; i < 16; ++i)
        {
            unsigned int packetId = highestPacketId - i;
            if (std::find(it->second.begin(), it->second.end(), packetId) != it->second.end())
                mask |= 1 << i;
        }
    }
    return mask;
}

void Network::PacketRegister::clear()
{
    std::lock_guard<std::mutex> lock(_mutex);
    _packetIdRegisterIn.clear();
}

unsigned int Network::PacketRegister::getLastPacketId(unsigned int remoteId)
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::sort(_packetIdRegisterIn[remoteId].begin(), _packetIdRegisterIn[remoteId].end());
    auto it = _packetIdRegisterIn.find(remoteId);
    if (it != _packetIdRegisterIn.end() && !it->second.empty())
        return it->second.back();
    return 0;
}

void Network::PacketRegister::registerSentPacket(unsigned int remoteId, Network::Packet packet)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (_packetRegisterOut.find(remoteId) == _packetRegisterOut.end())
        _packetRegisterOut[remoteId] = std::vector<Network::Packet>();

    if (_packetRegisterOut[remoteId].size() >= _maxSize) {
        _packetRegisterOut[remoteId].erase(_packetRegisterOut[remoteId].begin());
    }
    _packetRegisterOut[remoteId].push_back(packet);
    _mutex.unlock();
}

Network::Packet &Network::PacketRegister::getPacket(unsigned int remoteId, unsigned int packetId)
{
    std::lock_guard<std::mutex> lock(_mutex);
    auto it = _packetRegisterOut.find(remoteId);
    if (it != _packetRegisterOut.end() && !it->second.empty())
    {
        auto packetIt = std::find_if(it->second.begin(), it->second.end(), [packetId](const Network::Packet& packet) {
            return packet.header.sequenceNumber == packetId;
        });
        if (packetIt != it->second.end())
            return *packetIt;
    }
    if (_packetRegisterOut.find(remoteId) == _packetRegisterOut.end() || _packetRegisterOut[remoteId].empty())
        throw std::runtime_error("PacketRegister::getPacket: PacketRegister is empty");
    return _packetRegisterOut[remoteId].front();
}

std::vector<Network::Packet> Network::PacketRegister::getPacketsToResend(unsigned int remoteId, uint16_t ackMask)
{
    std::vector<Network::Packet> result;
    unsigned int packetId = 0;
    unsigned int lastPacketId = getLastPacketId(remoteId);

    for (unsigned int i = 0; i < _maxSize ; ++i) {
        if (!(ackMask & (1 << i))) {
            packetId = lastPacketId - i;
            if (packetId >= 0)
                try {
                    result.push_back(getPacket(remoteId, packetId));
                } catch (std::exception& e) {
                    return result;
                }
        }
    }
    return result;
}