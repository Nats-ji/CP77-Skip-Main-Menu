#pragma once

#include "Paths.h"
#include "Logger.h"
#include "Config.h"
#include "Patch.h"

class App
{
public:
  static void Initialize();
  static void Shutdown();
  static App &Get();

  static const Paths &GetPaths();
  static Config &GetConfig();
  static Patch &GetPatch();

  App(const App &) = delete;
  App(App &&) = delete;
  App &operator=(const App &) = delete;
  App &operator=(App &&) = delete;

private:
  App();
  ~App() {}
  void initialize();
  void shutdown();

  Paths m_paths;
  Logger m_logger;
  Config m_config;
  Patch m_patch;
};