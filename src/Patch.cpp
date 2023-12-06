#include "pch.h"
#include "Patch.h"

Patch::Patch(Paths &aPaths, Config &aConfig)
    : m_paths(aPaths), m_config(aConfig)
{
    m_archivePath = m_paths.Archives() / m_archivePath;
}

void Patch::Shutdown()
{
    SkipIntroVideo(false);
}

void Patch::SkipIntroVideo(bool aEnable)
{
    if (aEnable)
        copyArchive();
    if (!aEnable)
        removeArchive();
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

void Patch::copyArchive()
{
    Log::Info("Applying the skip intro patches...");
    std::error_code ec;

    auto copyOptions = std::filesystem::copy_options::none;

    // use create_hard_links if filesystem is NTFS
    if (isFileSystemNTFS())
    {
        Log::Info("The file system is NTFS. Symlink will be used to apply the patches.");
        copyOptions |= std::filesystem::copy_options::create_hard_links;
    }

    std::filesystem::copy(m_paths.PatchArchive(), m_archivePath, copyOptions, ec);
    if (ec)
        Log::Error("Failed to apply the skip intro patches: {}.", ec.message());
}

void Patch::removeArchive()
{
    Log::Info("Removing the skip intro patches...");
    if (!std::filesystem::exists(m_archivePath))
    {
        Log::Info("Skip intro patches cannot be remove since the archive does not exist.");
        return;
    }
    std::error_code ec;
    bool result = std::filesystem::remove(m_archivePath, ec);
    if (!result)
    {
        Log::Error("Error removing the skip intro patches: {}", ec.message());
    }
}