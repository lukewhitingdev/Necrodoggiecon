#pragma once
#include "CSpriteComponent.h"

enum class TextJustification
{
	Right, Center, Left
};

class CTextRenderComponent : public CComponent
{
	std::string text = "";
	std::string font = "Resources\\font.dds";
	std::vector<CSpriteComponent*> sprites;
	XMUINT2 characterSize = { 7,7 };
	unsigned short reserveSpriteCount = 16;
	unsigned short usedSpriteCount = 0;
	TextJustification justification = TextJustification::Center;
public:
	unsigned short spriteSheetWidth = 16;

	HRESULT SetFont(std::string filePath);
	void SetText(std::string newText);

	//Sets the minimum amount of sprites to be loaded in memory at any time.
	//Lower values will use less memory but will require extra sprites to be created if number of characters to display exceeds the reserve.
	void SetReserveCount(unsigned short newReserveCount);

	//Sets how the text will justified to the center of the component.
	//Just look at justification in MS Word.
	void SetTextJustification(TextJustification newJustification);

	CTextRenderComponent();
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override;
	virtual ~CTextRenderComponent();
};

