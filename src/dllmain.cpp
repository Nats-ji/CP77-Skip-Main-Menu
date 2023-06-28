#include "pch.h"
#include "App.h"
#include "iostream"

static HANDLE s_hMutexHandle = nullptr;

std::wstring UTF8ToUTF16(std::string_view utf8)
{
    const auto utf8Length = static_cast<int>(utf8.length());
    const auto utf16Length = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8Length, nullptr, 0);
    if (!utf16Length)
        return {};

    std::wstring utf16;
    utf16.resize(utf16Length);
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8Length, utf16.data(), utf16Length);

    return utf16;
}

static void Initialize()
{
    try
    {
        // Single instance check
        s_hMutexHandle = CreateMutex(NULL, TRUE, L"CP77_SKIP_MAIN_MENU");
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return;
        }
        App::Initialize();
    }
    catch (...)
    {
    }
}

void Shutdown()
{
    if (s_hMutexHandle)
    {
        App::Shutdown();

        spdlog::default_logger()->flush();

        ReleaseMutex(s_hMutexHandle);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved)
{
    DisableThreadLibraryCalls(hModule);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Initialize();
        break;
    case DLL_PROCESS_DETACH:
        Shutdown();
        break;
    }
    return TRUE;
}