#include "Borg/UI/CustomControl.h"
#include "CreateParams.h"
#include "ControlImpl.h"

namespace Borg::UI
{
    CustomControl::~CustomControl() {}

    CustomControl::CustomControl(const String &className) : UI::Control()
    {
    }

    CustomControl::CustomControl(const Ref<UI::IControl> &parent, const String &className) : UI::Control(parent)
    {
        //UI::Handle hParent = UI::Handle::GetSafeFrom(parent);
        UI::Handle hParent = UI::Handle::GetSafeFrom(this->GetParent());

        Windows::CreateParams cp;
        cp.ClassName = className;
        cp.ClassStyle = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
        cp.ExStyle = WS_EX_LEFT;
        cp.X = 0;
        cp.Y = 0;
        cp.Height = 100;
        cp.Width = 100;
        cp.Style =WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
        cp.Parent = hParent;
        
        m_Impl->CreateHandle(cp);
    }
}