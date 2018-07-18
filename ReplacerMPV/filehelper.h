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
private:
    // default tag map file separator
    static const QChar tagMapSeparator;

public:
    // define result codes for this classes methods
    enum ResultCode
    {
        OK,
        ERROR_FILE_OPEN,
        ERROR_INVALID_FILE,
        ERROR_FILE_CREATION,
        ERROR_INVALID_DATA
    };

    // constructor
    FileHelper();

    // getter
    static QChar getTagMapSeparator();

    // static methods to read and write to files
    static ResultCode readFile2String(const QDir& path, QString& readText);
    static ResultCode readFile2TagMap(const QDir& path, TagMapModel::tagMap& tags);
    static ResultCode writeString2File(const QDir& path, const QString& text);
    static ResultCode writeTags2File(const QDir& path, const TagMapModel::tagMap& tags);
};

#endif // FILEHELPER_H
