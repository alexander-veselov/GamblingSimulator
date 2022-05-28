#include "Platform.h"

#if __EMSCRIPTEN__
#include "WebAssembly/WebAssemblyUI.h"
#else
#include "Windows/WindowsUI.h"
#endif

std::shared_ptr<IPlatform> GetCurrentPlatform()
{
#if __EMSCRIPTEN__
    return std::shared_ptr<IPlatform>(new WebAssemblyUI());
#else
    return std::shared_ptr<IPlatform>(new WindowsUI());
#endif
}