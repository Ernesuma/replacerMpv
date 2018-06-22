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
    bool replace(const QString& plain, QString& final, const tagMap& tags) const;

};

#endif // REPLACER_H
