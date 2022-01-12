#include "Borg/UI/Handle.h"
#include <utility>

namespace Borg::UI
{
    Handle::Handle(Handle::Type nativeHandle) : m_Handle(nativeHandle) {}

    Handle::Handle(const Handle &handle) : m_Handle(handle.m_Handle) {}

    Handle::Handle(Handle &&handle)
    {
        std::swap(m_Handle, handle.m_Handle);
    }

    Handle &Handle::operator=(Handle::Type nativeHandle)
    {
        m_Handle = nativeHandle;
        return *this;
    }

    Handle &Handle::operator=(const Handle & handle)
    {
        m_Handle = handle.m_Handle;
        return *this;
    }

    Handle &Handle::operator=(Handle && handle)
    {
        std::swap(m_Handle, handle.m_Handle);
        return *this;
    }

    Handle::Type Handle::Get() const
    {
        return m_Handle;
    }

    Handle::operator Handle::Type() const
    {
        return m_Handle;
    }
}