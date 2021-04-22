#include "dictionary.h"

#include "commonAlghorithms.h"
#include <QObject>
#include <QDebug>
#include <algorithm>

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
    case MergeOption::Numbers:
        std::size_t counter = 0;
        for(std::size_t i = 0; i < dictionary_.size(); i++)
        {
            res.push_back(std::vector<QChar>());
            for(std::size_t j = 0; j < dict.dictionary().size(); j++)
            {
                res.at(i).push_back(static_cast<wchar_t>(counter++));
            }
        }
        break;
    }

    return res;
}

QChar Dictionary::offsetChar(const QChar &sourceChar, int offset) const
{
    auto pos = MyAlgo::findPosition(dictionary_, sourceChar);
    if(!pos)
    {
        qWarning() << QObject::tr("Не удалось найти символ %1 в словаре").arg(sourceChar);
        return QChar('!');
    }
    else
    {
        //делаем так, чтобы у нас всегда выходило положительное число

        if(offset < 0)
        {
            //пожалуйста, не смотрите в эту ветку if
            //ну я же прошу
            //не читайте код ниже по этому ифу
            int current = *pos;
            for(int i = 0; i < std::abs(offset); i++)
            {
                if(current != 0)
                    current--;
                else
                    current = dictionary_.size() - 1;

            }
            return dictionary_.at(current);
        }
        else
            return dictionary_.at((*pos + offset ) % dictionary_.size());
    }
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
