#include <QString>
#include <QtTest>

// include subject under test
#include"filehelper.h"


class Test_fileHelper : public QObject
{
    Q_OBJECT

public:
    Test_fileHelper();

private Q_SLOTS:
    void test_getTagMapSeparator();
    void test_readFile2String();
    void test_readFile2String_missingFile();
    void test_readFile2TagMap();
};

/*
 * constructor
 */
Test_fileHelper::Test_fileHelper()
{
}

/*
 * test the getTagMapSeparator method
 */
void Test_fileHelper::test_getTagMapSeparator()
{
    QCOMPARE(FileHelper::getTagMapSeparator(),
             QChar(','));
}

/*
 * test the read file 2 string method
 */
void Test_fileHelper::test_readFile2String()
{
    // use file defined in Resources
    QDir filePath{QDir(":testdata/plain01.testData")};

    // call DUT
    QString readString{};
    FileHelper::ResultCode resultCode = FileHelper::readFile2String(filePath, readString);

    // check the result code
    QCOMPARE(resultCode, FileHelper::ResultCode::OK);

    // check the read string
    QCOMPARE(readString, QString("This is some test data!!\n"));
}

/*
 * test the read file 2 string with a missing file
 */
void Test_fileHelper::test_readFile2String_missingFile()
{
    // create QDir object pointing to non existing file
    QDir filePath{QDir("./missingFile_20180811104155.missingFile")};
    QFile file{filePath.absolutePath()};
    QVERIFY2(!file.exists(), "ERROR in unit test: missing file does exist, but it should not!");

    // try to read the file to a string
    QString readString{};
    FileHelper::ResultCode resultCode = FileHelper::readFile2String(filePath, readString);

    // check for the expected result code
    QCOMPARE(resultCode, FileHelper::ResultCode::ERROR_FILE_OPEN);

    // make sure that the read string is still empty
    QVERIFY2(readString.isEmpty(), "the read string should still be empty");
}

/*
 * test the read file 2 tag map method
 */
void Test_fileHelper::test_readFile2TagMap()
{
    // use file defined in the Resources
    QDir filePath{QDir(":testdata/tagMap.testData")};

    // call DUT to get the tag map
    TagMapModel::tagMap tagMap;
    FileHelper::ResultCode result = FileHelper::readFile2TagMap(filePath, tagMap);

    // check the result code
    // Todo: write tests to trigger the other result codes
    QCOMPARE(result, FileHelper::ResultCode::OK);

    // define the expected tag map data
    // Todo: create more challanging test data
    TagMapModel::tagMap tagMapExpected;
    tagMapExpected.insert("Foo", "Bar");
    tagMapExpected.insert("foo", "bar");

    // compare read and expected tag map
    QCOMPARE(tagMap, tagMapExpected);
}

QTEST_APPLESS_MAIN(Test_fileHelper)

#include "test_fileHelper.moc"
