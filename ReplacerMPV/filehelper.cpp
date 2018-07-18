#include "filehelper.h"

const QChar FileHelper::tagMapSeparator = QChar(',');

QChar FileHelper::getTagMapSeparator()
{
    return tagMapSeparator;
}

FileHelper::FileHelper()
{
    // nothing to do here
}

FileHelper::ResultCode FileHelper::readFile2String(const QDir &path,
                                                   QString &readText)
{
    /*
     * reads from file in path and writes contents to string
     *
     * possible return codes:
     *   OK
     *   ERROR_FILE_OPEN
     */

    // returns error if file coud not be read
    ResultCode retVal{ResultCode::ERROR_FILE_OPEN};

    // open provided file path
    QFile data(path.absolutePath());
    if (data.open(QFile::ReadOnly | QFile::Text))
    {
        // write file contents to provided reference 'readText'
        QTextStream in(&data);
        readText = in.readAll();

        // will return OK because of successful read
        retVal = ResultCode::OK;
    }
    // close file
    data.close();

    // return retVal
    return retVal;
}

FileHelper::ResultCode FileHelper::readFile2TagMap(const QDir &path,
                                                   TagMapModel::tagMap &tags)
{
    /*
     * reads from file in path and writes contents into TagMapModel tags
     *
     * return codes:
     *   OK
     *   ERROR_INVALID_FILE
     *   ERROR_FILE_OPEN
     */

    // default code
    ResultCode retVal{ResultCode::OK};

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

                retVal = ResultCode::ERROR_INVALID_FILE;
                break;
            }
        }
    }
    // could not open file for reading
    else
    {
        retVal = ResultCode::ERROR_FILE_OPEN;
    }
    return retVal;
}

FileHelper::ResultCode FileHelper::writeString2File(const QDir &path,
                                                    const QString &text)
{
    /*
     * writes the string 'text' to the file in path
     *
     * possible return codes:
     *   OK
     *   ERROR_FILE_CREATION
     */

    // default return code
    ResultCode retVal{ResultCode::OK};

    // get absolute path
    QFile data(path.absolutePath());

    // try to open file as write only text file
    if (data.open(QFile::WriteOnly | QFile::Text))
    {
        // write text to file
        QTextStream out(&data);
        out << text;
    }
    else
    {
        // failed to open file
        retVal = ResultCode::ERROR_FILE_CREATION;
    }
    // close open file stream
    data.close();
    return retVal;
}

FileHelper::ResultCode FileHelper::writeTags2File(const QDir &path,
                                                  const TagMapModel::tagMap &tags)
{
    /*
     * this method writes the tags from the tagmap to a csv like file
     *
     * return codes:
     *    OK                  : export ok
     *    ERROR_INVALID_DATA  : invalid key detected, aborted export
     *    ERROR_FILE_CREATION : could not create file
     */

    // default return code
    ResultCode retVal{ResultCode::OK};

    // try to open file from path
    QFile data(path.absolutePath());
    if(data.open(QFile::WriteOnly | QFile::Text))
    {
        // use text stream to write to file
        QTextStream out(&data);

        // iterate over all unique keys of the tag map
        auto keys{tags.uniqueKeys()};
        foreach (auto key, keys)
        {
            // if the key is valid write key and value to file
            if (TagMapModel::isKeyValid(key))
            {
                out << key << getTagMapSeparator() << tags[key] << '\n';
            }
            else
            {
                // if key is invalid return error
                retVal = ResultCode::ERROR_INVALID_DATA;
                break;
            }
        }
    }
    else
    {
        retVal = ResultCode::ERROR_FILE_CREATION;
    }
    data.close();
    return retVal;
}
