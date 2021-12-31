#include "Borg/Uri.h"

namespace Borg
{
    Uri::Uri()
    {
    }

    String Uri::Scheme() const
    {
        return m_Scheme;
    }

    String Uri::Host() const
    {
        return m_Host;
    }

    int Uri::Port() const
    {
        return m_Port;
    }

    String Uri::Path() const
    {
        return m_Path;
    }

    String Uri::Query() const
    {
        return m_Query;
    }

    bool Uri::IsScheme(const String &scheme) const
    {
        return scheme.ToLower() == m_Scheme;
    }

    String Uri::OriginalString() const
    {
        return m_OriginalString;
    }

    String Uri::ToString() const
    {
        // FIXME: We should use a StringBuilder

        String result = m_Scheme + "://";

        if(m_Host)
            result = result + m_Host;

        if (m_Path)
            result = result + m_Path;

        if (m_Query)
            result = result + m_Query;

        return result;
    }

    Uri::operator bool() const
    {
        return !m_OriginalString.IsNullOrEmpty();
    }
}