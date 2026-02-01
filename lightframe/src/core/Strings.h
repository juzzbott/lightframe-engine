#include <string>
#include <algorithm>

/**
 * @brief Case-insensitive string comparison.
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return true if the strings are equal (case-insensitive), false otherwise.
 */
static inline bool strEqualsCi(const std::string& str1, const std::string str2) {
    // Check if lengths are different; if so, they can't be equal
    if (str1.length() != str2.length()) {
        return false;
    }
    
    // Use std::equal with a custom character-by-character comparator
    return std::equal(str1.begin(), str1.end(), str2.begin(), [](unsigned char a, unsigned char b) {
        return std::tolower(a) == std::tolower(b);
    });
}

/**
 * @brief Trims whitespace from the left side of the string.
 * @param str The string to trim.
 */
static inline std::string& lTrim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return str;
}

/**
 * @brief Trims whitespace from the right side of the string.
 * @param str The string to trim.
 */
static inline std::string& rTrim(std::string& str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
    return str;
}

/**
 * @brief Trims whitespace from both sides of the string.
 * @param str The string to trim.
 */
static inline std::string& trim(std::string str) {
    return lTrim(rTrim(str));
}