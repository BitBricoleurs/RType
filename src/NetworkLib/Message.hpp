//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <any>
#include <cstdint>
#include <sstream>
#include <map>
#include "IMessage.hpp"
#include <cstring>

namespace Network {

    class Serializer {
    public:

        static std::vector<std::uint8_t> serialize(const std::vector<std::any>& data);

        static std::vector<std::uint8_t> serializeItem(const std::any& item);
    };


    class Message : public IMessage {

        std::map<std::string, uint8_t> actionToCodeMap = {
                {"action1", 0x01},
                {"action2", 0x02},
        };

        std::map<std::string, uint8_t> typeToCodeMap = {
                { "INT", 0x01 },
                { "FLOAT", 0x02 },
                { "STRING", 0x03 },
        };

        std::map<uint8_t, uint8_t> typeToSizeMap = {
                { 0x01, sizeof(int) },
                { 0x02, sizeof(float) },
        };

    public:
            Message(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::vector<std::any> args);

            Message(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::any arg);

            Message(std::vector<std::uint8_t> &message);
            ~Message() = default;

            std::vector<std::uint8_t> &getMessage() override;

            unsigned int getSize() override;

    private:

        std::string getActionByCode(uint8_t code);

        std::string getTypeByCode(uint8_t code);

        void getDataMessage();


        void initializeMessage(const std::vector<unsigned int>& IDs, const std::vector<std::uint8_t>& serializedArgs);

        std::string _action;
        std::string _ArgType;
        uint8_t _ArgTypeCode;
        uint8_t _NbrArgs;
        uint16_t _NbrId;
        uint8_t _sizeArg;
        std::vector<unsigned int> _IDs;
        std::vector<std::any> _args;
        std::vector<std::uint8_t> _message;
    };
}
