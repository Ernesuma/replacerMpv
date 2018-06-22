#include "replacer.h"

bool Replacer::replace(const QString &plain, QString &final, const tagMap &tags) const
{
    // get std::string to work on with regular expressions
    std::string finalStd{plain.toStdString()};

    // get list of keys and iterate through
    auto keys = tags.uniqueKeys();
    foreach (auto key, keys)
    {
        // create regular expression from key
        std::string exprStr{"\\{"+key.toStdString()+"\\}"};
        std::regex expr(exprStr);

        // replace all occurencies of the regex with the value from the tag map
        finalStd = std::regex_replace(finalStd, expr, tags[key].toStdString());
    }
    // return the final text
    final = finalStd.c_str();

    // return 'true' for success
    return true;
}
