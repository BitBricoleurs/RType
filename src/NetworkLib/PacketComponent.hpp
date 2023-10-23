//
// Created by Clément Lagasse on 25/09/2023.
//

#pragma once

#include <cstdint>
#include "Pack.hpp"
#define MAX_PACKET_SIZE 4096
#define MAGIC_NUMBER 0x7F454C45

namespace Network {
    struct PACK(PacketHeader {
        unsigned magicNumber = MAGIC_NUMBER;
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