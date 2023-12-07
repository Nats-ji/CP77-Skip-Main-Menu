#include "pch.h"
#include "Logger.h"

Logger::Logger(Paths &aPaths)
    : m_paths(aPaths)
{
    spdlog::set_default_logger(CreateLogger());
}

std::shared_ptr<spdlog::logger> Logger::CreateLogger()
{
    const auto logFileName = m_paths.ModRoot() / "cp_skip_main_menu_asi.log";
    std::size_t max_size = 2 * 1024 * 1024;
    std::size_t max_files = 2;
    const std::string pattern = "[%Y-%m-%d %T UTC%z] [%l] %v";

    auto logger = spdlog::rotating_logger_mt("main", logFileName.string(), max_size, max_files);

    logger->set_pattern(pattern);
    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::info);

    return logger;
}