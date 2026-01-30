#include "ObjectId.h"

#include "core/Logger.h"

#include <chrono>
#include <random>
#include <thread>
#include <sstream>

ObjectId::  ObjectId() : idBytes{0} {

    using namespace std::chrono;

    // Timestamp
    const auto timestamp = static_cast<uint32_t>(
        duration_cast<seconds>(system_clock::now().time_since_epoch()).count()
        );

    // Machine + process + Thread hash
    static uint32_t processHash = static_cast<uint32_t>(std::hash<std::thread::id>{}(std::this_thread::get_id())) ^
        std::random_device{}();

    // Atomic counter
    std::random_device rd;
    const uint32_t randomValue = rd();

    writeBytes(0, timestamp);
    writeBytes(4, processHash);
    writeBytes(8, randomValue);
}

ObjectId::ObjectId(const std::string& id) : idBytes{0} {
    if (id.length() != 24) {
        LOG_ERROR("Invalid object id: {}", id);
        return;
    }

    for (size_t i = 0; i < 12; ++i) {
        std::string strByte = id.substr(i * 2, 2);

        // Validate the string only contains hex digits
        if (!std::isxdigit(strByte[0]) || !std::isxdigit(strByte[1])) {
            LOG_ERROR("Id string contains non-hex characters: {}", id);
            return;
        }

        // Convert 2-character hex string to a byte
        const auto byte = static_cast<uint8_t>(std::stoi(strByte, nullptr, 16));
        idBytes[i] = byte;
    }

}

std::string ObjectId::toString() const {
    std::ostringstream oss;
    for (const uint8_t byte : idBytes) {
        oss << std::format("{:02x}", byte);
    }
    return oss.str();
}

void ObjectId::writeBytes(const size_t offset, const uint32_t value) {
    idBytes[offset + 0] = (value >> 24) & 0xFF;
    idBytes[offset + 1] = (value >> 16) & 0xFF;
    idBytes[offset + 2] = (value >> 8) & 0xFF;
    idBytes[offset + 3] = value & 0xFF;
}