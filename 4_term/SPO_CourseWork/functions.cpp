//
// Created by sifi on 28.03.2022.
//


#include "functions.h"

std::string md5_to_string(unsigned char *md) {

    std::stringstream s_stream{};

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        s_stream << std::hex << static_cast<int>(md[i]);
    }

    return s_stream.str();
}

void collect_files(const std::string &current_dir,  std::map<std::string , std::string> &files_map) {
    unsigned char result[MD5_DIGEST_LENGTH];

    DIR *dir = opendir((current_dir + "/").c_str());

    if (!dir) {
        if (errno == EACCES) {
            std::cout << "Cant open file: access error" << std::endl;
            return;
        } else {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }

    dirent *file;
    while ((file = readdir(dir))) {
        std::string filename = file->d_name;
        if ((filename == "." || filename == "..")) {
            continue;
        }

        if (file->d_type == DT_DIR) {
            collect_files(current_dir + '/' + filename, files_map);
            continue;
        }
        // If it not directory:

        int file_descript;
        unsigned long file_size;
        char *file_buffer;

        file_descript = open((current_dir + '/' + filename).c_str(), O_RDONLY);

        if (file_descript < 0) {
            continue;
        }

        file_size = get_size_by_fd(file_descript);
        std::cout << "File size: " << file_size << std::endl;

        // Функция возвращает адрес начала участка отображаемой памяти или MAP_FAILED в случае неудачи.
        file_buffer = static_cast<char *>(mmap(nullptr, file_size, PROT_READ, MAP_SHARED, file_descript, 0));
        MD5(reinterpret_cast <unsigned char *>(file_buffer), file_size, result);
        munmap(file_buffer, file_size);

        std::string hash = md5_to_string(result);
        std::cout << "File name: " << filename << "; Hash: " << hash << std::endl;

        if (files_map.find(hash) == files_map.end()) {
            // We don't have that file in map
            std::cout << "File " << filename << " not found in map" << std::endl;
            files_map[hash] = current_dir + '/' + filename;
        } else {
            std::cout << "File " << filename << " already in map" << std::endl;
        }
    }
    closedir(dir);
}


// Get the size of the file by its file descriptor
unsigned long get_size_by_fd(int fd) {
    struct stat statbuf{};
    if (fstat(fd, &statbuf) < 0) {
        exit(-1);
    }

    return statbuf.st_size;
}