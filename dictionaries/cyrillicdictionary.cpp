#include "cyrillicdictionary.h"

CyrillicDictionary::CyrillicDictionary() : Dictionary()
{
    dictionary_ = {L'а', L'б', L'в', L'г', L'д', L'е', L'ё', L'ж', L'з', L'и', L'й', L'к', L'л',
                   L'м', L'н', L'о', L'п', L'р', L'с', L'т', L'у', L'ф', L'х', L'ц', L'ч', L'ш',
                   L'щ', L'ъ', L'ы', L'ь', L'э', L'ю', L'я'};
}
