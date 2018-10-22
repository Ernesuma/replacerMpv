#include "project.h"

Project::Project(QString name, QDir path)
{
    this->m_name = name;
    this->m_projectDir = path;
}

QString Project::getName() const
{
    return this->m_name;
}

QDir Project::getProjectDir() const
{
    return this->getProjectDir();
}

QDir Project::getPlainTextFilePath() const
{
    // todo: replace mock implementation
    return QDir("~/testProject/plain.txt");
}

QDir Project::getTagsFilePath() const
{
    // todo: replace mock implementation
    return QDir("~/testProject/tag.map");
}
