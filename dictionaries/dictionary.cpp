#include "dictionary.h"

Dictionary::Dictionary()
{

}

Dictionary::~Dictionary()
{

}

std::vector<QChar> Dictionary::dictionary() const
{
    return dictionary_;
}

std::vector<std::vector<QChar>> Dictionary::mergeWithDictionary(const Dictionary &dict, const MergeOption option) const
{
    std::vector<std::vector<QChar>> res;

    switch (option)
    {
    case MergeOption::FillFromOtherDict:
        for(std::size_t i = 0; i < dictionary_.size(); i++)
        {
            res.push_back(std::vector<QChar>());
            //смещение
            for(std::size_t j = dict.dictionary().size() - i; j < dict.dictionary().size(); j++)
            {
                res.at(i).push_back(dict.dictionary().at(j));
            }
            //основная часть
            for(std::size_t j = 0; j < dict.dictionary().size() - i; j++)
            {
                res.at(i).push_back(dict.dictionary().at(j));
            }
        }
        break;
    }

    return res;
}

QString Dictionary::uniqueCharsInString(const QString &sourceString)
{
    std::vector<QChar> vec;
    for(int i = 0; i < sourceString.size(); i++)
    {
        auto foundIt = std::find(vec.cbegin(), vec.cend(), sourceString.at(i));
        if(foundIt == vec.cend())
        {
            vec.push_back(sourceString.at(i));
        }
    }

    QString res(vec.size(), ' ');
    for(std::size_t i = 0; i < vec.size(); i++)
        res[static_cast<int>(i)] = vec.at(i);

    return res;
}
