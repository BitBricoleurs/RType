//
// Created by Clément Lagasse on 25/09/2023.
//

#pragma once

#include <cstdint>

namespace Network {
    struct PacketHeader {
        int sequenceNumber;
        uint16_t ackMask;
        int lastPacketSeq;
        unsigned int bodySize;
    }__attribute__((packed));
}