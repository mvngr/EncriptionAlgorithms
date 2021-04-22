#ifndef DIGITDICTIONARY_H
#define DIGITDICTIONARY_H

#include "dictionary.h"

class CIPHERSLIBRARY_EXPORT DigitDictionary : public Dictionary
{
public:
    DigitDictionary();
    virtual ~DigitDictionary();

    virtual std::vector<std::vector<QChar>> makeSquareDictionaryMatrix(const QString &keyword = QString()) const override;
};

#endif // DIGITDICTIONARY_H
