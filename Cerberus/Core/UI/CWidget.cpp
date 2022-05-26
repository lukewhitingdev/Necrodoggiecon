#include "Cerberus/Core/UI/CWidget.h"
/*****************************************************************//**
 * \file   CWidget.cpp
 * \brief  Base class for all UI widgets. Handles parenting operations
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
CWidget::CWidget()
{
	SetIsUI(true);
	SetShouldUpdate(false);
	parentWidget = nullptr;

}



/**
 * Sets the widgets transform, this is overriden by child classes.
 * 
 * \param Position Sets position on screen
 * \param Anchor Sets screen anchor
 * \param ZOrder Sets the Z-Order
 */
void CWidget::SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder)
{

}

/**
 * Sets the visibility of the current widget and all child components.
 * This function is overridden in child classes.
 * 
 * \param IsVisible Should the widget render
 */
void CWidget::SetVisibility(bool IsVisible)
{
	for (int i = 0; i < GetChildren().size(); i++)
	{
		GetChildren()[i]->SetVisibility(IsVisible);
		
	}
	
}

/**
 * Adds a widget to this object.
 * 
 * \param NewChild The new child object.
 */
void CWidget::AddChild(CWidget* NewChild)
{
	childWidgets.push_back(NewChild);
	NewChild->parentWidget = this;
}

/**
 * Removes all children fromt his object and destroys them.
 * 
 */
void CWidget::RemoveAllChildren()
{
	for (int i = 0; i < GetChildren().size(); i++)
	{
		if (GetChildren()[i] != nullptr)
		{
			GetChildren()[i]->RemoveAllChildren();
		}
	}
	//Engine::DestroyEntity(this);
}

void CWidget::UpdateWidgetOrigin(Vector3 Pos)
{
	SetPosition(Pos.x, Pos.y, GetPosition().z);
	for (int i = 0; i < GetChildren().size(); i++)
	{
		if (GetChildren()[i] != nullptr)
		{
			GetChildren()[i]->UpdateWidgetOrigin(Pos);
		}
	}
}

