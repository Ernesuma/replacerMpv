#include "model.h"

Model::Model()
{

}

const QString &Model::getPlainText() const
{
    return m_plainText;
}

void Model::setPlainText(const QString &text)
{
    m_plainText = text;
}

void Model::appendPlainText(const QString &text)
{
    m_plainText.append(text);
}
