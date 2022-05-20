#pragma once
#include "Cerberus/Core/UI/CWidget.h"
class CWidget_Text : public CWidget
{
public:
	virtual void SetWidgetTransform(Vector2 Position, Vector2 Anchor, int ZOrder);

	virtual void SetVisibility(bool IsVisible);

	class CTextRenderComponent* GetText() { return textRenderer; }


protected: 

	class CTextRenderComponent* textRenderer = nullptr;
};

