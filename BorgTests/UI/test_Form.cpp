#include "Borg/UI/Form.h"
#include <gtest/gtest.h>

using namespace Borg;

TEST(UIForm, DebugTest)
{
    Ref<UI::IForm> form = CreateRef<UI::Form>();
    form->SetBackColor(Color::Lime);
    form->ShowDialog();
}
