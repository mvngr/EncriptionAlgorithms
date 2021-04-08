#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <map>
#include <QString>

enum MergeOption {
    FillFromOtherDict = 0,
    Numbers
};

class Dictionary
{
public:
    Dictionary();
    virtual ~Dictionary();

    std::vector<QChar> dictionary() const;
    std::vector<std::vector<QChar>> mergeWithDictionary(const Dictionary &dict, const MergeOption option = MergeOption::FillFromOtherDict) const;
    virtual std::vector<std::vector<QChar>> makeSquareDictionaryMatrix(const QString &keyword = QString()) const = 0;

protected:
    static QString uniqueCharsInString(const QString &sourceString);
    std::vector<QChar> dictionary_;
};

#endif // DICTIONARY_H
