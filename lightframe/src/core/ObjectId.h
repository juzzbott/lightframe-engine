/**
 * @file ObjectId.h
 * @author Justin McKay
 * @brief Definition of the ObjectId class for unique object identification.
 * @date 2025-12-31
 */

#pragma once

#include <array>
#include <cstdint>
#include <string>

class ObjectId {
public:
    /**
     * @brief Default constructor for ObjectId. Generates a new unique ObjectId.
     */
    ObjectId();

    /**
     * @brief Constructs an ObjectId from a string representation.
     * @param id The string representation of the ObjectId.
     */
    explicit ObjectId(const std::string& id);

    /**
     * @brief Converts the ObjectId to its string representation.
     * @return The string representation of the ObjectId.
     */
    std::string toString() const;

    /**
     * @brief Returns the ObjectId as its 12-byte array representation.
     * @return The 12-byte array representing the ObjectId.
     */
    std::array<uint8_t, 12> toBytes() const { return idBytes; }

    /**
     * @brief Equality operator for ObjectId.
     * @return True if the ObjectIds are equal, false otherwise.
     */
    bool operator==(const ObjectId& other) const {
        return std::equal(idBytes.begin(), idBytes.end(), other.toBytes().begin());
    }

    /**
     * @brief Non-equality operator for ObjectId.
     * @return True if the ObjectIds are not equal, false otherwise.
     */
    bool operator!=(const ObjectId& other) const {
        return !(*this == other);
    }

    /**
     * @brief Less than operator for ObjectId.
     * @return True if this ObjectId is less than the other, false otherwise.
     */
    bool operator<(const ObjectId& other) const {
        return std::lexicographical_compare(
            idBytes.begin(), 
            idBytes.end(),
            other.idBytes.begin(),
            other.idBytes.end()
        );
    }

    /**
     * @brief Greater than operator for ObjectId.
     * @return True if this ObjectId is greater than the other, false otherwise.
     */
    bool operator>(const ObjectId& other) const {
        return std::lexicographical_compare(
            other.idBytes.begin(),
            other.idBytes.end(),
            idBytes.begin(), 
            idBytes.end()
        );
    }

    /**
     * @brief Returns the minimum possible ObjectId.
     * @return An ObjectId with all bytes set to 0x00.
     */
    static ObjectId min() {
        ObjectId id;
        id.idBytes.fill(0x00);
        return id;
    }

    /**
     * @brief Returns the maximum possible ObjectId.
     * @return An ObjectId with all bytes set to 0xFF.
     */
    static ObjectId max() {
        ObjectId id;
        id.idBytes.fill(0xFF);
        return id;
    }

private:
    std::array<uint8_t, 12> idBytes;

    /**
     * @brief Writes a 32-bit value into the idBytes array at the specified offset.
     * @param offset The offset in the array to start writing.
     * @param value The 32-bit value to write.
     */
    void writeBytes(size_t offset, uint32_t value);
};

/**
 * @brief Hash specialization for ObjectId to allow its use in unordered containers.
 */
template <>
struct std::hash<ObjectId> {
    /**
     * @brief Computes the hash value for an ObjectId.
     * @param id The ObjectId to hash.
     * @return The hash value.
     */
    std::size_t operator()(const ObjectId& id) const noexcept {
        // Hash the bytes of the ObjectId
        const auto& bytes = id.toBytes();
        std::size_t h = 0;
        for (const auto b : bytes) {
            h = h * 31 + b;
        }
        return h;
    }
};
