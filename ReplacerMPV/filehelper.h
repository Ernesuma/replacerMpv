#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QTextStream>
#include <QRegularExpression>

#include "tagmapmodel.h"

class FileHelper
{
public:
    FileHelper();
    static bool readFile2String(const QDir& path, QString& readText);
    static int readFile2TagMap(const QDir& path, tagMap& tags);
};

#endif // FILEHELPER_H
