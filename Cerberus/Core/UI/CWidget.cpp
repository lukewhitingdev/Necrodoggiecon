#include "Cerberus/Core/UI/CWidget.h"

CWidget::CWidget()
{
	SetShouldUpdate(false);
	parentWidget = nullptr;

}




void CWidget::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{
}

void CWidget::SetVisibility(bool IsVisible)
{
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
	}
	
}

void CWidget::AddChild(CWidget* NewChild)
{
	ChildWidgets.push_back(NewChild);
	NewChild->parentWidget = this;
}

void CWidget::RemoveAllChildren()
{
	for (int i = 0; i < GetChildren().size(); i++)
	{
		if (GetChildren()[i] != nullptr)
		{
			GetChildren()[i]->RemoveAllChildren();
		}
	}
	Engine::DestroyEntity(this);
}
