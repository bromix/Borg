#include "Borg/Environment.h"
#include "Windows.h"
#include <map>

namespace Borg
{
    String Environment::GetFolderPath(Environment::SpecialFolder specialFolder)
    {
        static std::map<Environment::SpecialFolder, REFKNOWNFOLDERID> folderIdMapping = {
            {SpecialFolder::LocalApplicationData, FOLDERID_LocalAppData},
            {SpecialFolder::ApplicationData, FOLDERID_RoamingAppData},
        };

        auto folderId = folderIdMapping.find(specialFolder);
        if (folderId == folderIdMapping.end())
        {
            // FIXME: throw ArgumentException
        }

        PWSTR buffer = nullptr;
        auto hr = SHGetKnownFolderPath(
            folderId->second,
            KF_FLAG_DEFAULT,
            nullptr,
            &buffer);

        if (FAILED(hr))
        {
            // FIXME: throw exception
        }

        // Create copy of the buffer.
        String result(buffer);

        /*
        We've to free the buffer.
        https://docs.microsoft.com/en-us/windows/win32/api/shlobj_core/nf-shlobj_core-shgetknownfolderpath
        */
        CoTaskMemFree(buffer);

        return result;
    }
}