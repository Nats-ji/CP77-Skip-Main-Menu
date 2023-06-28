#include <pch.h>
#include "App.h"

void App::Initialize()
{
    Get().initialize();
}

void App::Shutdown()
{
    Get().shutdown();
}

App &App::Get()
{
    static App instance;
    return instance;
}

const Paths &App::GetPaths()
{
    return Get().m_paths;
}

Config &App::GetConfig()
{
    return Get().m_config;
}

Patch &App::GetPatch()
{
    return Get().m_patch;
}

void App::initialize()
{
    Log::Info("Starting up...");
    m_config.Initialize();

    m_patch.SkipIntroVideo(m_config.SkipIntroVideos());
    m_patch.SkipBreachScreen(m_config.SkipBreachScreen());
}

void App::shutdown()
{
    m_patch.Shutdown();
    Log::Info("Shutting down...");
}

App::App()
    : m_logger(m_paths), m_config(m_paths), m_patch(m_paths, m_config)
{
}