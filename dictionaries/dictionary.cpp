#include "dictionary.h"

Dictionary::Dictionary()
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
