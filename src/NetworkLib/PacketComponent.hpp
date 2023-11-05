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
        int sequenceNumber = 0;
        int lastPacketSeq = 0;
        uint16_t ackMask = 0;
        uint16_t bodySize = 0;
    });

    struct Packet {
        Packet() {
            header.magicNumber = MAGIC_NUMBER;
            header.sequenceNumber = 0;
            header.lastPacketSeq = 0;
            header.ackMask = 0;
            header.bodySize = 0;
        }
        PacketHeader header;
        std::vector<std::uint8_t> body;
    };
}