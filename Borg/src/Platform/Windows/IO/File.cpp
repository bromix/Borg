#include "Borg/IO/File.h"
#include "../Windows.h"

namespace Borg::IO
{
    void File::Move(const Borg::String &sourceFileName, const Borg::String &destFileName)
    {
        // TODO: handle exceptions.
        WideStringBuffer source = Encoding::Convert<WideStringBuffer>(sourceFileName);
        WideStringBuffer dest = Encoding::Convert<WideStringBuffer>(destFileName);
        ::MoveFileExW(source, dest, MOVEFILE_WRITE_THROUGH);
    }
}