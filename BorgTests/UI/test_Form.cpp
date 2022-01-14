#include "Borg/UI/Form.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(UIForm, DebugTest)
{
    Ref<UI::IForm> form = CreateRef<UI::Form>();
    form->SetOpacity(0.5);
    form->SetFormBorderStyle(UI::FormBorderStyle::None);
    form->SetText("Form1");
    form->SetBackColor(Drawing::Color::Fuchsia);
    form->ShowDialog();
}
