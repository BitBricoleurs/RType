//
// Created by Clément Lagasse on 21/09/2023.
//

#pragma once

#include <any>
#include <cstdint>
#include <sstream>
#include <map>
#include <cstring>
#include <typeindex>
#include "AMessage.hpp"

namespace Network {

    class Serializer {
    public:

        static std::vector<std::uint8_t> decomposeUint32(uint32_t binValue);

        static std::vector<std::uint8_t> serialize(const std::vector<std::any>& data);

        static std::vector<std::uint8_t> serializeItem(const std::any& item);

        static std::vector<std::any> deserialize(const std::vector<std::uint8_t>& data, uint8_t typeCode, uint8_t size, uint8_t nbrArgs);

        static std::map<std::type_index, void(*)(const std::any&, std::vector<std::uint8_t>&)> serializers;
    };


    class Message : public AMessage {

    public:

        Message(const std::string &action, std::vector<size_t> IDs, const std::string &typeArg, std::vector<std::any> args, bool secure = false);
        Message(std::vector<std::uint8_t> &message);
        ~Message() override = default;

        std::string &getAction() {return _action;};
        std::string &getArgType() {return _ArgType;};
        uint8_t getArgTypeCode() {return _ArgTypeCode;};
        uint8_t getNbrArgs() {return _NbrArgs;};
        uint16_t getNbrId() {return _NbrId;};
        uint8_t getSizeArg() {return _sizeArg;};
        std::vector<size_t> &getIDs() {return _IDs;};
        std::vector<std::any> &getArgs() {return _args;};
        uint16_t &getMessageSize() {return _messageSize;};
        bool isMessageSecure() {return AMessage::isSecure();};
    private:
        static std::string getActionByCode(uint8_t code);

        static std::string getTypeByCode(uint8_t code);
        static uint8_t getSizeByType(uint8_t code);

        static uint8_t getCodeByAction(const std::string &action);
        static uint8_t getCodeByType(const std::string &type);

        void getDataMessage();


        void initializeMessage(const std::vector<size_t>& IDs, const std::vector<std::uint8_t>& serializedArgs);

        uint16_t _messageSize;
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
