#ifndef MODEL_H
#define MODEL_H

#include<QString>
#include"tagmapmodel.h"

class Model
{
    QString m_plainText{""};
    QString m_finalText{""};
    TagMapModel m_tagMapModel;

public:
    Model();

    // getter
    const QString &getPlainText() const;
    const QString &getFinalText() const;

    // get access to the raw pointer to the tag map class
    // USE WITH CARE!
    TagMapModel* getTagMapModelRawPtr();
    const tagMap& getTagMap() const;

    // setter
    void setPlainText(const QString &text);
    void setFinalText(const QString &text);
    void appendPlainText(const QString &text);

    // cleaner
    void clearPlainText();
    void clearAll();

    // other
    void addTag2List(const QString& tag, const QString& value);
};

#endif // MODEL_H
