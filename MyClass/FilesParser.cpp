#include "FilesParser.h"

FilesParser::FilesParser(const fs::path path_folder, const std::wstring name_out_file)
	: path_folder_m(path_folder), name_out_file_m(name_out_file) {};

void FilesParser::parser_files_txt() {
    std::wstring path_out_file = fs::current_path().wstring() + L'\\' + name_out_file_m + std::wstring{ L".txt" };
    int counter_file = 1;

    boost::thread_group tg;
    for (fs::directory_iterator it(path_folder_m); it != fs::directory_iterator(); ++it) {
        if (it->path().extension() == ".txt") {
            fs::path p = *it;
            tg.add_thread(new boost::thread([&](fs::path path_file) {
                std::unique_ptr<File> file = std::make_unique<File>(path_file);
                file->read_file();

                lock_out_data.lock();
                out_data_m += (L"Имя файла: " + file->get_name_file() + L" Исходная строка: " + file->get_data() + L"\n");

                for (auto& separator : file->get_separators()) {
                    std::vector<std::wstring> result;
                    al::split_regex(result, file->get_data(), boost::wregex(separator));

                    for (auto& elem : result) {
                        out_data_m += (L"Файл №" + std::to_wstring(counter_file) + L" Разделитель: \'" + separator + L"\' Подстрока: " + elem + L"\n");
                    }
                }

                out_data_m += L"\n";
                counter_file++;
                lock_out_data.unlock();
            }, p));
        }
    }
    tg.join_all();

    if (!out_data_m.empty()) {
        std::unique_ptr<File> out_file = std::make_unique<File>(path_out_file, out_data_m);
        out_file->write_file();
    }
    else {
        assert(false && L"В каталоге нет файлов с расширением .txt!");
        std::wcout << L"В каталоге нет файлов с расширением .txt!\nВыходной файл не был создан!\n";
    }
}
