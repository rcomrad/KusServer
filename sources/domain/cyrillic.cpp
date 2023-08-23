#include "cyrillic.hpp"

#include <cwctype>
#include <unordered_map>
#include <vector>

//--------------------------------------------------------------------------------

dom::Cyrilic dom::Cyrilic::global;

void
dom::Cyrilic::standardProcedure(std::wstring& aStr) noexcept
{
    dom::Cyrilic::global.cutOffEnding(aStr);
    dom::Cyrilic::global.destroyBadCharacters(aStr);
    dom::Cyrilic::global.toUpper(aStr);
    dom::Cyrilic::global.destroyWhiteSpaces(aStr, true);
}

void
dom::Cyrilic::toLower(std::wstring& aStr) noexcept
{
    for (auto& i : aStr)
    {
        if (i >= L'А' && i <= L'Я' || i == L'Ё')
        {
            if (i == L'Ё')
            {
                i = L'ё';
            }
            else
            {
                i -= L'А';
                i += L'а';
            }
        }
        else if (i >= L'A' && i <= L'Z')
        {
            i -= L'A';
            i += L'a';
        }
    }
}

//--------------------------------------------------------------------------------

void
dom::Cyrilic::toUpper(std::wstring& aStr) noexcept
{
    for (auto& i : aStr)
    {
        if (i >= L'а' && i <= L'я' || i == L'ё')
        {
            if (i == L'ё')
            {
                i = L'Ё';
            }
            else
            {
                i -= L'а';
                i += L'А';
            }
        }
        else if (i >= L'a' && i <= L'z')
        {
            i = std::towupper(i);
        }
    }
}

//--------------------------------------------------------------------------------

std::wstring
dom::Cyrilic::toWString(const std::string& aStr) noexcept
{
    return toWString(aStr.c_str());
}

//--------------------------------------------------------------------------------

std::wstring
dom::Cyrilic::toWString(const char* aStr) noexcept
{
    std::wstring result;
    auto str   = const_cast<char*>(aStr);
    uint8_t* s = (uint8_t*)str;

    for (uint8_t* c(s); *c != '\000'; ++c)
    {
        if (*c == 208 || *c == 209)
        {
            result.push_back((*c == 208 ? 896 : 960) + *++c);
        }
        else
        {
            result.push_back(static_cast<wchar_t>(*c));
        }
    }
    return result;
}

//--------------------------------------------------------------------------------

void
dom::Cyrilic::destroyBadCharacters(std::wstring& aStr) noexcept
{
    for (auto& i : aStr)
    {
        if (i == L'ё')
        {
            i = L'е';
        }
        else if (i == L'Ё')
        {
            i = L'Е';
        }
        else if (i == L'й')
        {
            i = L'и';
        }
        else if (i == L'Й')
        {
            i = L'И';
        }
        else if (i == L'A')
        {
            i = L'А';
        }
        else if (i == L'B')
        {
            i = L'В';
        }
        else if (i == L'a')
        {
            i = L'а';
        }
        else if (i == L'b')
        {
            i = L'в';
        }
        else if (i == L',')
        {
            i = L' ';
        }
        else if (i == L'.')
        {
            i = L' ';
        }
        else if (i == L'-')
        {
            i = L' ';
        }
        else if (i == L':')
        {
            i = L' ';
        }
        else if (i == L';')
        {
            i = L' ';
        }
    }
}

//--------------------------------------------------------------------------------

void
dom::Cyrilic::destroyWhiteSpaces(std::wstring& aStr, bool flag) noexcept
{
    int l = 0, r = 0;
    char last = ' ';
    while (r < aStr.size())
    {
        aStr[l] = aStr[r];
        if (flag)
        {
            if (!(std::iswspace(aStr[r])))
            {
                ++l;
            }
        }
        else
        {
            if (!(std::iswspace(last) && std::iswspace(aStr[r])))
            {
                ++l;
            }
        }
        last = aStr[r];
        ++r;
    }
    aStr.resize(l);
    if (std::iswspace(aStr.back()))
    {
        aStr.pop_back();
    }
}

//--------------------------------------------------------------------------------

void
dom::Cyrilic::cutOffEnding(std::wstring& aStr) noexcept
{
    if (aStr.size() < 5) return;

    if (aStr == L"геометрическая")
    {
        int yy = 0;
        ++yy;
    }

    std::vector<std::wstring> endings = {L"ой", L"ая", L"ое", L"ые"};
    aStr.push_back(L' ');
    for (auto& i : endings)
    {
        destroyWord(aStr, i + L" ");
    }
    if (aStr.back() == L' ') aStr.pop_back();
}

//--------------------------------------------------------------------------------

void
dom::Cyrilic::destroyWord(std::wstring& aStr,
                          const std::wstring& aWord) noexcept
{
    int num = 0;
    for (int i = 0; i < aStr.size(); ++i)
    {
        if (aStr[i] == aWord[num])
        {
            ++num;
        }
        else
        {
            num = 0;
        }
        if (num == aWord.size())
        {
            while (num)
            {
                aStr[i - aWord.size() + num--] = ' ';
            }
        }
    }
}

//--------------------------------------------------------------------------------

char*
dom::Cyrilic::toLowerCyrillic(const char* aCharacter) noexcept
{
    char* res(new char[3]);
    res[2] = '\000';

    if (aCharacter[1] == '\201')
    {
        res[0] = '\321';
        res[1] = '\221';
    }
    else if (aCharacter[1] < '\240')
    {
        res[0] = '\320';
        res[1] = static_cast<char>(aCharacter[1] + ' ');
    }
    else
    {
        res[0] = '\321';
        res[1] = static_cast<char>(aCharacter[1] - ' ');
    }

    return res;
}

char*
dom::Cyrilic::toUpperCyrillic(const char* aCharacter) noexcept
{
    char* res(new char[3]);
    res[0] = '\320';
    res[2] = '\000';

    if (aCharacter[0] == '\320')
    {
        res[1] = static_cast<char>(aCharacter[1] - ' ');
    }
    else
    {
        if (aCharacter[1] == '\221')
        {
            res[1] = '\201';
        }
        else
        {
            res[1] = static_cast<char>(aCharacter[1] + ' ');
        }
    }

    return res;
}

//--------------------------------------------------------------------------------
std::string
dom::Cyrilic::translit(const std::string& aStr) noexcept
{
    static std::unordered_map<std::string, std::string> dict = {
        {"А", "A"},
        {"а", "a"},
        {"Б", "B"},
        {"б", "b"},
        {"В", "V"},
        {"в", "v"},
        {"Г", "G"},
        {"г", "g"},
        {"Ґ", "G"},
        {"ґ", "g"},
        {"Д", "D"},
        {"д", "d"},
        {"Е", "E"},
        {"е", "e"},
        {"Є", "E"},
        {"є", "e"},
        {"Ж", "Zh"},
        {"ж", "zh"},
        {"З", "Z"},
        {"з", "z"},
        {"И", "I"},
        {"и", "i"},
        {"І", "I"},
        {"і", "i"},
        {"Ї", "Yi"},
        {"ї", "yi"},
        {"Й", "J"},
        {"й", "j"},
        {"К", "K"},
        {"к", "k"},
        {"Л", "L"},
        {"л", "l"},
        {"М", "M"},
        {"м", "m"},
        {"Н", "N"},
        {"н", "n"},
        {"О", "O"},
        {"о", "o"},
        {"П", "P"},
        {"п", "p"},
        {"Р", "R"},
        {"р", "r"},
        {
         "С", "S",
         },
        {"с", "s"},
        {"Т", "T"},
        {"т", "t"},
        {"У", "U"},
        {"у", "u"},
        {"Ф", "F"},
        {"ф", "f"},
        {"Х", "H"},
        {"х", "h"},
        {"Ц", "Ts"},
        {"ц", "ts"},
        {"Ч", "ch"},
        {"ч", "ch"},
        {
         "Ш", "Sh",
         },
        {"ш", "sh"},
        {"Щ", "Shh"},
        {"щ", "shh"},
        {
         "Ь", "'",
         },
        {"ь", "'"},
        {"Ю", "Yu"},
        {"ю", "yu"},
        {"Я", "Ya"},
        {"я", "ya"},
        {"Ы", "Y"},
        {"ы", "y"},
        {"Ъ", ""},
        {"ъ", ""},
        {"Ё", "Yo"},
        {"ё", "yo"},
        {"Э", "E"},
        {"э", "e"}
    };

    std::string result;
    for (int i = 0; i < aStr.size(); ++i)
    {
        std::string temp = aStr.substr(i, 2);
        auto it          = dict.find(temp);
        if (it != dict.end())
        {
            result += it->second;
            ++i;
        }
        else
        {
            result += temp;
        }
    }
    return result;
}
