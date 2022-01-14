#include "Borg/UI/Form.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(UIForm, DebugTest)
{
    Ref<UI::IForm> form = CreateRef<UI::Form>();
    form->SetText("Form1");
    //form->SetFormBorderStyle(UI::FormBorderStyle::None);
    form->SetBackColor(Drawing::Color::Lime);
    form->ShowDialog();
}
