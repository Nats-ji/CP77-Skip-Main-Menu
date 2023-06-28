#pragma once

class Patch
{
public:
    Patch(Paths &aPaths, Config &aConfig);
    void SkipIntroVideo(bool aEnable);
    void SkipBreachScreen(bool aEnable);
    void Shutdown();

private:
    bool isFileSystemNTFS();
    void copyArchive();
    void removeArchive();

    Paths &m_paths;
    Config &m_config;
    std::filesystem::path m_archivePath{"__00skip_intro_video_patch.archive"};
};