#pragma once
#include <stdint.h>
#include <string>
#include <map>

namespace Config
{
    inline constexpr size_t OutputBufferSize = 10 * 1024;
    inline constexpr size_t InputBufferSize = 11 * 1024;
    inline const std::string FilesPath = "D:/Projects/7_sem/SPOLKS/labs/ServerFolder/";
}

enum class Protocol
{
    TCP,
    UDP,
};

enum class MessageType
{
    ERROR_TYPE,
    COMMAND,
    STRING_DATA,
    BITSTREAM
};

namespace Commands
{
    inline const std::string ECHO = "ECHO";
    inline const std::string TIME = "TIME";
    inline const std::string DOWLOAD = "DOWNLOAD";
    inline const std::string UPLOAD = "UPLOAD";
}
