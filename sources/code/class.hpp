#ifndef CLASS_HPP
#define CLASS_HPP

#include <fstream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace code
{

class Class
{
public:
private:
    std::string mFileName;
    std::string mClassName;
    std::string mNamespace;
    std::string mDefineName;
    std::string mPath;

    std::string mDefaultTemplate;
    std::string mDefaultReturnType;
    std::string mDefaultResultBegin;
    std::string mDefaultResultEnd;

    std::set<std::string> mIncludes;
    std::set<std::string> mCPPIncludes;
    std::vector<Function> mFunctions;
    std::vector<StaticVar> mStaticVariables;
};

} // namespace code

#endif // !CLASS_HPP
