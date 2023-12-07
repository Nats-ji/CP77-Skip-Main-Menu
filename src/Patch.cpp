#include "pch.h"
#include "Patch.h"

Patch::Patch(Paths &aPaths, Config &aConfig)
    : m_paths(aPaths), m_config(aConfig)
{
    m_archivePath = m_paths.Archives() / m_archivePath;
    m_cmdConfigPath = m_paths.CyberCmdConfig() / m_cmdConfigPath;
}

void Patch::Shutdown()
{
    SkipIntroVideo(false);
}

void Patch::SkipIntroVideo(bool aEnable)
{
    if (aEnable)
    {
        setCopyOptions();
        copyArchive();
        copyCybercmdConfig();
    }
    if (!aEnable)
    {
        removeArchive();
        removeCybercmdConfig();
    }
}

bool Patch::isFileSystemNTFS()
{
    std::filesystem::path root_path_name = m_paths.ModRoot().root_path();
    wchar_t file_system_name[MAX_PATH];
    if (!GetVolumeInformationW(root_path_name.wstring().c_str(), NULL, 0, NULL, NULL, NULL, file_system_name, MAX_PATH))
        Log::Error("Failed to get the volume information.");
    std::wstring fsn(file_system_name);
    std::wstring ntfs = L"NTFS";
    return fsn == ntfs;
}

void Patch::setCopyOptions()
{
    // use create_hard_links if filesystem is NTFS
    if (isFileSystemNTFS())
    {
        Log::Info("The file system is NTFS. Symlink will be used to apply the patches.");
        m_copyOptions |= std::filesystem::copy_options::create_hard_links;
    }
    else
        m_copyOptions = std::filesystem::copy_options::none;
}

void Patch::copyArchive()
{
    Log::Info("Applying the skip intro patch...");
    std::error_code ec;

    std::filesystem::copy(m_paths.PatchArchive(), m_archivePath, m_copyOptions, ec);
    if (ec)
        Log::Error("Failed to apply the skip intro patch: {}.", ec.message());
}

void Patch::removeArchive()
{
    Log::Info("Removing the skip intro patch...");
    if (!std::filesystem::exists(m_archivePath))
    {
        Log::Info("Skip intro patch was not removed since the archive does not exist.");
        return;
    }
    std::error_code ec;
    bool result = std::filesystem::remove(m_archivePath, ec);
    if (!result)
    {
        Log::Error("Error removing the skip intro patch: {}", ec.message());
    }
}

bool Patch::hasCybercmd()
{
    if (std::filesystem::exists(m_paths.CyberCmd()))
        return true;
    else
        return false;
}

void Patch::copyCybercmdConfig()
{
    if (!hasCybercmd())
        return;
    
    Log::Info("Cybercmd installation detected.");
    Log::Info("Applying the skip breaching screen patch...");
    std::error_code ec;

    std::filesystem::copy(m_paths.PatchConfig(), m_cmdConfigPath, m_copyOptions, ec);
    if (ec)
        Log::Error("Failed to apply the skip breaching screen patch: {}.", ec.message());
}

void Patch::removeCybercmdConfig()
{
    Log::Info("Removing the skip breaching screen patch...");
    if (!std::filesystem::exists(m_cmdConfigPath))
    {
        Log::Info("Skip breaching screen patch was not removed since the patch does not exist.");
        return;
    }
    std::error_code ec;
    bool result = std::filesystem::remove(m_cmdConfigPath, ec);
    if (!result)
    {
        Log::Error("Error removing the skip breaching screen patch: {}", ec.message());
    }
}
