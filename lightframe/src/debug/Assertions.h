/**
 * @file Assertions.h
 * @author Justin McKay
 * @brief [...add brief description...]
 * @date 2025-12-22
 */

#pragma once

#include "core/Logger.h"

#include <format>

// Disable assertions by commenting out the below line.
#define LF_ENABLE_ASSERTS

// Always define lf_debug_break in case it is ever needed outside assertions (i.e fatal log errors)
// Try via __has_builtin first.
#if defined(__has_builtin) && !defined(__ibmxl__)
#   if __has_builtin(__builtin_debugtrap)
#        define lf_debug_break() __builtin_debugtrap()
#   elif __has_builtin(__debugbreak)
#        define lf_debug_break() __debugbreak()
#   endif
#endif

// If not setup, try the old way.
#if !defined(lf_debug_break)
#   if defined(__clang__) || defined(__gcc__)
/** @brief Causes a debug breakpoint to be hit. */
#       define lf_debug_break() __builtin_trap()
#   elif defined(_MSC_VER)
#       include <intrin.h>       
/** @brief Causes a debug breakpoint to be hit. */
#       define lf_debug_break() __debugbreak()
#   else
// Fall back to x86/x86_64
#       define lf_debug_break() __asm__ volatile("int $3")
#   endif
#endif

#ifdef LF_ENABLE_ASSERTS

/**
 * @brief Asserts the provided expression to be true, and logs a failure if not.
 * Also triggers a breakpoint if debugging.
 * @param expr The expression to be evaluated.
 */
#define LF_ASSERT(expr) {                                                                       \
    if (!(expr)) {                                                                                \
        LOG_FATAL(std::format("Assertion Failed: {0} at {1}:{2}", #expr, __FILE__, __LINE__));  \
        lf_debug_break() ;                                                                      \
    }                                                                                           \
}

/**
 * @brief Asserts the provided expression to be true, and logs a failure if not.
 * Allows the user to specify a message to accompany the failure.
 * Also triggers a breakpoint if debugging.
 * @param expr The expression to be evaluated.
 * @param message The message to be reported along with the assertion failure.
 */
#define LF_ASSERT_MSG(expr, msg) {                                                                                  \
    if (!(expr)) {                                                                                                    \
        LOG_FATAL(std::format("Assertion Failed: {0} at {1}:{2} | Message: {3}", #expr, __FILE__, __LINE__, msg));  \
        lf_debug_break() ;                                                                                          \
    }                                                                                                               \
}

#else

#define LF_ASSERT(expr)             // No-op
#define LF_ASSERT_MSG(expr, msg)    // No-op

#endif