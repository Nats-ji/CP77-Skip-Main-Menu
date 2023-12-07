#pragma once

class Patch
{
public:
    Patch(Paths &aPaths, Config &aConfig);
    void SkipIntroVideo(bool aEnable);
    void Shutdown();

private:
    bool isFileSystemNTFS();
    void setCopyOptions();
    void copyArchive();
    void removeArchive();
    bool hasCybercmd();
    void copyCybercmdConfig();
    void removeCybercmdConfig();

    Paths &m_paths;
    Config &m_config;
    std::filesystem::copy_options m_copyOptions{std::filesystem::copy_options::none};
    std::filesystem::path m_archivePath{"__00skip_intro_video_patch.archive"};
    std::filesystem::path m_cmdConfigPath{"skip_breaching_screen.toml"};
};