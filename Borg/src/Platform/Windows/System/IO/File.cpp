#include "Borg/System/IO/File.h"
#include "../../Windows.h"

namespace Borg::System::IO
{
    void File::Move(const Borg::String &sourceFileName, const Borg::String &destFileName)
    {
        // TODO: handle exceptions.
        WideCharBuffer source = Encoding::Convert<WideCharBuffer>(sourceFileName);
        WideCharBuffer dest = Encoding::Convert<WideCharBuffer>(destFileName);
        ::MoveFileExW(source, dest, MOVEFILE_WRITE_THROUGH);
    }
}