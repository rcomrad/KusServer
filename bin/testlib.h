#define WITHOUT_LOGS

#ifdef PART_OF_FILE_STD_READERS
#	define PART_OF_FILE_READER_ADD
#endif

#ifndef TESTLIBRARY_TESTLIBRARYSECURE_H
#define TESTLIBRARY_TESTLIBRARYSECURE_H

#ifdef _MSC_VER
#   define _CRT_SECURE_NO_WARNINGS

#   define __nonnull(params)
#endif

#ifdef SYSTEMKA_RUNNING
#   define NDEBUG
#endif

#include <cassert>

#ifdef NDEBUG
#   define TESTLIBRARY_ASSERT(expression, message) void(0)
#   define TESTLIBRARY_NONNULL_ASSERT(ptr) void(0)
#else
#    ifdef __GNUC__
#        define TESTLIBRARY_ASSERT(expression, message)						\
         if (!(expression))                                                 \
             __assert_fail(message, __FILE__, __LINE__, __ASSERT_FUNCTION)
#    elif _MSC_VER
#        define TESTLIBRARY_ASSERT(expression, message)						\
         if (!(expression))                                                 \
             _wassert(L ## message, __FILEW__,                              \
                     static_cast<unsigned>(__LINE__))
#   endif
#   define TESTLIBRARY_NONNULL_ASSERT(ptr)                                  \
        TESTLIBRARY_ASSERT(ptr != nullptr, #ptr " can't be null")
#endif

#endif //TESTLIBRARY_TESTLIBRARYSECURE_H

#ifndef TESTLIBRARY_TESTLIBRARYIOSETTINGS_H
#define TESTLIBRARY_TESTLIBRARYIOSETTINGS_H

#ifdef __GNUC__
#   include <unistd.h>

#   define CORRECT_VER(funcName) funcName
#elif defined(_MSC_VER)
#   include <io.h>

#   define CORRECT_VER(funcName) _ ## funcName
#endif

#include <fcntl.h>

#endif //TESTLIBRARY_TESTLIBRARYIOSETTINGS_H

#ifndef TESTLIBRARY_LOGGER_H
#define TESTLIBRARY_LOGGER_H

#ifndef WITHOUT_LOGS
#include <cstdio>
#include <cstdint>
#include <cstdarg>

#include <iostream>


namespace tl
{
    class Logger
    {
    public:
        explicit Logger(const char* funcName,
                        std::uint8_t funcNameSize);

        void funcStartLog(const char* format = nullptr, ...);

        void funcFinishLog(const char* format = nullptr, ...);

        static void resultLog(const char* messageFormat, std::va_list& ap);

    private:
        const char* mFuncName;
        std::uint8_t mFuncNameSize;
#ifdef TIME_CHECK_IN_LOGS
        double mStartTime;
        double mFinishTime;
#endif //TIME_CHECK_IN_LOGS

        static std::FILE* mFile;
        static std::uint8_t mCountTabs;

        static void write(const char* message, std::size_t messageSize);
    };
}

#if !defined(__PRETTY_FUNCTION__) && defined(_MSC_VER)
#   define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#define FUNC_START_LOG(loggerName, ...)                                          \
    tl::Logger loggerName(__PRETTY_FUNCTION__, sizeof(__PRETTY_FUNCTION__) - 1); \
    (loggerName).funcStartLog(__VA_ARGS__)

#define FUNC_FINISH_LOG(logger, ...) (logger).funcFinishLog(__VA_ARGS__)

#define FUNC_RETURN_LOG(logger, resultType, resultName, format, returnVal) \
    resultType resultName(returnVal);                                      \
    (logger).funcFinishLog(format, resultName);                            \
                                                                           \
    return resultName

#define BOOL_FUNC_RETURN_LOG(logger, resultName, returnVal)  \
    bool resultName(returnVal);                              \
    (logger).funcFinishLog((resultName) ? "true" : "false"); \
                                                             \
    return resultName
#else
#define FUNC_START_LOG(loggerName, ...) void(0)

#define FUNC_FINISH_LOG(logger, ...) void(0)

#define FUNC_RETURN_LOG(logger, resultType, resultName, format, returnVal) \
    return returnVal

#define BOOL_FUNC_RETURN_LOG(logger, resultName, returnVal) return returnVal
#endif //WITHOUT_LOGS

#endif //TESTLIBRARY_LOGGER_H

#ifndef TESTLIBRARY_RESULTWRITER_H
#define TESTLIBRARY_RESULTWRITER_H

#include <cstdarg>
#include <cstdio>
#include <cstdlib>


namespace tl
{
    class ResultWriter
            {
    public:
        static void vOKResultWr(const char* format,
                                std::va_list& ap);

        static void vWAResultWr(const char* format,
                                std::va_list& ap);

        static void vPEResultWr(const char* format,
                                std::va_list& ap);

        static void OKResultWr(const char* format, ...);

        static void WAResultWr(const char* format, ...);

        static void PEResultWr(const char* format, ...);

    private:
        static void printMessage(const char* result,
                                 const char* format,
                                 std::va_list& ap);
    };
}

#endif //TESTLIBRARY_RESULTWRITER_H

#ifndef TESTLIBRARY_ABSTRACTREADER_H
#define TESTLIBRARY_ABSTRACTREADER_H

#include "TestLibrarySecure.hpp"

#ifdef __GNUC__
#   include <sys/stat.h>
// #elif defined(_MSC_VER)
// #   include <Windows.h>
#endif

#include <cmath>
#include <cfloat>
#include <cstring>

#include <string>
#include <vector>
#include <functional>

#include "TestLibraryIOSettings.hpp"

#include "ResultWriter.hpp"

#define IS_NOT_OPEN_ASSERT TESTLIBRARY_ASSERT(isOpen(), "file isn't open")

#ifdef READ_SELFMADE_ERRORS
#   define READ_SUCCESS 0
#   define READ_EOF -1
#   define READ_TYPE_ERROR -2
#   define READ_INCORRECT_SIZE -3

#   define READ_RET_TYPE int

#   define READ_POS_RESULT(logger, result)               \
        FUNC_FINISH_LOG(logger, #result"(%d)", result);  \
                                                         \
        return result

#   define READ_NEG_RESULT(logger, result, message, ...)                       \
        FUNC_FINISH_LOG(logger, #result"(%d), " message, result __VA_ARGS__);  \
                                                                               \
        return result

#   define READ_USE_INSERT_FUNC_RESULT(logger, resultName, insertFuncCall)       \
        FUNC_RETURN_LOG(logger, READ_RET_TYPE, resultName, "%d", insertFuncCall)

#   define READ_CHECK_INSERT_FUNC_RESULT(logger, resultName, insertFuncCall) \
        READ_RET_TYPE resultName(insertFuncCall);                            \
        if (resultName != READ_SUCCESS)                                      \
        {                                                                    \
            FUNC_FINISH_LOG(logger, "%d", resultName);                       \
            return resultName;                                               \
        }
#else
#   define READ_SUCCESS
#   define READ_EOF WAResultWr
#   define READ_TYPE_ERROR PEResultWr
#   define READ_INCORRECT_SIZE WAResultWr

#   define READ_RET_TYPE void

#   define READ_POS_RESULT(logger, result) FUNC_FINISH_LOG(logger)

#   define _READ_NEG_RESULT(logger, result, message, ...) \
        tl::ResultWriter::result(message __VA_ARGS__)

#   define READ_NEG_RESULT(logger, result, message, ...) \
        _READ_NEG_RESULT(logger, result, message, __VA_ARGS__)

#   define READ_USE_INSERT_FUNC_RESULT(logger, resultName, insertFuncCall) \
        insertFuncCall;                                                    \
                                                                           \
        FUNC_FINISH_LOG(logger)

#   define READ_CHECK_INSERT_FUNC_RESULT(logger, resultName, insertFuncCall) \
        insertFuncCall
#endif //READ_SELFMADE_ERRORS

namespace tl
{
    using hugeInt = std::string;
    using hugeIntPtr = char*;

    class AbstractReader
    {
    public:
        ~AbstractReader();

        void changeMode();

        [[nodiscard]] bool isOpen() const;

        [[nodiscard]] bool isEndOfFile() const;

        void skipWhitespaces();

        void skipChar();

        void readAllFile(char*& fileStr);

        READ_RET_TYPE readWhitespace(char& whitespace);

        READ_RET_TYPE readWhitespaces(char*& whitespaces);

        READ_RET_TYPE readWhitespaces(std::string& whitespaces);

        READ_RET_TYPE readChar(char& c);

        READ_RET_TYPE readInt8(std::int8_t& i);

        READ_RET_TYPE readUInt8(std::uint8_t& i);

        READ_RET_TYPE readInt16(std::int16_t& i);

        READ_RET_TYPE readUInt16(std::uint16_t& i);

        READ_RET_TYPE readInt32(std::int32_t& i);

        READ_RET_TYPE readUInt32(std::uint32_t& i);

        READ_RET_TYPE readInt64(std::int64_t& i);

        READ_RET_TYPE readUInt64(std::uint64_t& i);

        READ_RET_TYPE readShort(short& s);

        READ_RET_TYPE readUShort(unsigned short& s);

        READ_RET_TYPE readInt(int& i);

        READ_RET_TYPE readUInt(unsigned int& i);

        READ_RET_TYPE readLong(long& l);

        READ_RET_TYPE readULong(unsigned long& l);

        READ_RET_TYPE readLongLong(long long& ll);

        READ_RET_TYPE readULongLong(unsigned long long& ll);

        READ_RET_TYPE readHugeInt(hugeIntPtr& i);

        READ_RET_TYPE readHugeInt(hugeInt& i);

        READ_RET_TYPE readFloat(float& num);

        READ_RET_TYPE readDouble(double& num);

        READ_RET_TYPE readBool(bool& b);

        READ_RET_TYPE readStr(char* s,
                              std::size_t sSize) __nonnull((2));

        READ_RET_TYPE readStr(char*& emptyS);

        READ_RET_TYPE readStr(std::string& s, std::size_t sSize);

        READ_RET_TYPE readStr(std::string& s);

        READ_RET_TYPE readLine(std::string& line);

    protected:
        char* mData;
        char* mBegin;

        explicit AbstractReader(bool ignoreWhitespaces = false);

    private:
        bool mIgnoreWhitespaces;

        [[nodiscard]] inline bool isNotWhitespace() const;

        [[nodiscard]] inline bool isWhitespace() const;

        [[nodiscard]] inline bool isNotDigit();

        template<typename NumT, typename SummandT,
                 typename = std::enable_if_t<std::is_arithmetic_v<NumT>>>
        [[nodiscard]] inline static
        bool isLessThanMin(NumT num, SummandT nextSummand) noexcept;

        template<typename NumT, typename SummandT,
                 typename = std::enable_if_t<std::is_arithmetic_v<NumT>>>
        [[nodiscard]] inline static
        bool isMoreThanMax(NumT num, SummandT nextSummand) noexcept;

        inline READ_RET_TYPE readAbstractStr(char*& s,
                                             bool (AbstractReader::*continueCond)() const,
                                             const std::function<bool()>& exitCond = [](){
                                                 return false;
                                             });

        inline READ_RET_TYPE readAbstractStr(std::string& s,
                                             bool (AbstractReader::*continueCond)() const,
                                             const std::function<bool()>& exitCond = [](){
                                                 return false;
                                             });

        template<typename IntT,
                 typename = std::enable_if_t<std::is_integral_v<IntT>>>
        READ_RET_TYPE readAbstractIntWithoutSign(
            IntT& num,
            bool(&checkOverflowFunc)(IntT, std::int8_t)
        ) noexcept;

        template<typename IntT,
                 typename = std::enable_if_t<std::is_integral_v<IntT>>>
        READ_RET_TYPE readAbstractPositiveInt(IntT& num) noexcept;

        template<typename IntT,
                 typename = std::enable_if_t<std::is_integral_v<IntT>>>
        READ_RET_TYPE readAbstractNegativeInt(IntT& num) noexcept;

        template<typename IntT,
                 typename = std::enable_if_t<std::is_integral_v<IntT>>>
        READ_RET_TYPE readAbstractInt(IntT& num) noexcept;

        template<typename IntT,
                 typename = std::enable_if_t<std::is_signed_v<IntT>>>
        READ_RET_TYPE readAbstractIntImpl(IntT& num, std::true_type) noexcept;

        template<typename IntT,
                 typename = std::enable_if_t<std::is_unsigned_v<IntT>>>
        READ_RET_TYPE readAbstractIntImpl(IntT& num, std::false_type) noexcept;

        template<typename Real>
        READ_RET_TYPE readAbstractReal(Real& num) noexcept;
    };
}

#endif //TESTLIBRARY_ABSTRACTREADER_H

#ifndef TESTLIBRARY_ABSTRACTPARTOFFILEREADER_H
#define TESTLIBRARY_ABSTRACTPARTOFFILEREADER_H

namespace tl
{
    class AbstractPartOfFileReader : public AbstractReader
    {
    protected:
        explicit AbstractPartOfFileReader(bool ignoreWhitespaces = false);

        explicit AbstractPartOfFileReader(int fd,
                                          bool ignoreWhitespaces = false);

        void openPart(int fd);
    };
}

#endif //TESTLIBRARY_ABSTRACTPARTOFFILEREADER_H

#ifndef TESTLIBRARY_ABSTRACTFILEREADER_H
#define TESTLIBRARY_ABSTRACTFILEREADER_H


namespace tl
{
    class AbstractFileReader : public AbstractReader
    {
    public:
        void open(int fd);

    protected:
        explicit AbstractFileReader(int fd, bool ignoreWhitespaces = false);

        explicit AbstractFileReader(bool ignoreWhitespaces);
    };
}

#endif //TESTLIBRARY_ABSTRACTFILEREADER_H

#ifndef TESTLIBRARY_PARTOFSTDINREADER_H
#define TESTLIBRARY_PARTOFSTDINREADER_H


namespace tl
{
    class PartOfStdinReader : public AbstractPartOfFileReader
    {
    public:
        explicit PartOfStdinReader(bool ignoreWhitespaces = false);
    };
}

#endif //TESTLIBRARY_PARTOFSTDINREADER_H

#ifdef PART_OF_FILE_READER_ADD
#ifndef TESTLIBRARY_PARTOFFILEREADER_H
#define TESTLIBRARY_PARTOFFILEREADER_H


namespace tl
{
    class PartOfFileReader : public AbstractPartOfFileReader
    {
    public:
        explicit PartOfFileReader(bool ignoreWhitespaces = false);

        explicit PartOfFileReader(int fd,
                                  bool ignoreWhitespaces = false);

        explicit PartOfFileReader(FILE*& file,
                                  bool ignoreWhitespaces = false);

        explicit PartOfFileReader(const char* path,
                                  bool ignoreWhitespaces = false);

        explicit PartOfFileReader(const std::string& path,
                                  bool ignoreWhitespaces = false);

        void open(int fd);

        void open(FILE*& file);

        void open(const char* path);

        void open(const std::string& path);

    private:
        static int mFd;
    };
}

#endif //TESTLIBRARY_PARTOFFILEREADER_H
#endif

#ifndef TESTLIBRARY_STDINREADER_H
#define TESTLIBRARY_STDINREADER_H


namespace tl
{
    class StdinReader : public AbstractFileReader
    {
    public:
        explicit StdinReader(bool ignoreWhitespaces = false);

    private:
        using AbstractFileReader::open;
    };
}

#endif //TESTLIBRARY_STDINREADER_H

#ifndef TESTLIBRARY_FILEREADER_H
#define TESTLIBRARY_FILEREADER_H


namespace tl
{
    class FileReader : public AbstractFileReader
    {
    public:
        explicit FileReader(bool ignoreWhitespaces = false);
        explicit FileReader(int fd, bool ignoreWhitespaces = false);

        explicit FileReader(FILE*& file, bool ignoreWhitespaces = false);

        explicit FileReader(const char* path,
                            bool ignoreWhitespaces = false) __nonnull((2));

        explicit FileReader(const std::string& path, bool ignoreWhitespaces = false);

        void open(FILE*& file);

        void open(const char* path) __nonnull((2));

        void open(const std::string& path);
    };
}

#endif //TESTLIBRARY_FILEREADER_H

#ifndef TESTLIBRARY_STANDARDREADERS_H
#define TESTLIBRARY_STANDARDREADERS_H

#ifdef PART_OF_FILE_STD_READERS
#elif defined(FILE_STD_READERS)
#else
#endif

namespace tl
{
    struct StandardReaders
    {
#ifdef PART_OF_FILE_STD_READERS
        static PartOfFileReader input;
        static PartOfFileReader output;
        static PartOfFileReader ans;
#elif defined(FILE_STD_READERS)
        static FileReader input;
        static FileReader output;
        static FileReader ans;
#else
        static PartOfStdinReader input;
        static PartOfStdinReader output;
        static PartOfStdinReader ans;
#endif
    };
}

#endif //TESTLIBRARY_STANDARDREADERS_H

#ifndef TESTLIBRARY_COMPARES_H
#define TESTLIBRARY_COMPARES_H

#include <cmath>

namespace tl
{
    class Compares
    {
    public:
        [[nodiscard]] static bool doubleCmp(double expected,
                                            double result,
                                            double maxDblErr);
    };
}

#endif //TESTLIBRARY_COMPARES_H

#ifndef TESTLIBRARY_STRINGTOOLS_H
#define TESTLIBRARY_STRINGTOOLS_H

#include <cstring>

#include <string>

namespace tl
{
    class StringTools
    {
    public:
        static std::string partOfStr(std::string str);

        static char* withEnglishEnding(std::uint8_t num);

        static char* withEnglishEnding(std::uint16_t num);

        static char* withEnglishEnding(std::uint32_t num);

        static char* withEnglishEnding(std::uint64_t num);

        static char* withEnglishEnding(std::int8_t num);

        static char* withEnglishEnding(std::int16_t num);

        static char* withEnglishEnding(std::int32_t num);

        static char* withEnglishEnding(std::int64_t num);

    private:
        template<typename Int>
        static char* withEnglishEnding(Int num,
                                       const char* format,
                                       Int beginSize = 0);
    };
}

#endif //TESTLIBRARY_STRINGTOOLS_H

#ifndef WITHOUT_BACK_COMP
#ifndef TESTLIBRARY_INSTREAM_H
#define TESTLIBRARY_INSTREAM_H


#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    class InStream {
    public:
        explicit InStream(tl::AbstractReader& reader);

        bool seekEof();

        void readWordTo(std::string& result);

        void readTokenTo(std::string& result);

        void readStringTo(std::string& result);

        std::string readWord();

        std::string readToken();

        std::string readString();

        int readInteger();

        int readInt();

        long long readLong();

        double readReal();

        double readDouble();

    private:
        tl::AbstractReader &mReader;
    };
#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L

#endif //TESTLIBRARY_INSTREAM_H

#ifndef TESTLIBRARY_TESTLIBGLOBALS_H
#define TESTLIBRARY_TESTLIBGLOBALS_H


#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    InStream inf(tl::StandardReaders::input);

    InStream ouf(tl::StandardReaders::output);

    InStream ans(tl::StandardReaders::ans);
#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L

#endif //TESTLIBRARY_TESTLIBGLOBALS_H

#ifndef TESTLIBRARY_TESTLIBFUNCS_H
#define TESTLIBRARY_TESTLIBFUNCS_H

#include <string>



#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    void setTestCase(int testCase);

    void unsetTestCase();

    [[noreturn]] static void __testlib_fail(const std::string& message);

    static bool __testlib_prelimIsNaN(double r);

    static std::string removeDoubleTrailingZeroes(std::string value);

    std::string format(const char* fmt, ...);

    std::string format(const std::string fmt, ...);

    static std::string __testlib_part(const std::string& s);

    static bool __testlib_isNaN(double r);

    static double __testlib_nan();

    static bool __testlib_isInfinite(double r);

    inline bool doubleCompare(double expected, double result,
                              double MAX_DOUBLE_ERROR);

    inline double doubleDelta(double expected, double result) noexcept;

    static void __testlib_set_binary(std::FILE* file);

    void prepareOpts(int argc, char* argv[]);


    void registerTestlibCmd(int argc, char* argv[]);

    void setName(const char* format, ...);

    enum TResult {
        _ok = 0,
        _wa = 1,
        _pe = 2,
        _fail = 3,
        _dirt = 4,
        _points = 5,
        _unexpected_eof = 8,
        _partially = 16
    };

    void quitf(TResult result, const char* format, ...);

    inline std::string englishEnding(int x);

    inline std::string compress(const std::string& s);

    static inline long long stringToLongLong(InStream& in, const char* buffer);

    static inline unsigned long long stringToUnsignedLongLong(InStream& in, const char* buffer);

    inline bool doubleCompare(double expected, double result, double MAX_DOUBLE_ERROR);

    std::string upperCase(std::string s);


    template<typename T>
    static inline T __testlib_abs(const T& x) {
        return x > 0 ? x : -x;
    }

    template<typename T>
    static inline T __testlib_min(const T& a, const T& b) {
        return a < b ? a : b;
    }

    template<typename T>
    static inline T __testlib_max(const T& a, const T& b) {
        return a > b ? a : b;
    }

    template<typename T>
    static std::string vtos(const T& t) {
        return std::to_string(t);
    }
#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L

#endif //TESTLIBRARY_TESTLIBFUNCS_H

#ifndef TESTLIBRARY_RANDOM_T_H
#define TESTLIBRARY_RANDOM_T_H

class pattern;

#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    class random_t
    {
    public:
    };
#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L

#endif //TESTLIBRARY_RANDOM_T_H

#ifndef TESTLIBRARY_PATTERN_H
#define TESTLIBRARY_PATTERN_H

#include <string>
#include <vector>


#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    class pattern {
    public:
        explicit pattern(std::string s);

        std::string next(random_t& rnd) const;

        bool matches(const std::string& s) const;

        std::string src() const;

    private:
        bool matches(const std::string& s, size_t pos) const;

        std::string s;
        std::vector<pattern> children;
        std::vector<char> chars;
        int from;
        int to;
    };
#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L

#endif //TESTLIBRARY_PATTERN_H

#endif

#ifndef WITHOUT_LOGS

namespace tl
{
    Logger::Logger(const char* funcName,
                   std::uint8_t funcNameSize) :
            mFuncName(funcName),
            mFuncNameSize(funcNameSize)
    {
        if (mFile == nullptr)
        {
#ifdef LOGS_TO_STDIN
            mFile = stdin;
#else
            mFile = std::fopen("../logs/logs.txt", "w");
#endif
        }
    }

    void
    Logger::funcStartLog(const char* format, ...)
    {
        for (std::uint8_t numTab = 0; numTab < mCountTabs; numTab++)
        {
            putc('\t', mFile);
        }

        write(mFuncName, mFuncNameSize);
        write(" has started", 12);

        if (format != nullptr)
        {
            write(" with args: ", 12);
            std::va_list ap;
            va_start(ap, format);
            std::vfprintf(mFile, format, ap);
            va_end(ap);
        }
        putc('\n', mFile);

        mCountTabs++;

#ifdef TIME_CHECK_IN_LOGS
#endif //TIME_CHECK_IN_LOGS
    }

    void
    Logger::funcFinishLog(const char* format, ...)
    {
        for (std::uint8_t numTab = 0; numTab < mCountTabs; numTab++)
        {
            putc('\t', mFile);
        }

        write(mFuncName, mFuncNameSize);
        write(" has finished", 13);

        if (format != nullptr)
        {
            write(" with return: ", 14);
            std::va_list ap;
            va_start(ap, format);
            std::vfprintf(mFile, format, ap);
            va_end(ap);
        }
        putc('\n', mFile);

        mCountTabs--;

#ifdef TIME_CHECK_IN_LOGS
#endif //TIME_CHECK_IN_LOGS
    }

    void
    Logger::resultLog(const char* messageFormat, std::va_list& ap)
    {
        for (std::uint8_t numTab = 0; numTab < mCountTabs; numTab++)
        {
            putc('\t', mFile);
        }

        write("checker has finished with message ", 34);
        std::vfprintf(mFile, messageFormat, ap);
        putc('\n', mFile);
    }

    FILE* Logger::mFile = nullptr;
    std::uint8_t Logger::mCountTabs = 0;

    void
    Logger::write(const char *message, std::size_t messageSize)
    {
        std::fwrite(static_cast<const void*>(message),
                    1, messageSize, mFile);
    }
}

#endif //!WITHOUT_LOGS

namespace tl
{
    void ResultWriter::vOKResultWr(const char* format,
                                   std::va_list& ap)
    {
        printMessage("ok ", format, ap);
    }

    void ResultWriter::vWAResultWr(const char* format,
                                   std::va_list& ap)
    {
        printMessage("wa ", format, ap);
    }

    void ResultWriter::vPEResultWr(const char* format,
                                   std::va_list& ap)
    {
        printMessage("pe ", format, ap);
    }

    void ResultWriter::OKResultWr(const char *format, ...)
    {
        std::va_list ap;
        va_start(ap, format);
        vOKResultWr(format, ap);
        va_end(ap);
    }

    void ResultWriter::WAResultWr(const char *format, ...)
    {
        std::va_list ap;
        va_start(ap, format);
        vWAResultWr(format, ap);
        va_end(ap);
    }

    void ResultWriter::PEResultWr(const char *format, ...)
    {
        std::va_list ap;
        va_start(ap, format);
        vPEResultWr(format, ap);
        va_end(ap);
    }

    void ResultWriter::printMessage(const char *result,
                                    const char *format,
                                    std::va_list& ap)
    {
        ::write(1, static_cast<const void*>(result), 3);

        std::vprintf(format, ap);

#ifndef WITHOUT_LOGS
        Logger::resultLog(format, ap);
#endif

        std::exit(0);
    }
}

#include "AbstractReader.hpp"

namespace tl
{
    void
    AbstractReader::changeMode()
    {
        FUNC_START_LOG(logger);

        mIgnoreWhitespaces = !mIgnoreWhitespaces;

        FUNC_FINISH_LOG(logger);
    }

    AbstractReader::~AbstractReader()
    {
        FUNC_START_LOG(logger);

        delete[] mBegin;

        FUNC_FINISH_LOG(logger);
    }

    bool
    AbstractReader::isOpen() const
    {
        FUNC_START_LOG(logger);

        BOOL_FUNC_RETURN_LOG(logger, result, mData != nullptr);
    }

    bool
    AbstractReader::isEndOfFile() const
    {
        FUNC_START_LOG(logger);

        BOOL_FUNC_RETURN_LOG(logger, result, *mData == '\000');
    }

    void
    AbstractReader::skipWhitespaces()
    {
        FUNC_START_LOG(logger);

        while (isWhitespace() && !isEndOfFile())
        {
            mData++;
        }

        FUNC_FINISH_LOG(logger);
    }

    void
    AbstractReader::skipChar()
    {
        FUNC_START_LOG(logger);

        if (!isEndOfFile())
        {
            mData++;
        }

        FUNC_FINISH_LOG(logger);
    }

    void
    AbstractReader::readAllFile(char*& fileStr)
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        std::strcpy(fileStr, mBegin);

        FUNC_FINISH_LOG(logger);
    }

    READ_RET_TYPE
    AbstractReader::readWhitespace(char& whitespace)
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected whitespace, but found end of file");
        }

        if (isNotWhitespace())
        {
            READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                            "expected whitespace, but found another symbol");
        }

        whitespace = *mData++;

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    READ_RET_TYPE
    AbstractReader::readWhitespaces(char*& whitespaces)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(
                logger, result,
                readAbstractStr(whitespaces, &AbstractReader::isWhitespace));
    }

    READ_RET_TYPE
    AbstractReader::readWhitespaces(std::string& whitespaces)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(
                logger, result,
                readAbstractStr(whitespaces, &AbstractReader::isWhitespace));
    }

    READ_RET_TYPE
    AbstractReader::readChar(char& c)
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected char, but found end of file");
        }

        c = *mData++;

        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }

        READ_POS_RESULT(logger, EXIT_SUCCESS);
    }

    READ_RET_TYPE
    AbstractReader::readInt8(std::int8_t& i)
    {
        FUNC_START_LOG(logger);


        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readUInt8(std::uint8_t& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readInt16(std::int16_t& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readUInt16(std::uint16_t& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readInt32(std::int32_t& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readUInt32(std::uint32_t& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readInt64(std::int64_t& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readUInt64(std::uint64_t& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readShort(short& s)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(s));
    }

    READ_RET_TYPE
    AbstractReader::readUShort(unsigned short& s)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(s));
    }

    READ_RET_TYPE
    AbstractReader::readInt(int& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readUInt(unsigned int& i)
    {
        FUNC_START_LOG(logger);

        READ_USE_INSERT_FUNC_RESULT(logger, result, readAbstractInt(i));
    }

    READ_RET_TYPE
    AbstractReader::readLong(long& l)
    {
        FUNC_START_LOG(logger);

        readAbstractInt(l);
    }

    READ_RET_TYPE
    AbstractReader::readULong(unsigned long& l)
    {
        FUNC_START_LOG(logger);

        readAbstractInt(l);
    }

    READ_RET_TYPE
    AbstractReader::readLongLong(long long& ll)
    {
        FUNC_START_LOG(logger);

        readAbstractInt(ll);
    }

    READ_RET_TYPE
    AbstractReader::readULongLong(unsigned long long& ll)
    {
        FUNC_START_LOG(logger);

        readAbstractInt(ll);
    }

    READ_RET_TYPE
    AbstractReader::readHugeInt(hugeIntPtr& i)
    {
        FUNC_START_LOG(logger);

        //TODO refactoring

        return readAbstractStr(i, &AbstractReader::isNotWhitespace,
                               [this]()
                               {
                                   return isNotDigit();
                               });
    }

    READ_RET_TYPE
    AbstractReader::readHugeInt(hugeInt& i)
    {
        FUNC_START_LOG(logger);
        //TODO refactoring

        return readAbstractStr(i, &AbstractReader::isNotWhitespace,
                               [this]()
                               {
                                   return isNotDigit();
                               });
    }

    READ_RET_TYPE
    AbstractReader::readFloat(float& num)
    {
        readAbstractReal(num);
    }

    READ_RET_TYPE
    AbstractReader::readDouble(double& num)
    {
        readAbstractReal(num);
    }

    READ_RET_TYPE
    AbstractReader::readBool(bool& b)
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected bool, but found end of file");
        }

        if((*mData != '0' && *mData != '1'))
        {
            READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                            "expected bool, but found another symbol");
        }

        b = static_cast<bool>(*mData++ - '0');

        if (isNotWhitespace() && !isEndOfFile())
        {
            mData--;

            READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                            "expected whitespace after bool");
        }

        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    READ_RET_TYPE
    AbstractReader::readStr(char* s, const std::size_t sSize)
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        TESTLIBRARY_NONNULL_ASSERT(s);

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected bool, but found end of file");
        }

        //TODO reactoring
        for (std::size_t pos(UINT64_C(0));
             pos < sSize; pos++)
        {
//            if (!readChar(s[pos]))
//            {
//                READ_NEG_RESULT(logger, READ_INCORRECT_SIZE,
//                                "to less symbols");
//            }
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    READ_RET_TYPE
    AbstractReader::readStr(char*& emptyS)
    {
        FUNC_START_LOG(logger);

        READ_CHECK_INSERT_FUNC_RESULT(
            logger,
            result,
            readAbstractStr(emptyS, &AbstractReader::isNotWhitespace)
        );
    }

    READ_RET_TYPE
    AbstractReader::readStr(std::string& s, const std::size_t sSize)
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger,
                            READ_EOF,
                            "expected string, but found end of file");
        }

        s.resize(sSize);

        char* begin = mData;
        for (char& sym : s)
        {
            if (isEndOfFile())
            {
                READ_NEG_RESULT(logger,
                                READ_EOF,
                                "Expected more characters");
            }

            sym = *mData++;
        }

        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    READ_RET_TYPE
    AbstractReader::readStr(std::string& s)
    {
        FUNC_START_LOG(logger);

        READ_CHECK_INSERT_FUNC_RESULT(
            logger,
            result,
            readAbstractStr(s, &AbstractReader::isNotWhitespace)
        );
    }

    READ_RET_TYPE
    AbstractReader::readLine(std::string& line)
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger,
                            READ_EOF,
                            "expected string, but found end of file");
        }

        line.clear();

        while (*mData != '\n' && !isEndOfFile())
        {
            line.push_back(*mData++);
        }
        
        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }
    }

    AbstractReader::AbstractReader(const bool ignoreWhitespaces) :
            mIgnoreWhitespaces(ignoreWhitespaces),
            mData(nullptr),
            mBegin(nullptr)
    {
        FUNC_START_LOG(logger, ignoreWhitespaces ? "true" : "false");

        FUNC_FINISH_LOG(logger);
    }

    bool
    AbstractReader::isNotWhitespace() const
    {
        FUNC_START_LOG(logger);

        BOOL_FUNC_RETURN_LOG(logger, result,
                             *mData != ' ' && *mData != '\n' && *mData != '\r');
    }

    bool
    AbstractReader::isWhitespace() const
    {
        FUNC_START_LOG(logger);

        BOOL_FUNC_RETURN_LOG(logger, result, !isNotWhitespace());
    }

    bool
    AbstractReader::isNotDigit()
    {
        FUNC_START_LOG(logger);

        BOOL_FUNC_RETURN_LOG(logger, result,
                             *mData < '0' || *mData > '9');
    }

    template<typename NumT,  typename SummandT,
             typename = std::enable_if_t<std::is_arithmetic_v<NumT>>>
    bool
    AbstractReader::isLessThanMin(const NumT num,
                                  const SummandT nextSummand) noexcept
    {
        FUNC_START_LOG(
            logger,
            (std::to_string(num) + ", " + std::to_string(nextSummand)).c_str()
        );

        BOOL_FUNC_RETURN_LOG(
            logger,
            result, 
            ((std::numeric_limits<NumT>::lowest() + nextSummand) / 10) > -num
        );
    }

    template<typename NumT,  typename SummandT,
             typename = std::enable_if_t<std::is_arithmetic_v<NumT>>>
    bool
    AbstractReader::isMoreThanMax(const NumT num,
                                  const SummandT nextSummand) noexcept
    {
        FUNC_START_LOG(
            logger,
            (std::to_string(num) + ", " + std::to_string(nextSummand)).c_str()
        );

        BOOL_FUNC_RETURN_LOG(
            logger,
            result,
            ((std::numeric_limits<NumT>::max() - nextSummand) / 10) < num
        );
    }

#define BUFF_SIZE UINT64_C(256)

    READ_RET_TYPE
    AbstractReader::readAbstractStr(char*& s,
                                    bool (AbstractReader::*continueCond)() const,
                                    const std::function<bool()>& exitCond)
    {
        //TODO refactoring
        FUNC_START_LOG(logger);

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected string, but found end of file");
        }

        if (!(this->*continueCond)())
        {
            READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                            "");
        }

        s = new char [BUFF_SIZE];

        std::size_t pos = 0;
        while ((this->*continueCond)() && !isEndOfFile())
        {
            if (exitCond())
            {
                s = static_cast<char*>(
                        realloc(static_cast<void*>(s),
                                pos + UINT64_C(1)));
                s[pos] = '\000';

                READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                                "");
            }

            s[pos++] = *mData++;
            if (pos % BUFF_SIZE == UINT64_C(0))
            {
                s = static_cast<char*>(
                        realloc(static_cast<void*>(s),
                                pos + BUFF_SIZE));
            }
        }

        s = static_cast<char*>(
                realloc(static_cast<void*>(s),
                        pos + UINT64_C(1)));
        s[pos] = '\000';

        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    READ_RET_TYPE
    AbstractReader::readAbstractStr(std::string& s,
                                    bool (AbstractReader::*continueCond)() const,
                                    const std::function<bool()>& exitCond)
    {
        //TODO refactoring
        FUNC_START_LOG(logger);

        s.clear();

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected string, but found end of file");
        }

        if (!(this->*continueCond)())
        {
            READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                            "");
        }

        while ((this->*continueCond)() && !isEndOfFile())
        {
            if (exitCond())
            {
                READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                                "");
            }

            s.push_back(*mData++);
        }

        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    template<typename IntT,
             typename = std::enable_if_t<std::is_integral_v<IntT>>>
    READ_RET_TYPE
    AbstractReader::readAbstractIntWithoutSign(
        IntT& num,
        bool(&checkOverflowFunc)(IntT, std::int8_t)
    ) noexcept
    {
        FUNC_START_LOG(logger, "%lld");

        num = 0;

        char* begin(mData);
        std::uint8_t nextDigit;
        while (isNotWhitespace() && !isEndOfFile())
        {
            nextDigit = *mData - '0';
            if (isNotDigit() || checkOverflowFunc(num, nextDigit))
            {
                mData = begin;

                READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                                "expected int, but found another type");
            }
            num = num * 10 + nextDigit;

            mData++;
        }

        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    template<typename IntT,
             typename = std::enable_if_t<std::is_integral_v<IntT>>>
    READ_RET_TYPE
    AbstractReader::readAbstractPositiveInt(IntT& num) noexcept
    {
        readAbstractIntWithoutSign(num, isMoreThanMax);
    }

    template<typename IntT,
             typename = std::enable_if_t<std::is_integral_v<IntT>>>
    READ_RET_TYPE
    AbstractReader::readAbstractNegativeInt(IntT& num) noexcept
    {
        readAbstractIntWithoutSign(num, isLessThanMin);
    }

    template<typename IntT,
             typename = std::enable_if_t<std::is_integral_v<IntT>>>
    READ_RET_TYPE
    AbstractReader::readAbstractInt(IntT& num) noexcept
    {
        readAbstractIntImpl(num, std::is_signed<IntT>());
    }

    template<typename IntT,
             typename = std::enable_if_t<std::is_signed_v<IntT>>>
    READ_RET_TYPE
    AbstractReader::readAbstractIntImpl(IntT& num, std::true_type) noexcept
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected int, but found end of file");
        }

        bool minus(false);
        if (*mData == '-')
        {
            minus = true;
            ++mData;
        }

        if (minus)
        {
            READ_CHECK_INSERT_FUNC_RESULT(logger,result,
                                          readAbstractNegativeInt(num));
        }
        else
        {
            READ_CHECK_INSERT_FUNC_RESULT(logger,result,
                                          readAbstractPositiveInt(num));
        }

        if (minus)
        {
            num *= -1;
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }

    template<typename IntT,
                 typename = std::enable_if_t<std::is_unsigned_v<IntT>>>
    inline READ_RET_TYPE
    AbstractReader::readAbstractIntImpl(IntT& num, std::false_type) noexcept
    {
        FUNC_START_LOG(logger);

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected int, but found end of file");
        }

        READ_CHECK_INSERT_FUNC_RESULT(logger,result,
                                      readAbstractNegativeInt(num));
    }

    template<typename Real>
    READ_RET_TYPE
    AbstractReader::readAbstractReal(Real& num) noexcept
    {
        FUNC_START_LOG(logger, "%lf, %lf");

        IS_NOT_OPEN_ASSERT;

        if (isEndOfFile())
        {
            READ_NEG_RESULT(logger, READ_EOF,
                            "expected real, but found end of file");
        }

        bool minus(false);
        if (*mData == '-')
        {
            minus = true;
            ++mData;
        }

        auto checkOverflowFunc(minus ? 
            isLessThanMin<Real, Real> : isMoreThanMax<Real, Real>);

        num = 0.F;

        char* begin(mData);
        Real nextDigit;
        while (*mData != '.' && isNotWhitespace()
               && !isEndOfFile())
        {
            nextDigit = *mData - '0';
            if (isNotDigit() || checkOverflowFunc(num, nextDigit))
            {
                mData = begin;

                READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                                "expected real");
            }
            num = num * 10.F + nextDigit;

            mData++;
        }

        if (isNotWhitespace() && !isEndOfFile())
        {
            if (*mData++ != '.')
            {
                mData = begin;

                READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                                "expected \'.\' or whitespace or end of file");
            }

            Real afterPoint = 0.F;
            Real countDigit = 0.F;

            while (isNotWhitespace() && !isEndOfFile())
            {
                nextDigit = *mData - '0';
                if (isNotDigit() || checkOverflowFunc(afterPoint, nextDigit))
                {
                    mData = begin;

                    READ_NEG_RESULT(logger, READ_TYPE_ERROR,
                                    "expected digit, but found another symbol");
                }
                afterPoint = afterPoint * 10.F + nextDigit;
                countDigit++;

                mData++;
            }

            afterPoint /= std::pow(10.F, countDigit);

            if (checkOverflowFunc(num, afterPoint))
            {
                mData = begin;

                READ_NEG_RESULT(logger, READ_TYPE_ERROR, "");
            }

            num += afterPoint;
        }

        if (minus)
        {
            num *= -1.F;
        }

        if (mIgnoreWhitespaces)
        {
            skipWhitespaces();
        }

        READ_POS_RESULT(logger, READ_SUCCESS);
    }
}

namespace tl
{
    AbstractPartOfFileReader::AbstractPartOfFileReader(const bool ignoreWhitespaces) :
            AbstractReader(ignoreWhitespaces)
    {

    }

    AbstractPartOfFileReader::AbstractPartOfFileReader(const int fd,
                                                       const bool ignoreWhitespaces) :
            AbstractReader(ignoreWhitespaces)
    {
        openPart(fd);
    }

    void
    AbstractPartOfFileReader::openPart(const int fd)
    {
        TESTLIBRARY_ASSERT(fd != -1, "file doesn't exist");
        TESTLIBRARY_ASSERT(fd != 1,
                           "PartOfFileReader doesn't work with stdout");
        TESTLIBRARY_ASSERT(fd != 2,
                           "PartOfFileReader doesn't work with stderr");

        std::size_t sizeOfPart;

if (sizeof(std::size_t) == 8)
{
        ::CORRECT_VER(read)(fd, static_cast<void*>(&sizeOfPart), 8);
}
else
{
        ::CORRECT_VER(read)(fd, static_cast<void*>(&sizeOfPart), 4);

        std::size_t lastFourBites;
        ::CORRECT_VER(read)(fd, static_cast<void*>(&lastFourBites), 4);
        TESTLIBRARY_ASSERT(lastFourBites == 0, "You can't read so long file in x86 system");
}

        mData = new char[sizeOfPart + 1];
        mData[sizeOfPart] = '\000';
        ::CORRECT_VER(read)(fd, static_cast<void*>(mData), sizeOfPart);

        mBegin = mData;
    }
}


namespace tl
{
    AbstractFileReader::AbstractFileReader(bool ignoreWhitespaces) :
            AbstractReader(ignoreWhitespaces)
    {

    }

    AbstractFileReader::AbstractFileReader(const int fd,
                                           const bool ignoreWhitespaces) :
            AbstractReader(ignoreWhitespaces)
    {
        open(fd);
    }

    void
    AbstractFileReader::open(const int fd)
    {
        TESTLIBRARY_ASSERT(fd != -1, "file doesn't exist");
        TESTLIBRARY_ASSERT(fd != 1, "FileReader doesn't work with stdout");
        TESTLIBRARY_ASSERT(fd != 2, "FileReader doesn't work with stderr");

#ifdef __GNUC__
        struct ::stat file{};
        ::fstat(fd, &file);
        const ::off_t fSize(file.st_size);
//#elif _MSC_VER
//      HANDLE hF = CreateFileA("F:\\TestLib\\TestLib\\test.exe", 0x00, 0x00, NULL,
//            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//      const DWORD fSize(GetFileSize(hF, NULL));
#else
        const long fSize(::CORRECT_VER(lseek)(fd, 0L, SEEK_END));
        ::CORRECT_VER(lseek)(fd, 0L, SEEK_SET);
#endif

        mData = new char[fSize + 1];
        mData[fSize] = '\000';

        ::CORRECT_VER(read)(fd, static_cast<void*>(mData), fSize);
        ::CORRECT_VER(close)(fd);
        mBegin = mData;
    }
}


namespace tl
{
    PartOfStdinReader::PartOfStdinReader(const bool ignoreWhitespaces) :
            AbstractPartOfFileReader(0, ignoreWhitespaces)
    {

    }
}

#ifdef PART_OF_FILE_READER_ADD

namespace tl
{
    int PartOfFileReader::mFd = -1;

    PartOfFileReader::PartOfFileReader(const bool ignoreWhitespaces) :
            AbstractPartOfFileReader(ignoreWhitespaces)
    {

    }

    PartOfFileReader::PartOfFileReader(const int fd,
                                       const bool ignoreWhitespaces) :
            AbstractPartOfFileReader(ignoreWhitespaces)
    {
        TESTLIBRARY_ASSERT(fd != 0,
                           "PartOfFileReader doesn't work with stdin");

        open(fd);
    }

    PartOfFileReader::PartOfFileReader(FILE*& file,
                                       const bool ignoreWhitespaces)
    {

    }

    PartOfFileReader::PartOfFileReader(const char* path,
                                       const bool ignoreWhitespaces) :
            AbstractPartOfFileReader(ignoreWhitespaces)
    {

        open(path);
    }

    PartOfFileReader::PartOfFileReader(const std::string& path,
                                       const bool ignoreWhitespaces) :
            PartOfFileReader(ignoreWhitespaces)
    {
        open(path);
    }

    void
    PartOfFileReader::open(const int fd)
    {
        PartOfFileReader::mFd = fd;

        openPart(fd);
    }

    void
    PartOfFileReader::open(FILE*& file)
    {
        TESTLIBRARY_NONNULL_ASSERT(file);

        open(::CORRECT_VER(fileno)(file));
    }

    void
    PartOfFileReader::open(const char* path)
    {
        if (path == nullptr)
        {
            open(mFd);
        }
        else
        {
            int fd(::CORRECT_VER(open)(path,
                                       CORRECT_VER(O_RDONLY)));
            PartOfFileReader::mFd = fd;

            open(fd);
        }
    }

    void
    PartOfFileReader::open(const std::string& path)
    {
        TESTLIBRARY_ASSERT(!path.empty(), "path is empty");

        open(path.c_str());
    }
}
#endif


tl::StdinReader::StdinReader(const bool ignoreWhitespaces) :
        AbstractFileReader(0, ignoreWhitespaces)
{

}


namespace tl {
    FileReader::FileReader(const bool ignoreWhitespaces) :
            AbstractFileReader(ignoreWhitespaces)
    {

    }

    FileReader::FileReader(const int fd, const bool ignoreWhitespaces) :
            AbstractFileReader(ignoreWhitespaces)
    {
        TESTLIBRARY_ASSERT(fd != 0,
                           "FileReader doesn't work with stdin");

        AbstractFileReader::open(fd);
    }

    FileReader::FileReader(FILE*& file, const bool ignoreWhitespaces) :
            AbstractFileReader(ignoreWhitespaces)
    {
        open(file);
    }

    FileReader::FileReader(const char *path,
                           const bool ignoreWhitespaces) :
            AbstractFileReader(ignoreWhitespaces)
    {
        open(path);
    }

    FileReader::FileReader(const std::string &path,
                           const bool ignoreWhitespaces) :
            FileReader(path.c_str(), ignoreWhitespaces)
    {
        open(path);
    }

    void
    FileReader::open(FILE*& file)
    {
        TESTLIBRARY_NONNULL_ASSERT(file);

        AbstractFileReader::open(::CORRECT_VER(fileno)(file));
    }

    void
    FileReader::open(const char* path)
    {
        TESTLIBRARY_NONNULL_ASSERT(path);

        AbstractFileReader::open(::CORRECT_VER(open)(path,
                             CORRECT_VER(O_RDONLY)));
    }

    void
    FileReader::open(const std::string& path)
    {
        TESTLIBRARY_ASSERT(!path.empty(), "path is empty");

        open(path.c_str());
    }
}


namespace tl
{
#ifdef PART_OF_FILE_STD_READERS
    PartOfFileReader StandardReaders::input(true);
    PartOfFileReader StandardReaders::output(true);
    PartOfFileReader StandardReaders::ans(true);
#elif defined(FILE_STD_READERS)
    FileReader StandardReaders::input(true);
    FileReader StandardReaders::output(true);
    FileReader StandardReaders::ans(true);
#else
    PartOfStdinReader StandardReaders::input(true);
    PartOfStdinReader StandardReaders::output(true);
    PartOfStdinReader StandardReaders::ans(true);
#endif
}


namespace tl
{
    bool
    Compares::doubleCmp(const double expected,
                        const double result,
                        const double maxDblErr)
    {
        return std::abs(result - expected) <= std::abs(maxDblErr) + 1E-15;
    }
}

#include <cmath>

namespace tl
{
    std::string
    StringTools::partOfStr(std::string str)
    {
        if (str.length() <= 64)
        {
            return str;
        }
        else
        {
            return str.substr(0, 30) + "..." +
                   str.substr(str.length() - 31, 31);
        }
    }

    char*
    StringTools::withEnglishEnding(std::uint8_t num)
    {
        return withEnglishEnding(num, "%u");
    }

    char*
    StringTools::withEnglishEnding(std::uint16_t num)
    {
        return withEnglishEnding(num, "%u");
    }

    char*
    StringTools::withEnglishEnding(std::uint32_t num)
    {
        return withEnglishEnding(num, "%u");
    }

    char*
    StringTools::withEnglishEnding(std::uint64_t num)
    {
#ifdef __GNUC__
        return withEnglishEnding(num, "%lu");
#elif defined(_MSC_VER)
        return withEnglishEnding(num, "%llu");
#endif
    }

    char*
    StringTools::withEnglishEnding(std::int8_t num)
    {
        return withEnglishEnding(num,
                                 "%i",
                                 num >= 0 ?
                                 static_cast<int8_t>(0) :
                                 static_cast<int8_t>(1));
    }

    char*
    StringTools::withEnglishEnding(std::int16_t num)
    {
        return withEnglishEnding(num,
                                 "%i",
                                 num >= 0 ?
                                 static_cast<int16_t>(0) :
                                 static_cast<int16_t>(1));
    }

    char*
    StringTools::withEnglishEnding(std::int32_t num)
    {
        return withEnglishEnding(num, "%i", num >= 0 ? 0 : 1);
    }

    char*
    StringTools::withEnglishEnding(std::int64_t num)
    {
#ifdef __GNUC__
        return withEnglishEnding(num, "%li", num >= 0L ? 0L : 1L);
#elif defined(_MSC_VER)
        return withEnglishEnding(num, "%lli", num >= 0LL ? 0LL : 1LL);
#endif
    }

    template<typename Int>
    char*
    StringTools::withEnglishEnding(const Int num,
                                   const char* format,
                                   const Int beginSize)
    {
        Int numSize(
                static_cast<Int>(std::log10(beginSize == 0 ? num : -num))
                + 2 + beginSize);
        Int resultSize(numSize + 2);
        char* result = new char[resultSize];
        result[resultSize - 1] = '\000';
        std::snprintf(result, numSize, format, num);

        const char* ending;
        if (num / 10 == 1)
        {
            ending = "th";
        }
        else
        {
            switch (num % 10) {
                case 1:
                    ending = "st";
                    break;
                case 2:
                    ending = "nd";
                    break;
                case 3:
                    ending = "rd";
                    break;
                default:
                    ending = "th";
                    break;
            }
        }

        std::snprintf(result + numSize - 1, 3, "%s", ending);

        return result;
    }
}

#ifndef WITHOUT_BACK_COMP

#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    InStream::InStream(tl::AbstractReader& reader) :
            mReader(reader)
    {

    }

    bool
    InStream::seekEof()
    {
        return mReader.isEndOfFile();
    }

    void
    InStream::readWordTo(std::string& result)
    {
        mReader.readStr(result);
    }

    void
    InStream::readTokenTo(std::string& result)
    {
        mReader.readStr(result);
    }

    void
    InStream::readStringTo(std::string& result)
    {
        mReader.readStr(result);
    }

    std::string
    InStream::readWord()
    {
        std::string result;
        mReader.readLine(result);

        return result;
    }

    std::string
    InStream::readToken()
    {
        return readWord();
    }

    std::string
    InStream::readString()
    {
        return readWord();
    }

    int
    InStream::readInteger()
    {
        int result;
        mReader.readInt(result);

        return result;
    }

    int
    InStream::readInt()
    {
        return readInteger();
    }

    long long
    InStream::readLong()
    {
        long long result;
        mReader.readLongLong(result);

        return result;
    }

    double
    InStream::readReal()
    {
        double result;
        mReader.readDouble(result);

        return result;
    }

    double
    InStream::readDouble()
    {
        return readReal();
    }

#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L


#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    void setTestCase(int testCase)
    {

    }

    void unsetTestCase()
    {

    }

    static void __testlib_fail(const std::string &message)
    {

    }

    static bool __testlib_prelimIsNaN(double r)
    {
        return false;
    }

    static std::string removeDoubleTrailingZeroes(std::string value)
    {
        return std::string();
    }

    std::string format(const char *fmt, ...)
    {
        static char buff[16777216];

        std::va_list ap;
        va_start(ap, fmt);
        std::vsnprintf(buff, 16777216, fmt, ap);
        va_end(ap);

        return buff;
    }

    std::string format(const std::string fmt, ...)
    {
        return std::string();
    }

    static std::string __testlib_part(const std::string &s)
    {
        return std::string();
    }

    static bool __testlib_isNaN(double r)
    {
        return false;
    }

    static double __testlib_nan()
    {
        return 0.;
    }

    static bool __testlib_isInfinite(double r)
    {
        return false;
    }

    inline bool doubleCompare(double expected, double result, double MAX_DOUBLE_ERROR)
    {
        return tl::Compares::doubleCmp(expected, result, MAX_DOUBLE_ERROR);
    }

    inline double doubleDelta(double expected, double result) noexcept
    {
        double absoluteDiffer(std::fabs(result - expected));

        if (std::fabs(expected) > 1E-9)
        {
            return std::min(absoluteDiffer,
                            std::fabs(absoluteDiffer / expected));
        }
        
        return absoluteDiffer;
    }

    void registerTestlibCmd(int argc, char *argv[])
    {
#ifdef FILE_STD_READERS
        tl::StandardReaders::input.open(argv[1]);
        tl::StandardReaders::output.open(argv[2]);
        tl::StandardReaders::ans.open(argv[3]);
#elif defined(PART_OF_FILE_STD_READERS)
        tl::StandardReaders::input.open(argv[1]);
        tl::StandardReaders::output.open(nullptr);
        tl::StandardReaders::ans.open(nullptr);
#endif
    }

    void setName(const char *format, ...)
    {

    }

    void quitf(TResult result, const char* format, ...)
    {
        std::va_list ap;
        va_start(ap, format);

        switch (result)
        {
            case TResult::_ok:
                tl::ResultWriter::vOKResultWr(format, ap);
                break;
            case TResult::_wa:
                tl::ResultWriter::vWAResultWr(format, ap);
                break;
            case TResult::_pe:
                tl::ResultWriter::vPEResultWr(format, ap);
        }

        va_end(ap);

        std::exit(0);
    }

    inline std::string englishEnding(int x)
    {
        if (x / 10 == 1)
        {
            return "th";
        }

        switch (x % 10)
        {
            case 1:
                return "st";
            case 2:
                return "nd";
            case 3:
                return "rd";
            default:
                return "th";
        }
    }

    inline std::string compress(const std::string &s)
    {
        return tl::StringTools::partOfStr(s);
    }

#define STRING_TO_LONG_LONG(type, limit)                                                         \
    do                                                                                           \
    {                                                                                            \
        type nextNum;                                                                            \
        while (*buffer != '\000')                                                                \
        {                                                                                        \
            nextNum = *buffer - '0';                                                             \
            if (*buffer < '0' || *buffer > '9'                                                   \
                || (((limit) - nextNum) / 10) < result)                                          \
            {                                                                                    \
                quitf(_wa,                                                                       \
                    ("Expected integer, but \"" + __testlib_part(buffer) + "\" found").c_str()); \
            }                                                                                    \
            result = result * 10 + nextNum;                                                      \
                                                                                                 \
            buffer++;                                                                            \
        }                                                                                        \
    } while(false)

    static inline long long stringToLongLong(InStream &in, const char *buffer)
    {
        if (buffer == nullptr)
        {
            quitf(_wa, "Expected integer, but nullptr found");
        }

        bool minus(false);
        if (*buffer == '-')
        {
            minus = true;
            buffer++;
        }

        long long result = 0;

        if (minus)
        {
            STRING_TO_LONG_LONG(long long, INT64_MAX);
            result *= -1;
        }
        else
        {
            STRING_TO_LONG_LONG(long long, INT64_MIN);
        }

        return result;
    }

    static inline unsigned long long stringToUnsignedLongLong(InStream &in, const char *buffer)
    {
        if (buffer == nullptr)
        {
            quitf(_wa, "Expected integer, but nullptr found");
        }

        unsigned long long result = 0;

        STRING_TO_LONG_LONG(unsigned long long, UINT64_MAX);

        return result;
    }

    std::string upperCase(std::string s)
    {
        std::string res;

#if __cplusplus >= 201703L
//        std::transform(s.begin(), s.end(),
//                       std::back_inserter(res), toupper);
//#else
        for (char& c : s)
        {
            c = std::toupper(c);
        }
#endif //__cplusplus >= 201703L

        return res;
    }
#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L


#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{
    pattern::pattern(std::string s)
    {

    }

    std::string
    pattern::next(random_t& rnd) const
    {
        return std::string();
    }

    bool
    pattern::matches(const std::string& s) const
    {
        return false;
    }

    std::string
    pattern::src() const
    {
        return std::string();
    }
#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L


#if __cplusplus >= 201703L
namespace tl::bc
#else
namespace tl { namespace bc
#endif //__cplusplus >= 201703L
{

#if __cplusplus >= 201703L
}
#else
}}
#endif //__cplusplus >= 201703L

#endif
using namespace tl::bc;