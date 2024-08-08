#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <serial/serial.h>
#include "Logcode.h" // Include your Support_logcode definitions here




class Monitor {
public:
    Monitor()
        : phy_baudrate(9600), phy_ser_name(""), buffer("") {}

    void set_baudrate(unsigned int baudrate) {
        phy_baudrate = baudrate;
    }

    void set_serial_port(const string& phy_ser_name) {
        this->phy_ser_name = phy_ser_name;
    }

    void enable_log(const string& log_type) {
        vector<string> log_types_to_enable;
        log_types_to_enable.push_back(log_type);

        enable_log(log_types_to_enable);
    }

    void enable_log(const vector<string>& log_types) {
        for (const auto& i : log_types) {
            if (Support_logcode.find(i) == Support_logcode.end()) {
                cerr << "Unsupported log message type: " << i << endl;
                continue;
            }
            if (find(this->log_types.begin(), this->log_types.end(), i) == this->log_types.end()) {
                this->log_types.push_back(i);
                cout << "Enable collection: " << i << endl;
            }
        }
    }

    void run() {
        cout << "PHY COM: " << phy_ser_name << endl;
        cout << "PHY BAUD RATE: " << phy_baudrate << endl;

        try {
            // Open COM ports
            serial::Serial phy_ser(phy_ser_name, phy_baudrate, serial::Timeout::simpleTimeout(1000));

            cout << "phy port connect!" << endl;

            generate_cfg(log_types);


            while (true) {
                string data;
                if (phy_ser.available()) {
                    data = phy_ser.read(64);
                    buffer += data;
                }

                // decode part
                // wait !!!!!
            }
        }
        catch (const exception& e) {
            cerr << "\n\nException Detected: " << e.what() << " Disabling all logs" << endl;
            // Disable logs
            // we should send some special logcode to phone to stop!!!
            exit(EXIT_FAILURE);
        }
    }

private:
    unsigned int phy_baudrate;
    string phy_ser_name;
    vector<string> log_types;
    string buffer;
};


void generate_cfg(vector<string> log_types){
    vector<int> type_ids;
    for (auto& log_type : log_types) {
        auto it = Support_logcode.find(log_type);
        if (it != Support_logcode.end()) {
            cout << "Log type found: " << log_type << " with code: " << static_cast<int>(it->second) << endl;
            // here may be wrong
            type_ids.push_back(it->second);
        } else {
            cerr << "Log type not found in Support_logcode: " << log_type << endl;
        }
    }
}