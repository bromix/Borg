#pragma once

#include "IForm.h"
#include "Control.h"

namespace Borg::UI
{
	class Form : public Control, public IForm
	{
	public:
		~Form() override;

		Form();

		explicit Form(const Ref<UI::IForm>& owner);

		Ref<IForm> GetOwner() const override;

		void SetOpacity(double opacity) override;

		double GetOpacity() const override;

		void SetFormBorderStyle(FormBorderStyle style) override;

		UI::FormBorderStyle GetFormBorderStyle() const override;

		void CenterToParent() override;

		void CenterToScreen() override;

		void SetShowInTaskbar(bool show) override;

		bool GetShowInTaskbar() const override;

		void Close() override;

		void Show() override;

		UI::DialogResult ShowDialog() override;

		void SetDialogResult(UI::DialogResult dialogResult) override;

		UI::DialogResult GetDialogResult() const override;

#ifdef _WIN32

		void DragMove() override;

#endif

		static Ref<UI::IForm> CreateFrom(const UI::Handle& handle);

	protected:
		UI::DialogResult m_DialogResult{ DialogResult::None };

		void onClosed(const UI::FormClosedEventArgs& e) override;

		void onMessage(UI::Message& message) override;
	};
}