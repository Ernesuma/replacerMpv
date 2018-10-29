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
    Project();
    Project(QString name, QDir path);

    QString getName() const;
    QDir getProjectDir() const;

    void setName(QString name);
    void setProjectDir(QDir path);

    QDir getPlainTextFilePath() const;
    QDir getTagsFilePath() const;
    bool isEmpty() const;
};
#endif // PROJECT_H
