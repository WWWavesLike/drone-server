//
// Created by waves-like on 24. 6. 30.
//

#ifndef INI_HANDLER_H
#define INI_HANDLER_H
#include <fstream>
#include <sstream>
#include <string>
#include <map>


std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to parse an INI file
std::map<std::string, std::map<std::string, std::string>> parseINI(const std::string &filename) {
    std::ifstream file(filename);
    std::string line, section;
    std::map<std::string, std::map<std::string, std::string>> config;

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    while (std::getline(file, line)) {
        line = trim(line);

        // Ignore comments and empty lines
        if (line.empty() || line[0] == ';' || line[0] == '#')
            continue;

        // Check for section headers
        if (line[0] == '[' && line[line.size() - 1] == ']') {
            section = line.substr(1, line.size() - 2);
        } else {
            // Parse key-value pairs
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = trim(line.substr(0, delimiterPos));
                std::string value = trim(line.substr(delimiterPos + 1));
                config[section][key] = value;
            }
        }
    }

    file.close();
    return config;
}


#endif //INI_HANDLER_H
