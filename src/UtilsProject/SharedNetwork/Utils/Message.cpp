//
// Created by Clément Lagasse on 28/09/2023.
//

#include <iostream>
#include <memory>
#include <functional>
#if defined(_WIN32) || defined(_WIN64)
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
#endif
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

std::vector<std::uint8_t> Network::Serializer::decomposeUint32(uint32_t binValue) {
    std::vector<std::uint8_t> result;
    for(int i = 0; i < sizeof(uint32_t); ++i)
    {
        uint8_t byte = (binValue >> (i * 8)) & 0xFF;
        result.push_back(byte);
    }
    return result;
}

std::map<std::type_index, void(*)(const std::any&, std::vector<std::uint8_t>&)> Network::Serializer::serializers = {
    { typeid(int), [](const std::any& item, std::vector<std::uint8_t>& result) {
        int value = std::any_cast<int>(item);
        uint32_t binValue;
        std::memcpy(&binValue, &value, sizeof(int));
        std::vector<std::uint8_t> bytes = decomposeUint32(binValue);
        result.insert(result.end(), bytes.begin(), bytes.end());
    }},
    { typeid(float), [](const std::any& item, std::vector<std::uint8_t>& result) {
        float value = std::any_cast<float>(item);
        uint32_t binValue;
        std::memcpy(&binValue, &value, sizeof(float));
        std::vector<std::uint8_t> bytes = decomposeUint32(binValue);
        result.insert(result.end(), bytes.begin(), bytes.end());
    }},
    { typeid(std::string), [](const std::any& item, std::vector<std::uint8_t>& result) {
        std::string value = std::any_cast<std::string>(item);
        result.insert(result.end(), value.begin(), value.end());
    }},
    { typeid(const std::string&), [](const std::any& item, std::vector<std::uint8_t>& result) {
        const std::string& value = std::any_cast<const std::string&>(item);
        result.insert(result.end(), value.begin(), value.end());
    }},
    { typeid(char), [](const std::any& item, std::vector<std::uint8_t>& result) {
        char value = std::any_cast<char>(item);
        result.push_back(static_cast<uint8_t>(value));
    }}
};

std::vector<std::uint8_t> Network::Serializer::serializeItem(const std::any &item)
{

    std::vector<std::uint8_t> result;
    try {
        auto it = serializers.find(item.type());
        if (it != serializers.end()) {
            it->second(item, result);
        } else {
            std::cout << item.type().name() << std::endl;
            throw std::runtime_error("Unsupported data type for serialization check Message.hpp file");
        }
    } catch (std::exception& e) {
        throw std::runtime_error("Unsupported data type for serialization check Message.hpp file");
    }


    return result;
}


std::vector<std::any> Network::Serializer::deserialize(const std::vector<std::uint8_t> &data, uint8_t typeCode, uint8_t size, uint8_t nbrArgs)
{
    std::vector<std::any> result;

    static const std::map<uint8_t, std::function<std::any(const std::vector<std::uint8_t>&, std::size_t)>> deserializers = {
        { 0x01, [](const std::vector<std::uint8_t>& data, std::size_t offset) -> std::any {
            int value;
            std::memcpy(&value, data.data() + offset, sizeof(int));
            return value;
        }},
        { 0x02, [](const std::vector<std::uint8_t>& data, std::size_t offset) -> std::any {
            float value;
            std::memcpy(&value, data.data() + offset, sizeof(float));
            return value;
        }},
        { 0x03, [](const std::vector<std::uint8_t>& data, std::size_t offset) -> std::any {
            std::string value(data.begin() + offset, data.begin() + offset + 1);
            return value;
        }},
    };

    for (int i = 0; i < nbrArgs; i++) {
        auto deserializer = deserializers.find(typeCode);
        if (deserializer != deserializers.end()) {
            result.push_back(deserializer->second(data, i * size));
        } else {
            throw std::runtime_error("Unsupported data type for deserialization check Message.hpp file");
        }
    }

    return result;
}


Network::Message::Message(std::vector <std::uint8_t> &message)
: AMessage(), _ArgType(), _args()
{
    uint16_t messageSize;
    std::memcpy(&messageSize, message.data(), sizeof(uint16_t));
    messageSize = ntohs(messageSize);
    message.resize(messageSize + sizeof(uint16_t));
    _message = message;

    try {
        getDataMessage();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

Network::Message::Message(const std::string &action, std::vector<size_t> IDs, const std::string &typeArg, std::vector<std::any> args, bool secure)
: AMessage(secure), _action(action), _ArgType(typeArg), _args(args), _IDs(IDs), _NbrArgs(args.size()), _NbrId(IDs.size())
{
    std::vector<std::uint8_t> serializedArgs = {};
    try {
        if (getCodeByType(_ArgType) != 0x00)
            serializedArgs = Serializer::serialize(_args);
        initializeMessage(IDs, serializedArgs);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::map<std::string, uint8_t> actionToCodeMap =
{
    {"CONNECT", 0x01},
    {"DISCONNECTING", 0x02},
    {"DISCONNECT", 0x03},
    {"ACCEPTED", 0x04},
    {"CREATED_USER", 0x05},
    {"CREATED_BULLET", 0x06},
    {"CREATED_MOB", 0x07},
    {"UPDATE_VELOCITY", 0x08},
    {"UPDATE_POSITION", 0x09},
    {"MOVE", 0x10},
    {"CHARGE_SHOOT", 0x11},
    {"DELETED_ENTITY", 0x12},
    {"READY", 0x13},
    {"START_GAME", 0x14},
    {"CHARGE", 0x15},
};

std::map<std::string, uint8_t> typeToCodeMap =
{
    {"", 0x00},
    {"IGNORE", 0x00},
    { "INT", 0x01 },
    { "FLOAT", 0x02 },
    { "STRING", 0x03 },
    { "CHAR", 0x03}
};

std::map<uint8_t, uint8_t> typeToSizeMap =
{
    { 0x01, sizeof(int) },
    { 0x02, sizeof(float) },
    { 0x03, sizeof(char) },
};

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

uint8_t Network::Message::getCodeByAction(const std::string &action)
{
    for (auto& item : actionToCodeMap) {
        if (item.first == action) {
            return item.second;
        }
    }
    throw std::runtime_error("Unknown action");
}

uint8_t Network::Message::getCodeByType(const std::string &type)
{
    for (auto& item : typeToCodeMap) {
        if (item.first == type) {
            return item.second;
        }
    }
    throw std::runtime_error("Unknown type");
}

uint8_t Network::Message::getSizeByType(uint8_t code)
{
    for (auto& item : typeToSizeMap) {
        if (item.first == code) {
            return item.second;
        }
    }
    throw std::runtime_error("Unknown type");
}
void Network::Message::getDataMessage()
{
    uint16_t messageSize;
    std::memcpy(&messageSize, _message.data(), sizeof(uint16_t));
    messageSize = ntohs(messageSize);

    if (messageSize + sizeof(uint16_t) != _message.size()) {
        throw std::runtime_error("Malformed message: size field does not match message size");
    }

    _action = getActionByCode(_message[2]);
    std::memcpy(&_NbrId, _message.data() + 3, sizeof(_NbrId));
    _NbrId = ntohs(_NbrId);

    for (int i = 0; i < _NbrId; ++i) {
        size_t id = 0;
        std::memcpy(&id, _message.data() + 5 + i * sizeof(size_t), sizeof(size_t));
        _IDs.push_back(id);
    }
    _ArgTypeCode = _message[5 + (_NbrId * sizeof(size_t))];
    _NbrArgs = _message[6 + (_NbrId * sizeof(size_t))];

    if (_ArgTypeCode == 0x00) {
        _sizeArg = 0;
        _args = {};
        return;
    }

    _ArgType = getTypeByCode(_ArgTypeCode);
    _sizeArg = getSizeByType(_ArgTypeCode);

    if (_ArgTypeCode == 0x03) {
        _sizeArg = _NbrArgs;
        _NbrArgs = 1;
    }

    _args.resize(_NbrArgs);
    _args = Serializer::deserialize(
        std::vector<uint8_t>(_message.begin() + 7 + (_NbrId * sizeof(size_t)), _message.end()),
        _ArgTypeCode,
        _sizeArg,
        _NbrArgs
    );
}


void Network::Message::initializeMessage(const std::vector<size_t>& IDs, const std::vector<std::uint8_t>& serializedArgs)
{
    std::vector<std::uint8_t> messageWithoutSize = {};
    messageWithoutSize.push_back(actionToCodeMap[_action]);
    messageWithoutSize.push_back(static_cast<uint8_t>(_NbrId >> 8));
    messageWithoutSize.push_back(static_cast<uint8_t>(_NbrId));
    for (size_t id : IDs) {
        for (int i = 0; i < sizeof(size_t); ++i) {
            messageWithoutSize.push_back(static_cast<uint8_t>(id >> (i * 8)));
        }
    }

    uint8_t Type = typeToCodeMap[_ArgType];
    if (Type == 0x03)
        _NbrArgs = serializedArgs.size();
    messageWithoutSize.push_back(Type);
    messageWithoutSize.push_back(_NbrArgs);
    messageWithoutSize.insert(messageWithoutSize.end(), serializedArgs.begin(), serializedArgs.end());

    uint16_t messageSize = messageWithoutSize.size();
    _message.push_back(static_cast<uint8_t>(messageSize >> 8));
    _message.push_back(static_cast<uint8_t>(messageSize));
    _message.insert(_message.end(), messageWithoutSize.begin(), messageWithoutSize.end());
}
