// Description: FileHandler class for reading
#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cerrno>
#include "log.hpp"

const size_t LINE_SIZE = 256;

class FileHandler {
public:
    FileHandler ():_curPos(0), _fp(nullptr) {}

    void open(std::string filename = "") {
        _fp = filename.empty() ? stdin : fopen(filename.c_str(), "r");
        if (!_fp) {
            logMessage(FATAL, "file open error, %d:%s", errno, strerror(errno));
            exit(1);
        }
        char line[LINE_SIZE];
        while (fgets(line, sizeof line, _fp)) {
            if (strcmp(line, "end\n") == 0) break;
            _input_buffer += line;
        }
        if (filename.empty()) logMessage(NORMAL, "read success.");
        else logMessage(NORMAL, "read file:%s success.", filename.c_str());
    }

    std::string read() const { return _input_buffer; }

    int read(char* buf, const size_t begin, const size_t len) const {
        size_t readCnt = 0;
        for (; _curPos + readCnt < _input_buffer.size() && readCnt < len; ++readCnt)
            buf[begin + readCnt] = _input_buffer[_curPos + readCnt];
        return readCnt;
    }

    int close() {
        _input_buffer.clear();
        return fclose(_fp);
    }

private:
    std::string _input_buffer;
    size_t _curPos;
    FILE* _fp;
};
