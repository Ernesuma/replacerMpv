#include "model.h"

Model::Model()
{

}

const QString &Model::getPlainText() const
{
    return m_plainText;
}

const QString &Model::getFinalText() const
{
    return m_finalText;
}

const bool Model::isTagMapEmpty() const
{
    return (0 == m_tagMapModel.rowCount());
}

TagMapModel *Model::getTagMapModelRawPtr()
{
    return &m_tagMapModel;
}

const tagMap &Model::getTagMap() const
{
    return m_tagMapModel.getTagMap();
}

void Model::setPlainText(const QString &text)
{
    m_plainText = text;
}

void Model::setFinalText(const QString &text)
{
    m_finalText = text;
}

void Model::appendPlainText(const QString &text)
{
    m_plainText.append(text);
}

void Model::clearPlainText()
{
    m_plainText.clear();
}

void Model::clearAllTags()
{
    // remove all entries of the tag map model
    m_tagMapModel.removeAllRows();
}

void Model::clearAll()
{
    clearPlainText();
}

void Model::addTag2List(const QString &tag, const QString &value)
{
    m_tagMapModel.insert(tag, value);
}
