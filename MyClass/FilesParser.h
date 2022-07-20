#pragma once

#include <memory>
#include <boost\thread\thread.hpp>
#include <boost\algorithm\string\split.hpp>
#include <boost\algorithm\string\regex.hpp>
#include "File.h"

namespace al = boost::algorithm;

class FilesParser {
    const fs::path path_folder_m;
    const std::wstring name_out_file_m;
    std::wstring out_data_m = L"";
    boost::mutex lock_out_data;
public:
    FilesParser(const fs::path path_folder, const std::wstring name_out_file);

    void parser_files_txt();
};