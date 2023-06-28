#pragma once

struct Paths
{
  Paths();
  const std::filesystem::path& GameRoot() const;
  const std::filesystem::path& Archives() const;
  const std::filesystem::path& Plugins() const;
  const std::filesystem::path& CETMods() const;
  const std::filesystem::path& CETConfig() const;
  const std::filesystem::path& ModRoot() const;
  const std::filesystem::path& Config() const;
  const std::filesystem::path& EXE() const;
  const std::filesystem::path& PatchArchive() const;

  std::filesystem::path m_exe;
  std::filesystem::path m_exeRoot;
  std::filesystem::path m_gameRoot;
  std::filesystem::path m_modRoot;
  std::filesystem::path m_archives;
  std::filesystem::path m_plugins;
  std::filesystem::path m_cetmods;
  std::filesystem::path m_cetconfig;
  std::filesystem::path m_config;
  std::filesystem::path m_patchArchive;
};
