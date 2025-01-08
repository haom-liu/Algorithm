// Description: A simple log system.
#pragma once

#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <ctime>

enum Level {
    DEBUG,
    NORMAL,
    WARNING,
    ERROR,
    FATAL
};

const size_t STD_SIZE = 0x40;
const size_t TIME_SIZE = 0x20;
const size_t LOG_SIZE = 0x400;

const std::string logFile = "./file.log";

const std::string gLevelMap[] = {
    "DEBUG",
    "NORMAL",
    "WARNING",
    "ERROR",
    "FATAL"
};

void logMessage(const size_t level, const char* format, ...) {
#ifndef DEBUG_SHOW
    if (level == DEBUG) return ;
#endif
    char stdBuffer[STD_SIZE];
    char logBuffer[LOG_SIZE];
    char timeBuffer[TIME_SIZE];
    const time_t t = time(nullptr);
    const struct tm* timeinfo = localtime(&t);
    strftime(timeBuffer, sizeof timeBuffer, "%Y-%m-%d %H:%M:%S", timeinfo);
    snprintf(stdBuffer, sizeof stdBuffer, "[%s][%s]", gLevelMap[level].c_str(), timeBuffer);
    va_list args;
    va_start(args, format);
    vsnprintf(logBuffer, sizeof logBuffer, format, args);
    va_end(args);
#ifdef LOG_FILE
    FILE* fp = fopen(logFile, "a");
    fprintf(fp, "%s%s\n", stdBuffer, logBuffer);
    fclose(fp);
#else
    printf("%s%s\n", stdBuffer, logBuffer);
#endif
}
