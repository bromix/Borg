#include "Windows.h"
#include "Borg/Encoding.h"
#include "Borg/RefCast.h"
#include "Borg/CharBuffer.h"

namespace Borg
{
    template <>
    static CharBuffer Encoding::ConvertTo(const WideCharBuffer &input)
    {
        if (input.IsNull())
            return nullptr;

        if (input.IsEmpty())
            return L"";

        if (input.Length() > static_cast<size_t>((std::numeric_limits<int>::max)()))
        {
            throw std::overflow_error(
                "Input string too long: size_t-length doesn't fit into int.");
        }

        // constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;
        const int utf16Length = static_cast<int>(input.Length());
        const int utf8Length = ::WideCharToMultiByte(
            CP_UTF8,
            0,
            input,
            utf16Length,
            nullptr,
            0,
            nullptr,
            nullptr);

        if (utf8Length == 0)
        {
            // Conversion error: capture error code and throw
            const DWORD error = ::GetLastError();
            // throw Utf8ConversionException(
            //     "Cannot get result string length when converting "
            //     "from UTF-8 to UTF-16 (MultiByteToWideChar failed).",
            //     error);
        }

        CharBuffer utf8(utf8Length);

        int result = ::WideCharToMultiByte(
            CP_UTF8,     // Source string is in UTF-8
            0,           // Conversion flags
            input,       // Source UTF-8 string pointer
            utf16Length, // Length of source UTF-8 string, in chars
            utf8,        // Pointer to destination buffer
            utf8Length,  // Size of destination buffer, in wchar_ts
            nullptr,
            nullptr);

        if (result == 0)
        {
            // Conversion error: capture error code and throw
            const DWORD error = ::GetLastError();
            // throw Utf8ConversionException(
            //     "Cannot convert from UTF-8 to UTF-16 "
            //     "(MultiByteToWideChar failed).",
            //     error);
        }

        return utf8;
    }

    template <>
    static WideCharBuffer Encoding::ConvertTo(const CharBuffer &input)
    {
        if (input.IsNull())
            return nullptr;

        if (input.IsEmpty())
            return L"";

        if (input.Length() > static_cast<size_t>((std::numeric_limits<int>::max)()))
        {
            // FIXME: use proper Exception.
            throw std::overflow_error(
                "Input string too long: size_t-length doesn't fit into int.");
        }

        constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;
        const int utf8Length = static_cast<int>(input.Length());
        const int utf16Length = ::MultiByteToWideChar(
            CP_UTF8,    // Source string is in UTF-8
            kFlags,     // Conversion flags
            input,      // Source UTF-8 string pointer
            utf8Length, // Length of the source UTF-8 string, in chars
            nullptr,    // Unused - no conversion done in this step
            0           // Request size of destination buffer, in wchar_ts
        );

        if (utf16Length == 0)
        {
            // Conversion error: capture error code and throw
            const DWORD error = ::GetLastError();
            // throw Utf8ConversionException(
            //     "Cannot get result string length when converting "
            //     "from UTF-8 to UTF-16 (MultiByteToWideChar failed).",
            //     error);
        }

        WideCharBuffer utf16(utf16Length);

        int result = ::MultiByteToWideChar(
            CP_UTF8,    // Source string is in UTF-8
            kFlags,     // Conversion flags
            input,      // Source UTF-8 string pointer
            utf8Length, // Length of source UTF-8 string, in chars
            utf16,      // Pointer to destination buffer
            utf16Length // Size of destination buffer, in wchar_ts
        );

        if (result == 0)
        {
            // Conversion error: capture error code and throw
            const DWORD error = ::GetLastError();
            // throw Utf8ConversionException(
            //     "Cannot convert from UTF-8 to UTF-16 "
            //     "(MultiByteToWideChar failed).",
            //     error);
        }

        return utf16;
    }
}