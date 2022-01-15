#include "Borg/UI/Form.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(UIForm, DebugTest)
{
    Ref<UI::IForm> form = CreateRef<UI::Form>();
    auto style = form->GetFormBorderStyle();
    form->SetOpacity(0.5);
    //form->SetFormBorderStyle(UI::FormBorderStyle::None);
    style = form->GetFormBorderStyle();
    form->SetText("Form1");
    form->SetBackColor(Drawing::Color::Fuchsia);
    form->ShowDialog();
}
