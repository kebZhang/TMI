#include "monitor.h"

int main()
{
    Monitor example;
    example.set_baudrate(9600);
    example.set_serial_port("USB0");
    example.enable_log("LTE_RRC_OTA_Packet");
    example.run();
}
