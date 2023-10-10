//
// Created by Clément Lagasse on 25/09/2023.
//

#pragma once

#include <cstdint>
#include "Pack.hpp"
#define MAX_PACKET_SIZE 4096

namespace Network {
    struct PACK(PacketHeader {
        int sequenceNumber;
        int lastPacketSeq;
        uint16_t ackMask;
        uint16_t bodySize;
    });

    struct Packet {
        PacketHeader header;
        std::vector<std::uint8_t> body;
    };
}