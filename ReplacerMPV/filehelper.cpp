#include "filehelper.h"

FileHelper::FileHelper()
{

}

bool FileHelper::readFile2String(const QDir &path, QString &readText)
{
    // returns false if file coud not be read
    bool retVal{false};

    // open provided file path
    QFile data(path.absolutePath());
    if (data.open(QFile::ReadOnly | QFile::Text))
    {
        // write file contents to provided reference 'readText'
        QTextStream in(&data);
        readText = in.readAll();

        // will return true because of successful read
        retVal = true;
    }
    // close file
    data.close();

    // return retVal
    return retVal;
}

int FileHelper::readFile2TagMap(const QDir &path, tagMap &tags)
{
    // return codes:
    // 0: OK
    // 1: file not readable
    // 2: invalid file format

    // default code
    int retVal{0};

    // open in provided file path as data
    QFile data(path.absolutePath());
    if (data.open(QFile::ReadOnly | QFile::Text))
    {
        // use text stream 'in' to read from 'data'
        QTextStream in(&data);

        // declare string row
        QString row{};
        QString validRowPattern{"^([a-zA-Z0-9]*),(.*)$"};
        QRegularExpression reValidRow(validRowPattern);

        // while text stream 'in' is not at end
        while (!in.atEnd())
        {
            // read one line from stream to string 'row' and use regex
            // to check for validity
            in.readLineInto(&row);

            // check if row has valid format
            QRegularExpressionMatch validRowMatch = reValidRow.match(row);
            if (validRowMatch.hasMatch())
            {
                // add the key and the value to the tag map
                auto key = validRowMatch.captured(1);
                auto value = validRowMatch.captured(2);
                tags[key] = value;
            }
            // row not valid
            else
            {
                // print warning to log output
                qWarning() << "WARNING: invalid tag list file to import";

                retVal = 2;
                break;
            }
        }
    }
    // could not open file for reading
    else
    {
        retVal = 1;
    }
    return retVal;
}
