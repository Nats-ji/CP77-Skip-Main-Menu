#include "pch.h"
#include "Config.h"

Config::Config(Paths &aPaths)
    : m_paths(aPaths)
{
}

void Config::Initialize()
{
    Load();
    Log::Info("Current configs: skip_intro = {}, auto_load = {}", m_skipIntroVideos, m_autoLoad);
}

void Config::Load()
{
    Log::Info("Loading config...");
    const auto &path = m_paths.Config();
    if (!std::filesystem::exists(path))
    {
        Log::Warn("The config file doesn't exsist.");
        return;
    }

    std::ifstream configFile(path);
    if (!configFile)
    {
        Log::Warn("Failed to open the config file.");
        return;
    }

    auto config = nlohmann::json::parse(configFile);

    m_skipIntroVideos = config.value("skip_intro", m_skipIntroVideos);
    m_autoLoad = config.value("auto_load", m_autoLoad);
}

const bool Config::SkipIntroVideos() const
{
    return m_skipIntroVideos;
}
const bool Config::AutoLoad() const
{
    return m_autoLoad;
}