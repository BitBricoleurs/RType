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

        static std::vector<std::uint8_t> serialize(const std::vector<std::any>& data) {
            std::vector<std::uint8_t> result;

            for (const auto& item : data) {
                std::vector<std::uint8_t> serializedItem = serializeItem(item);
                result.insert(result.end(), serializedItem.begin(), serializedItem.end());
            }

            return result;
        }

        static std::vector<std::uint8_t> serializeItem(const std::any& item) {
            std::stringstream ss;

            if (item.type() == typeid(int)) {
                ss << std::any_cast<int>(item);
            } else if (item.type() == typeid(float)) {
                ss << std::fixed << std::any_cast<float>(item);
            } else if (item.type() == typeid(std::string)) {
                ss << std::any_cast<std::string>(item);
            } else {
                throw std::runtime_error("Unsupported data type for serialization check Message.hpp file");
            }

            std::string serialized = ss.str();
            return std::vector<std::uint8_t>(serialized.begin(), serialized.end());
        }
        private:
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
            Message(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::vector<std::any> args)
                    : _action(action), _ArgType(typeArg), _args(args), _IDs(IDs), _NbrArgs(args.size())
            {
                std::vector<std::uint8_t> serializedArgs = Serializer::serialize(_args);
                initializeMessage(IDs, serializedArgs);
            }

            Message(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::any arg)
                    : _action(action), _ArgType(typeArg), _args(), _IDs(IDs), _NbrArgs(1)
            {
                std::vector<std::uint8_t> serializedArgs = Serializer::serializeItem(arg);
                initializeMessage(IDs, serializedArgs);
            }

            Message(std::vector<std::uint8_t> &message)
            : _message(message), _ArgType(), _args()
            {
                getDataMessage();
            }
            ~Message() = default;

            std::vector<std::uint8_t> &getMessage() override {
                return _message;
            }

            unsigned int getSize() override {
                return _message.size();
            }

    private:

        std::string getActionByCode(uint8_t code) {
            for (auto& item : actionToCodeMap) {
                if (item.second == code) {
                    return item.first;
                }
            }
            throw std::runtime_error("Unknown action code");
        }

        std::string getTypeByCode(uint8_t code) {
            for (auto& item : typeToCodeMap) {
                if (item.second == code) {
                    return item.first;
                }
            }
            throw std::runtime_error("Unknown type code");
        }

        void getDataMessage() {
            _action = _message.front();
            memcpy(&_NbrId, &_message[1], sizeof(_NbrId));
            _IDs.insert(_IDs.end(), _message.begin() + 2, _message.begin() + 2 + _NbrId);
            _ArgTypeCode = _message[3 + _NbrId];
            _NbrArgs = _message[4 + _NbrId];

           if (_ArgTypeCode == 0x03) {
               _sizeArg = 1;
           } else {
               _sizeArg = typeToSizeMap[_ArgTypeCode];
           }
           for (int i = 0; i < _NbrArgs; i++) {
               memcpy(&_args[i], &_message[5 + _NbrId + i * _sizeArg], _sizeArg);
           }

        }


        void initializeMessage(const std::vector<unsigned int>& IDs, const std::vector<std::uint8_t>& serializedArgs) {
            _message.push_back(actionToCodeMap[_action]);
            _message.push_back(_NbrId);
            _message.insert(_message.end(), IDs.begin(), IDs.end());
            _message.push_back(typeToCodeMap[_ArgType]);
            _message.push_back(_NbrArgs);
            _message.insert(_message.end(), serializedArgs.begin(), serializedArgs.end());
        }

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
