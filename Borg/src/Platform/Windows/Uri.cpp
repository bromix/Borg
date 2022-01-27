#include "Borg/Uri.h"
#include "Borg/Exception.h"
#include "Borg/Encoding.h"
#include "Windows.h"

namespace Borg
{
    Uri::Uri(const String &uri)
    {
        if (!uri)
            throw ArgumentNullException("uri");

        m_OriginalString = uri;

        // TODO: UriFormatException
        // See: https://docs.microsoft.com/en-us/dotnet/api/system.uri.-ctor?view=net-6.0#System_Uri__ctor_System_String_

        URL_COMPONENTSW url_components{};
        url_components.dwStructSize = sizeof(URL_COMPONENTSW);
        url_components.dwExtraInfoLength = -1;
        url_components.dwHostNameLength = -1;
        url_components.dwPasswordLength = -1;
        url_components.dwSchemeLength = -1;
        url_components.dwUrlPathLength = -1;
        url_components.dwUserNameLength = -1;

        WideStringBuffer buffer = Encoding::Convert<WideStringBuffer>(uri);
        if (!InternetCrackUrlW(buffer, buffer.Length(), 0, &url_components))
        {
            // FIXME: process GetLastError();
        }

        if (url_components.lpszScheme)
            m_Scheme = String(url_components.lpszScheme, url_components.dwSchemeLength).ToLower();

        if (url_components.lpszHostName)
            m_Host = String(url_components.lpszHostName, url_components.dwHostNameLength).ToLower();

        m_Port = url_components.nPort >= 0 ? url_components.nPort : 0;

        if (url_components.lpszUrlPath)
            m_Path = String(url_components.lpszUrlPath, url_components.dwUrlPathLength);

        if (url_components.lpszExtraInfo)
            m_Query = String(url_components.lpszExtraInfo, url_components.dwExtraInfoLength);
    }
}