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

bool FileHelper::readFile2TagMap(const QDir &path, tagMap &tags)
{
    // return false if reading 2 tag map fails
    bool retVal{false};

    // open in path provided file as data
    QFile data(path.absolutePath());
    if (data.open(QFile::ReadOnly | QFile::Text))
    {
        // use text stream 'in' to read from 'data'
        QTextStream in(&data);

        // declare string row
        QString row{};

        // return true if reading was successful
        retVal = true;

        // while text stream 'in' is not at end
        while (!in.atEnd())
        {
            // read one line from stream to string 'row' and split it
            // on the seperator ','
            in.readLineInto(&row);
            QStringList rowList = row.split(",");

            // TODO: delete debug output
            qInfo() << rowList;

            // check if exact two items are in the split row and add the
            // row parts to the tag map
            if (2 == rowList.size())
            {
                tags[rowList[0]] = rowList[1];
            }
            // else reading failed due invalid file format
            else
            {
                // print warning to log output
                qWarning() << "WARNING: invalid tag list file to import";

                // return false because reading failed and end the loop
                retVal = false;
                break;
            }
        }
    }
    return retVal;
}
