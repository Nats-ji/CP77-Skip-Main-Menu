#pragma once

class Config
{
public:
    Config(Paths& aPaths);
    void Initialize();
    void Load();
    const bool SkipIntroVideos() const;
    const bool SkipBreachScreen() const;
    const bool AutoLoad() const;

private:
    Paths& m_paths;

    bool m_skipIntroVideos{true};
    bool m_skipBreachScreen{true};
    bool m_autoLoad{true};
};