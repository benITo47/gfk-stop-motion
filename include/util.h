#pragma once

#include <vector>
#include <string>

// Split string by delimiter
std::vector<wxString> split(wxString s, wxString delimiter) {
    size_t posStart = 0, posEnd, delimLen = delimiter.length();
    std::string token;
    std::vector<wxString> res;

    while ((posEnd = s.find(delimiter, posStart)) != std::string::npos) {
        token = s.substr(posStart, posEnd - posStart);
        posStart = posEnd + delimLen;
        res.push_back(token);
    }

    res.push_back(s.substr(posStart));
    return res;
}