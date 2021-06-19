//
// Created by migecha on 6/13/21.
//

#ifndef BOXING2D_FILEMANAGER_H
#define BOXING2D_FILEMANAGER_H

#include <vector>
#include <string>
class FileManager {
    static FileManager *m_instance;
public:
    static FileManager *getInstance();

    int getFileCountInDirectory(std::string p_path);

    std::vector<std::string> getFiles(std::string p_path);
};


#endif //BOXING2D_FILEMANAGER_H
