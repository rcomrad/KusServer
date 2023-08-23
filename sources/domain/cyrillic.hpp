#ifndef CYRILLIC_HPP
#define CYRILLIC_HPP

//--------------------------------------------------------------------------------

#include <string>

//--------------------------------------------------------------------------------

namespace dom
{
class Cyrilic
{
public:
    static Cyrilic global;

    void toLower(std::wstring& aStr) noexcept;
    void toUpper(std::wstring& aStr) noexcept;

    std::wstring toWString(const std::string& aStr) noexcept;
    std::wstring toWString(const char* aStr) noexcept;

    void destroyBadCharacters(std::wstring& aStr) noexcept;
    void destroyWhiteSpaces(std::wstring& aStr, bool flag = false) noexcept;
    void destroyWord(std::wstring& aStr, const std::wstring& aWord) noexcept;
    void cutOffEnding(std::wstring& aStr) noexcept;
    void standardProcedure(std::wstring& aStr) noexcept;
    static std::string translit(const std::string& aStr) noexcept;

private:
    Cyrilic()  = default;
    ~Cyrilic() = default;

    Cyrilic(const Cyrilic& other)            = delete;
    Cyrilic& operator=(const Cyrilic& other) = delete;

    Cyrilic(Cyrilic&& other) noexcept            = default;
    Cyrilic& operator=(Cyrilic&& other) noexcept = default;

    char* toLowerCyrillic(const char* aCharacter) noexcept;
    char* toUpperCyrillic(const char* aCharacter) noexcept;
};
} // namespace dom

//--------------------------------------------------------------------------------

#endif // !CYRILLIC_HPP
