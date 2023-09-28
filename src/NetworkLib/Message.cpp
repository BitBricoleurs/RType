//
// Created by Clément Lagasse on 28/09/2023.
//

#include "Message.hpp"

std::vector <std::uint8_t> Network::Serializer::serialize(const std::vector <std::any> &data)
{
    std::vector<std::uint8_t> result;

    for (const auto& item : data) {
        std::vector<std::uint8_t> serializedItem = serializeItem(item);
        result.insert(result.end(), serializedItem.begin(), serializedItem.end());
    }

    return result;
}

std::vector<std::uint8_t> Network::Serializer::serializeItem(const std::any &item)
{
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

Network::Message::Message(std::vector <std::uint8_t> &message): _message(message), _ArgType(), _args()
{
    getDataMessage();
}

Network::Message::Message(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::vector<std::any> args)
: _action(action), _ArgType(typeArg), _args(args), _IDs(IDs), _NbrArgs(args.size())
{
    std::vector<std::uint8_t> serializedArgs = Serializer::serialize(_args);
    initializeMessage(IDs, serializedArgs);
}

Network::Message::Message(std::string &action, std::vector<unsigned int> IDs, std::string &typeArg, std::any arg)
        : _action(action), _ArgType(typeArg), _args(), _IDs(IDs), _NbrArgs(1)
{
    std::vector<std::uint8_t> serializedArgs = Serializer::serializeItem(arg);
    initializeMessage(IDs, serializedArgs);
}

std::vector<std::uint8_t> &Network::Message::getMessage()
{
    return _message;
}

unsigned int Network::Message::getSize() {
    return _message.size();
}

std::string Network::Message::getActionByCode(uint8_t code)
{
    for (auto& item : actionToCodeMap) {
        if (item.second == code) {
            return item.first;
        }
    }
    throw std::runtime_error("Unknown action code");
}

std::string Network::Message::getTypeByCode(uint8_t code)
{
    for (auto& item : typeToCodeMap) {
        if (item.second == code) {
            return item.first;
        }
    }
    throw std::runtime_error("Unknown type code");
}

void Network::Message::getDataMessage()
{
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

void Network::Message::initializeMessage(const std::vector<unsigned int>& IDs, const std::vector<std::uint8_t>& serializedArgs)
{
    _message.push_back(actionToCodeMap[_action]);
    _message.push_back(_NbrId);
    _message.insert(_message.end(), IDs.begin(), IDs.end());
    _message.push_back(typeToCodeMap[_ArgType]);
    _message.push_back(_NbrArgs);
    _message.insert(_message.end(), serializedArgs.begin(), serializedArgs.end());
}