#include <QString>
#include <QtTest>

// include subject under test
#include"model.h"


class Test_modelTest : public QObject
{
    Q_OBJECT

    // member
    static const QString m_testText01;
    static const QString m_testText02;

public:
    Test_modelTest();

private Q_SLOTS:
    void test_clear();
    void test_setPlainText();
    void test_appendPlainText();
};

// initialise the static const member
const QString Test_modelTest::m_testText01 = QString("This is some text to test the model! \
Foo Bar\nLore ipsum doloret set…");
const QString Test_modelTest::m_testText02 = QString("\nThe Appendables 2\n");

Test_modelTest::Test_modelTest()
{
}

/*
 * test_clear
 * ----------
 * test the models clear methods
 */
void Test_modelTest::test_clear()
{
    // test clearPlainText
    Model model{Model()};
    model.setPlainText(m_testText01);
    QVERIFY(!model.getPlainText().isEmpty());
    model.clearPlainText();
    QVERIFY(model.getPlainText().isEmpty());

    // test clearAll
    model.setPlainText(m_testText02);
    QVERIFY(!model.getPlainText().isEmpty());
    model.clearAll();
    QVERIFY(model.getPlainText().isEmpty());
}

/*
 * test_setPlainText
 * -----------------
 * test the models setPlainText method
 */
void Test_modelTest::test_setPlainText()
{
    Model model = Model();
    model.setPlainText(m_testText01);
    QCOMPARE(model.getPlainText(), m_testText01);
}

/*
 * test_appendPlainText
 * --------------------
 * test the models appendPlainText method
 */
void Test_modelTest::test_appendPlainText()
{
    Model model{Model()};
    model.setPlainText(m_testText01);
    model.appendPlainText(m_testText02);
    QCOMPARE(model.getPlainText(), m_testText01 + m_testText02);
}


QTEST_APPLESS_MAIN(Test_modelTest)

#include "test_modeltest.moc"
