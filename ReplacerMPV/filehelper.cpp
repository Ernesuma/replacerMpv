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
