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
    void test_readFile2TagMap_missingFile();
    void test_readFile2TagMap_invalidFile();

private:
    QDir getNonExistingFile();
    void assertNonExistingFile(QDir filePath);
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
    // get a path to a non existing file
    QDir filePath = getNonExistingFile();
    assertNonExistingFile(filePath);

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
    TagMapModel::tagMap tagMap{};
    FileHelper::ResultCode result = FileHelper::readFile2TagMap(filePath, tagMap);

    // check the result code
    // Todo: write tests to trigger the other result codes
    QCOMPARE(result, FileHelper::ResultCode::OK);

    // define the expected tag map data
    // Todo: create more challanging test data
    TagMapModel::tagMap tagMapExpected{};
    tagMapExpected.insert("Foo", "Bar");
    tagMapExpected.insert("foo", "bar");

    // compare read and expected tag map
    QCOMPARE(tagMap, tagMapExpected);
}

/*
 * test the read file 2 tag map method with a non existent file
 */
void Test_fileHelper::test_readFile2TagMap_missingFile()
{
    // use helper method to get a path to a non existing file
    QDir filePath = getNonExistingFile();
    assertNonExistingFile(filePath);

    // try to read the file to the tag map
    TagMapModel::tagMap tagMap{};
    FileHelper::ResultCode resultCode = FileHelper::readFile2TagMap(filePath, tagMap);

    // check for the correct error code
    QCOMPARE(resultCode, FileHelper::ResultCode::ERROR_FILE_OPEN);

    // the tag map should still be empty
    QVERIFY2(tagMap.isEmpty(), "the tag map should still be empty");
}

/*
 * test the read file 2 tag map file with an invalid file
 */
void Test_fileHelper::test_readFile2TagMap_invalidFile()
{
    // use file defined in the Resources
    QList<QDir> filePaths{};
    filePaths.append(QDir(":testdata/tagMap_invalidRow.testData"));
    filePaths.append(QDir(":testdata/tagMap_invalidKey.testData"));

    foreach (QDir filePath, filePaths)
    {
        // try to read the file to the tag map
        TagMapModel::tagMap tagMap{};
        FileHelper::ResultCode resultCode = FileHelper::readFile2TagMap(filePath, tagMap);

        // check for the correct result code
        QCOMPARE(resultCode, FileHelper::ResultCode::ERROR_INVALID_FILE);

        // the tag map should still be empty
        QVERIFY2(tagMap.isEmpty(), "the tag map should still be empty");
    }
}

/*
 * helper to get a path to a non existing file
 */
QDir Test_fileHelper::getNonExistingFile()
{
    // create QDir object pointing to non existing file
    QDir filePath{QDir("./missingFile_20180811104155.missingFile")};
    return filePath;
}

/*
 * helper to assert the file in the given path does not exist
 */
void Test_fileHelper::assertNonExistingFile(QDir filePath)
{
    // assert the file really does not exist
    QFile file{filePath.absolutePath()};
    QVERIFY2(!file.exists(), "missing file does exist, but it should not!");
}

QTEST_APPLESS_MAIN(Test_fileHelper)

#include "test_fileHelper.moc"
