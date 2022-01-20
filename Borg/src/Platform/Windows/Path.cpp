#include "Borg/Path.h"
#include "Windows.h"

namespace Borg
{
    Borg::String Path::GetTempPath()
    {
        WideCharBuffer buffer(MAX_PATH);
        DWORD size = ::GetTempPathW(MAX_PATH, buffer);
        return String(buffer, size);
    }

    Borg::String Path::GetTempFileName()
    {
        WideCharBuffer tempPath = Encoding::Convert<WideCharBuffer>(GetTempPath());
        WideCharBuffer buffer(MAX_PATH - 14);
        UINT size = ::GetTempFileNameW(tempPath, L"tmp", 0, buffer);
        return String(buffer, size);
    }
}