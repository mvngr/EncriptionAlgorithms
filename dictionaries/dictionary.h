#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <vector>
#include <map>
#include <QString>

enum MergeOption {
    FillFromOtherDict = 0
};

class Dictionary
{
public:
    Dictionary();

    std::vector<QChar> dictionary() const;
    std::vector<std::vector<QChar>> mergeWithDictionary(const Dictionary &dict, const MergeOption option = MergeOption::FillFromOtherDict) const;

protected:
    std::vector<QChar> dictionary_;
};

#endif // DICTIONARY_H
