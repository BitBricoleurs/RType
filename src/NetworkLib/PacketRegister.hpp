//
// Created by Clément Lagasse on 19/10/2023.
//

#pragma once

#include <unordered_map>
#include <vector>
#include <mutex>
#include <algorithm>
#include <stdexcept>
#include "PacketComponent.hpp"

namespace Network {
    class PacketRegister {
    public:
        PacketRegister();
        ~PacketRegister() = default;

        void registerReceivedPacket(unsigned int remoteId, unsigned int packetId);
        bool isPacketRegisteredIn(unsigned int remoteId, unsigned int packetId);
        void registerSentPacket(unsigned int remoteId, std::shared_ptr<Network::Packet> packet);
        std::shared_ptr<Network::Packet> getPacket(unsigned int remoteId, unsigned int packetId);
        std::vector<std::shared_ptr<Network::Packet>> getPacketsToResend(unsigned int remoteId, uint16_t ackMask);
        uint16_t getAckMask(unsigned int remoteId);
        unsigned int getLastPacketId(unsigned int remoteId);

        void clear();
    private:
        const size_t _maxSize = 16;
        std::mutex _mutex;
        std::unordered_map<unsigned int, std::vector<unsigned int>> _packetIdRegisterIn;
        std::unordered_map<unsigned int, std::vector<std::shared_ptr<Network::Packet>>>_packetRegisterOut;
    };
};

