#include "Platform.h"

#ifdef LF_PLATFORM_WINDOWS
    #include "WindowsPlatform.h"
#elifdef LF_PLATFORM_LINUX
#include "LinuxPlatform.h"
#else
#error "Unsupported platform!"
#endif

static std::unique_ptr<Platform> s_Instance = nullptr;

Platform* Platform::get() {
    if (!s_Instance) {
#ifdef LF_PLATFORM_WINDOWS
        s_Instance = std::make_unique<WindowsPlatform>();
#elifdef LF_PLATFORM_LINUX
        s_Instance = std::make_unique<LinuxPlatform>();
#endif
    }

    return s_Instance.get();
}