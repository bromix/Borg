#include "Borg/UI/CustomControl.h"
#include "ClassFactory.h"

namespace Borg::UI
{
    CustomControl::CustomControl(const WeakRef<UI::IControl> &parent, const String &className) : UI::Control(parent)
    {
        UI::Handle hParent = UI::Handle::GetSafeFrom(m_InternalParent.lock());

        WideCharBuffer clsName = Encoding::Convert<WideCharBuffer>(className);

        CREATESTRUCTW cs{0};
        cs.lpszClass = clsName;
        cs.style = WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        cs.dwExStyle = WS_EX_LEFT;
        cs.hwndParent = hParent;
        cs.x = 50;
        cs.y = 50;
        cs.cx = 100;
        cs.cy = 100;

        auto classStyle = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        m_Handle = ClassFactory::Create(cs, classStyle, [this](const UI::Message &message)
                                        { return this->onMessage(message); });
    }
}