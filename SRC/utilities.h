#pragma once

#include<string>
#include <fstream>

static void log(const char* msg){
    std::ofstream logs;
    logs.open("log.txt", std::ofstream::app | std::ofstream::out);
    logs << msg;
    logs.close();
}
