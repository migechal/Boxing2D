//
// Created by migecha on 6/13/21.
//

#include "../include/FileManager.h"
#include <bits/stdc++.h>
#include <sys/types.h>
#include <dirent.h>
#include <filesystem>

namespace fs = std::filesystem;

//namespace fs = std::filesystem;
FileManager *FileManager::m_instance = nullptr;

FileManager *FileManager::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new FileManager();
    }
    return m_instance;
}

int FileManager::getFileCountInDirectory(std::string p_path) {
    DIR *dp;
    int i = 0;
    struct dirent *ep;
    dp = opendir(p_path.c_str());

    if (dp != NULL) {
        while ((ep = readdir(dp)))
            i++;

        (void) closedir(dp);
    } else {
        perror("Couldn't open the directory");
        return -1;
    }

    return i;
}

std::vector<std::string> FileManager::getFiles(std::string p_path) {
    std::vector<std::string> r_ret;
    for (const auto &entry : fs::directory_iterator(p_path))
      r_ret.push_back(p_path.path());
    return r_ret;
}
