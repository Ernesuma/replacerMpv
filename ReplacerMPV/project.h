#ifndef PROJECT_H
#define PROJECT_H

#include <QDir>

class Project
{
private:
    // member
    QString m_name{};
    QDir m_projectDir{};

public:
    Project(QString name, QDir path);

    QString getName() const;
    QDir getProjectDir() const;

    QDir getPlainTextFilePath() const;
    QDir getTagsFilePath() const;
};
#endif // PROJECT_H
