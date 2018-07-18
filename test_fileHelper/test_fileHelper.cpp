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
    void test_1();
};

Test_fileHelper::Test_fileHelper()
{
}

/*
 * test_1
 * ------
 */
void Test_fileHelper::test_1()
{
    QVERIFY(true);
}

QTEST_APPLESS_MAIN(Test_fileHelper)

#include "test_fileHelper.moc"
