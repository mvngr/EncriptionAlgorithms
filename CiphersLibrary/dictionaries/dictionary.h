#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <map>
#include <QString>

#include "CiphersLibrary_global.h"

enum MergeOption {
    FillFromOtherDict = 0,
    Numbers
};

class CIPHERSLIBRARY_EXPORT Dictionary
{
public:
    Dictionary();
    virtual ~Dictionary();

    std::vector<QChar> dictionary() const;
    std::vector<std::vector<QChar>> mergeWithDictionary(const Dictionary &dict, const MergeOption option = MergeOption::FillFromOtherDict) const;
    virtual std::vector<std::vector<QChar>> makeSquareDictionaryMatrix(const QString &keyword = QString()) const = 0;
    QChar offsetChar(const QChar &sourceChar, int offset) const;

protected:
    static QString uniqueCharsInString(const QString &sourceString);
    std::vector<QChar> dictionary_;
};

#endif // DICTIONARY_H
