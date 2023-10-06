//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <any>
#include <cstdint>
#include <sstream>
#include <map>
#include <cstring>
#include "AMessage.hpp"

namespace Network {

    class Serializer {
    public:

        static std::vector<std::uint8_t> serialize(const std::vector<std::any>& data);

        static std::vector<std::uint8_t> serializeItem(const std::any& item);

        static std::vector<std::any> deserialize(const std::vector<std::uint8_t>& data, uint8_t typeCode, uint8_t size, uint8_t nbrArgs);
    };


    class Message : public AMessage {

        std::map<std::string, uint8_t> actionToCodeMap = {
                {"HELLO", 0x01},
                {"BYE", 0x02},
        };

        std::map<std::string, uint8_t> typeToCodeMap = {
            {"IGNORE", 0x00},
            { "INT", 0x01 },
            { "FLOAT", 0x02 },
            { "STRING", 0x03 },
            { "CHAR", 0x03}
        };

        std::map<uint8_t, uint8_t> typeToSizeMap = {
                { 0x01, sizeof(int) },
                { 0x02, sizeof(float) },
                { 0x03, sizeof(char) },
        };

    public:

        Message(const std::string &action, std::vector<size_t> IDs, const std::string &typeArg, std::vector<std::any> args);
        Message(std::vector<std::uint8_t> &message);
        ~Message() override = default;



        std::string getActionByCode(uint8_t code);

        std::string getTypeByCode(uint8_t code);
        uint8_t getSizeByType(uint8_t code);

        uint8_t getCodeByAction(const std::string &action);
        uint8_t getCodeByType(const std::string &type);

        void getDataMessage();


        void initializeMessage(const std::vector<size_t>& IDs, const std::vector<std::uint8_t>& serializedArgs);

        std::string _action;
        std::string _ArgType;
        uint8_t _ArgTypeCode;
        uint8_t _NbrArgs;
        uint16_t _NbrId;
        uint8_t _sizeArg;
        std::vector<size_t> _IDs;
        std::vector<std::any> _args;
      private:
    };
}
