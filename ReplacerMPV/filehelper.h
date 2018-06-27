#ifndef FILEHELPER_H
#define FILEHELPER_H

#include<QFile>
#include<QDir>
#include<QString>
#include<QTextStream>

class FileHelper
{
public:
    FileHelper();
    static bool readFile2String(const QDir& path, QString& readText);
};

#endif // FILEHELPER_H
