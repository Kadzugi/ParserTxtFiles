#include "File.h"

File::File(const fs::path path_file, std::wstring data)
    : path_file_m(path_file), data_m(data) {
    name_file_m = path_file_m.filename().wstring();
}

void File::read_file() {
    fs::wifstream ifs(path_file_m);
    ifs.imbue(std::locale("ru_RU.utf8"));
    if (ifs.is_open()) {
        std::wstring line;
        while (getline(ifs, line)) {
            if (data_m.empty()) {
                data_m = line;
            }
            else {
                separators_m.push_back(line);
            }
        }
    }
    else {
        assert(false && "Ошибка чтения данных файла!");
        std::wcout << L"Ошибка чтения данных файла!\n";
    }
}

void File::write_file() {
    fs::wofstream ofs(path_file_m);
    ofs.imbue(std::locale("ru_RU.utf8"));
    ofs << data_m;
    ofs.close();
}

const std::wstring& File::get_name_file() {
    return name_file_m;
}

std::wstring& File::get_data() {
    return data_m;
}

std::vector<std::wstring>& File::get_separators() {
    return separators_m;
}