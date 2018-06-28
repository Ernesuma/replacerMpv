#ifndef REPLACER_H
#define REPLACER_H

#include <memory>
#include <regex>
#include <QString>

#include "tagmapmodel.h"

class Replacer
{
public:
    // constructor
    Replacer(){};

    // destructor
    ~Replacer(){};

    // replace method
    static bool replace(const QString& plain,
                        QString& final,
                        const TagMapModel::tagMap& tags);

};

#endif // REPLACER_H
