#include "project.h"

Project::Project() :
    m_name(),
    m_projectDir() {

}

Project::Project(QString name, QDir path) {
    setName(name);
    setProjectDir(path);
}

QString Project::getName() const
{
    return this->m_name;
}

QDir Project::getProjectDir() const
{
    return this->m_projectDir;
}

void Project::setName(QString name)
{
    // todo: check name for validity
    this->m_name = name;
}

void Project::setProjectDir(QDir path)
{
    // todo: check of path
    this->m_projectDir = path;
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
