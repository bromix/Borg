#include "Borg/Environment.h"
#include "Borg/Exception.h"
#include "Windows.h"
#include <map>

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

        if (FAILED(hr))
        {
            // TODO: provide Exception class for failed HRs and throw.
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