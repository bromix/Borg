#include "Borg/Uri.h"

namespace Borg
{
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
}