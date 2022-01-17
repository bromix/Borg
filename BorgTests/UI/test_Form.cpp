#include "Borg/UI/Form.h"
#include "Borg/UI/CustomControl.h"
#include <gtest/gtest.h>

using namespace Borg;

class DeriveForm : public UI::Form
{
public:
protected:
    void onSizeChanged(EventArgs e) override
    {
        UI::Form::onSizeChanged(e);
    }

    void initialize(const Ref<UI::IForm>& thisForm) override
    {
        // auto control = CreateRef<UI::CustomControl>(shared_from_this(), "Button");
        // control->SetBackColor(Drawing::Color::Red);
        // control->SetLocation({0, 0});
        // control->SetSize({100, 100});
        // control->SetVisible(true);
        UI::Form::initialize(thisForm);
    }
};

TEST(UIForm, DebugTest)
{
    Ref<UI::IForm> form = CreateRef<DeriveForm>();
    auto style = form->GetFormBorderStyle();
    form->SetOpacity(0.5);
    // form->SetFormBorderStyle(UI::FormBorderStyle::None);
    style = form->GetFormBorderStyle();
    form->SetText("Form1");
    form->SetBackColor(Drawing::Color::Fuchsia);
    form->ShowDialog();
}
