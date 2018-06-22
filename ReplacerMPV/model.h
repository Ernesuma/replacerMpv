#ifndef MODEL_H
#define MODEL_H

#include<QString>

class Model
{
    QString m_plainText{""};
public:
    Model();

    // getter
    const QString &getPlainText() const;

    // setter
    void setPlainText(const QString &text);
    void appendPlainText(const QString &text);

    // cleaner
    void clearPlainText();
    void clearAll();
};

#endif // MODEL_H
