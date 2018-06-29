#include <QString>
#include <QtTest>

#include "tagmapmodel.h"

class Test_tagmapmodel : public QObject
{
    Q_OBJECT

public:
    Test_tagmapmodel();

private Q_SLOTS:
    void test_validKeys();
    void test_invalidKeys();
};

Test_tagmapmodel::Test_tagmapmodel()
{
}

void Test_tagmapmodel::test_validKeys()
{
    QList<QString> keys;
    keys.append("foo");
    keys.append("Bar");
    keys.append("Foo_Bar");
    keys.append("foo_bar");
    keys.append("_abc_");
    keys.append("1_abc_");
    keys.append("Moo_1_abc_");
    keys.append("-__-__-");
    keys.append("-_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-");
    foreach (auto key, keys)
    {
        QVERIFY(TagMapModel::isKeyValid(key));
    }
}

void Test_tagmapmodel::test_invalidKeys()
{
    QList<QString> keys;
    keys.append("foo;");
    keys.append("#_Bar");
    keys.append("F00 B48");
    foreach (auto key, keys)
    {
        QVERIFY(!TagMapModel::isKeyValid(key));
    }
}

QTEST_APPLESS_MAIN(Test_tagmapmodel)

#include "test_tagmapmodel.moc"
