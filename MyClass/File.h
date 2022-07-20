#pragma once

#include <vector>
#include <cassert>
#include <iostream>
#include <boost\filesystem\fstream.hpp>
#include <boost\filesystem.hpp>

namespace fs = boost::filesystem;

class File {
    const fs::path path_file_m;
    std::wstring name_file_m;
    std::wstring data_m;
    std::vector<std::wstring> separators_m;
public:
    File(const fs::path path_file, std::wstring data = L"");

    void read_file();
    void write_file();
    const std::wstring& get_name_file();
    std::wstring& get_data();
    std::vector<std::wstring>& get_separators();
};

