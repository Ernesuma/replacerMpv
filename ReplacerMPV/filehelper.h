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
    // define result codes for this classes methods
    enum ResultCode
    {
        OK,
        ERROR_FILE_OPEN,
        ERROR_INVALID_FILE
    };

    FileHelper();
    static ResultCode readFile2String(const QDir& path, QString& readText);
    static ResultCode readFile2TagMap(const QDir& path, tagMap& tags);

};

#endif // FILEHELPER_H
