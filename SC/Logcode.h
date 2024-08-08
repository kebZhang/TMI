#include <string>
#include <unordered_map>

enum class Support_logcode{
    LTE_RRC_OTA_Packet = 0xB0C0
};


static const std::unordered_map<std::string, SupportLogcode> Support_logcode = {
    {"LTE_RRC_OTA_Packet", SupportLogcode::LTE_RRC_OTA_Packet},
};

