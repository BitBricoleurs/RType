//
// Created by Clément Lagasse on 25/09/2023.
//

#pragma once

#pragma pack(1)

#include <cstdint>

namespace Network {
    struct PacketHeader {
        int sequenceNumber;
        uint16_t ackMask;
        int lastPacketSeq;
        unsigned int bodySize;
    }__attribute__((packed));

    struct Packet {
        PacketHeader header;
        std::vector<std::uint8_t> body;
    }__attribute__((packed));
}