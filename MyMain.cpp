#include <iostream>
#include "MyClass/FilesParser.h"

int main()
{
    setlocale(LC_ALL, "Russian_Russia.866");
    //setlocale(LC_ALL, "Russian_Russia");

    std::wstring path_folder;
    while (!fs::is_directory(path_folder)) {
        std::wcout << L"Введите корректный путь до каталога с файлами *.txt (или введите команду exit для выхода из приложения): ";
        getline(std::wcin, path_folder);
        if (path_folder == L"exit")
            break;
    }
    
    if (path_folder != L"exit") {
        std::wstring name_out_file;
        std::wcout << L"Введите название выходного файла: ";
        getline(std::wcin, name_out_file);

        std::unique_ptr<FilesParser> parser = std::make_unique<FilesParser>(path_folder, name_out_file);
        parser->parser_files_txt();
    } 
}