//
// Created by Clément Lagasse on 25/09/2023.
//

#pragma once

#include <cstdint>
#define MAX_PACKET_SIZE 4096

namespace Network {
    struct PacketHeader {
        int sequenceNumber;
        int lastPacketSeq;
        uint16_t ackMask;
        uint16_t bodySize;
    }__attribute__((packed));

    struct Packet {
        PacketHeader header;
        std::vector<std::uint8_t> body;
    }__attribute__((packed));
}