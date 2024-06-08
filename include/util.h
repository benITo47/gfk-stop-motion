#pragma once

#include <vector>
#include <string>
#include <wx/string.h>
#include <algorithm>

// Split string by delimiter
inline std::vector<wxString> split(wxString s, wxString delimiter) {
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

inline wxString toUnixPath(const wxString& path) {
    wxString unixPath = path;
    std::replace(unixPath.begin(), unixPath.end(), '\\', '/');
    return unixPath;
}