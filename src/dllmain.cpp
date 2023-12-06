#include "pch.h"
#include "App.h"
#include "iostream"

static HANDLE s_hMutexHandle = nullptr;

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