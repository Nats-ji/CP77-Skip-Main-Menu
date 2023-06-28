#pragma once

#include <string>
#include <filesystem>
#include <fstream>

#include <Windows.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <nlohmann/json.hpp>

#include "Paths.h"
#include "Logger.h"
#include "Config.h"
#include "Patch.h"