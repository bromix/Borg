#include "Borg/UI/IForm.h"
#include "Win32Form.h"

namespace Borg::UI
{
    Ref<UI::IForm> IForm::CreateFrom(const UI::Handle& handle)
    {
        if(!handle)
            return nullptr;
        return CreateRef<UI::Win32Form>(handle);
    }
}