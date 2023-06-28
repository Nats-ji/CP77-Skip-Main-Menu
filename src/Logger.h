#pragma once

namespace Log
{
    template <typename... Args>
    using format_string_t = fmt::format_string<Args...>;

    template <typename... Args>
    void Info(format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::default_logger_raw()->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void Warn(format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::default_logger_raw()->log(spdlog::level::warn, fmt, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void Error(format_string_t<Args...> fmt, Args &&...args)
    {
        spdlog::default_logger_raw()->log(spdlog::level::err, fmt, std::forward<Args>(args)...);
    }
};

class Logger
{
public:
    Logger(Paths &aPath);
    std::shared_ptr<spdlog::logger> CreateLogger();

private:
    Paths &m_paths;
};