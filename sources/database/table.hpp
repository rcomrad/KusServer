#ifndef TABLE_HPP
#define TABLE_HPP

#include "database_structures.hpp"

#include "struct_array.hpp"

namespace data
{

template <typename T>
class Table : public StructArray<T>
{
public:
    std::string getFirstAsCondition()
    {
        std::string result;
        for (auto& i : this->getRow(0))
        {
            auto temp = toString(i.type, i.ptr);
            if (!temp.empty())
            {
                result += toString(i.type, i.ptr) + " AND ";
            }
        }
        result.resize(result.size() - 4);
        return result;
    }

    std::string getAllAsInsert()
    {
        std::string result;
        for (auto& i : *this)
        {
            result += "(";
            for (auto& j : i)
            {
                auto temp = toString(j.type, j.ptr);
                if (temp.empty()) temp = "default";
                result += temp + ",";
            }
            result[result.size() - 2] = ')';
            result.back()             = ',';
        }
        result[result.size() - 2] = ' ';
        return result;
    }

    std::string getFirstAsUpdate()
    {
        std::string result;
        auto names = AsteriskHendler::table[T::tableName];
        for (auto& i : this->getRow(0))
        {
            auto temp = toString(i.type, i.ptr);
            if (!temp.empty())
            {
                result += names[i.num] + "=" + toString(i.type, i.ptr) + ", ";
            }
        }
        result.resize(result.size() - 2);
        return result;
    }

    bool loadFromRawData(const std::vector<std::vector<std::string>>& aData)
    {
        bool result = false;

        if (aData.size() != 0 && (aData[0].size() == this->columnCount() ||
                                  aData[0].size() == this->columnCount() - 1))
        {
            bool hasOffset = this->columnCount() - aData[0].size();
            result         = true;

            for (auto& i : aData)
            {
                bool flag = hasOffset;
                this->emplace_back();
                for (auto& i : this->backRow())
                {
                    if (flag)
                    {
                        flag = false;
                    }
                    else
                    {
                        fromString(i.type, i.ptr, i);
                    }
                }
            }
        }

        return result;
    }

    //--------------------------------------------------------------------------------

private:
    std::string toString(data::Type aType, void* aPtr)
    {
        std::string result;
        switch (aType)
        {
            case data::Type::INT:
                if (*((int*)aPtr) != 0) result = wrap(*((int*)aPtr));
                break;
            case data::Type::BOOL:
                if (*((char*)aPtr) != -1) result = wrap(bool(*((char*)aPtr)));
                break;
            case data::Type::STRING:
                if (!((std::string*)aPtr)->empty())
                    result = wrap(*((std::string*)aPtr));
                break;
        }
        return result;
    }

    void fromString(data::Type aType, void* aPtr, const std::string& aData)
    {
        switch (aType)
        {
            case data::Type::INT:
                *(int*)aPtr = std::stoi(aData);
                break;
            case data::Type::BOOL:
                // TODO: other bool formats
                *(bool*)aPtr = aData == "true";
                break;
            case data::Type::STRING:
                *(std::string*)aPtr = aData;
                break;
        }
    }
};

} // namespace data

//--------------------------------------------------------------------------------

#endif // !TABLE_HPP
