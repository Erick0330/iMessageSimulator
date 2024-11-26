#include "iscorrectstring.h"

IsCorrectString::IsCorrectString()
{
}

bool IsCorrectString::verify(string s)
{
    bool safe = false;

    if(s.empty())
        return false;


    for(size_t i = 0; i < s.length(); i++){
        char c = s[i];
        if(!std::isspace(c))
            return true;
    }


    return safe;
}

