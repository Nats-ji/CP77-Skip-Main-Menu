#include "pch.h"
#include "Paths.h"

Paths::Paths()
{
  TCHAR exePathBuf[MAX_PATH] = {0};
  GetModuleFileName(GetModuleHandle(nullptr), exePathBuf, std::size(exePathBuf));
  m_exe = exePathBuf;
  m_exeRoot = m_exe.parent_path();
  m_gameRoot = m_exeRoot.parent_path().parent_path();
  m_archives = m_gameRoot / "archive" / "pc" / "mod";
  m_plugins = m_exeRoot / "plugins";
  m_cetmods = m_plugins / "cyber_engine_tweaks" / "mods";
  m_cetconfig = m_plugins / "cyber_engine_tweaks" / "config.json";
  m_modRoot = m_cetmods / "skip_main_menu";
  m_config = m_modRoot / "config.json";
  m_patchArchive = m_modRoot / "archive" / "patch.archive";
}

const std::filesystem::path &Paths::GameRoot() const
{
  return m_gameRoot;
}

const std::filesystem::path &Paths::Archives() const
{
  return m_archives;
}

const std::filesystem::path &Paths::Plugins() const
{
  return m_plugins;
}

const std::filesystem::path &Paths::CETMods() const
{
  return m_cetmods;
}

const std::filesystem::path &Paths::CETConfig() const
{
  return m_cetconfig;
}

const std::filesystem::path &Paths::ModRoot() const
{
  return m_modRoot;
}

const std::filesystem::path &Paths::Config() const
{
  return m_config;
}

const std::filesystem::path &Paths::EXE() const
{
  return m_exe;
}

const std::filesystem::path &Paths::PatchArchive() const
{
  return m_patchArchive;
}