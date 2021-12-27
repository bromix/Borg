#include "Borg/Environment.h"
#include "Borg/Exception.h"
#include "Borg/MemoryBlock.h"
#include "Windows.h"
#include <map>
#include <array>

namespace Borg
{
    String Environment::GetFolderPath(Environment::SpecialFolder folder)
    {
        static std::map<Environment::SpecialFolder, REFKNOWNFOLDERID> folderIdMapping = {
            {SpecialFolder::LocalApplicationData, FOLDERID_LocalAppData},
            {SpecialFolder::ApplicationData, FOLDERID_RoamingAppData},
        };

        auto folderId = folderIdMapping.find(folder);
        if (folderId == folderIdMapping.end())
            throw ArgumentException("folder is not a member of Environment.SpecialFolder.", "folder");

        PWSTR buffer = nullptr;
        auto hr = SHGetKnownFolderPath(
            folderId->second,
            KF_FLAG_DEFAULT,
            nullptr,
            &buffer);

        if (hr == E_INVALIDARG)
            throw ArgumentException("folder is not a member if KNOWNFOLDERID", "folder");

        if (FAILED(hr))
            throw Exception("SHGetKnownFolderPath failed");

        // Create copy of the buffer.
        String result(buffer);

        /*
        We've to free the buffer.
        https://docs.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
        */
        CoTaskMemFree(buffer);

        return result;
    }

    String Environment::MachineName()
    {
        MemoryBlock<wchar_t> buffer{MAX_COMPUTERNAME_LENGTH + 1};
        DWORD count = buffer.Count();
        if (GetComputerNameW(buffer.Data(), &count) == FALSE)
            throw InvalidOperationException("The name of this computer cannot be obtained.");
        return String(buffer.Data(), count - 1);
    }

    String Environment::UserName()
    {
        MemoryBlock<wchar_t> buffer{UNLEN + 1};
        DWORD count = buffer.Count();
        if (GetUserNameW(buffer.Data(), &count) == FALSE)
            throw InvalidOperationException("The name of this computer cannot be obtained.");
        return String(buffer.Data(), count - 1);
    }

    String Environment::NewLine()
    {
        static String newLine("\r\n");
        return newLine;
    }
}