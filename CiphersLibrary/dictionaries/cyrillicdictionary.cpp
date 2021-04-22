#include "cyrillicdictionary.h"

CyrillicDictionary::CyrillicDictionary() : Dictionary()
{
    dictionary_ = {
        L'а', L'б', L'в', L'г', L'д', L'е', L'ё', L'ж', L'з', L'и', L'й', L'к', L'л',
        L'м', L'н', L'о', L'п', L'р', L'с', L'т', L'у', L'ф', L'х', L'ц', L'ч', L'ш',
        L'щ', L'ъ', L'ы', L'ь', L'э', L'ю', L'я',
        L'.', ',', ' ' //довел до 36 символов для квадрата. Нужен в некоторых алгоритмах
    };
}

CyrillicDictionary::~CyrillicDictionary()
{

}

std::vector<std::vector<QChar>> CyrillicDictionary::makeSquareDictionaryMatrix(const QString &keyword) const
{
    const std::size_t matrixSize = 6;
    std::vector<std::vector<QChar>> res(matrixSize);

    auto dictCopy = dictionary_;    

    QString uniqueKeywordChars = uniqueCharsInString(keyword);
    std::remove_if(dictCopy.begin(), dictCopy.end(), [&uniqueKeywordChars](const QChar &value){
        return uniqueKeywordChars.contains(value);
    });

    std::size_t dictCopyIndex = 0;
    for(std::size_t i = 0; i < res.size(); i++)
    {
        for(std::size_t j = 0; j < res.size(); j++)
        {
            //если у нас есть ключевое слово - помещаем его в начало
            if(uniqueKeywordChars.size() > matrixSize * i + j)
            {
                res.at(i).push_back( uniqueKeywordChars.at(matrixSize * i + j) );
            }
            else
            {
                res.at(i).push_back( dictCopy.at(dictCopyIndex++) );
            }
        }
    }

    return res;
}
