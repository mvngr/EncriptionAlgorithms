#ifndef CYRILLICDICTIONARY_H
#define CYRILLICDICTIONARY_H

#include "dictionary.h"

class CyrillicDictionary : public Dictionary
{
public:
    CyrillicDictionary();
    virtual ~CyrillicDictionary();

    virtual std::vector<std::vector<QChar>> makeSquareDictionaryMatrix(const QString &keyword = QString()) const override;
};

#endif // CYRILLICDICTIONARY_H
