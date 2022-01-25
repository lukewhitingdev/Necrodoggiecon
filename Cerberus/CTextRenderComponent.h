#pragma once
#include "CSpriteComponent.h"

enum class TextJustification
{
	Right, Center, Left
};

class CTextRenderComponent : public CComponent
{
	std::string text = "";
	std::string font = "Resources\\font.png";
	std::vector<CSpriteComponent*> sprites;
	XMUINT2 characterSize = { 7,7 };
	XMUINT2 characterDrawSize = { 14,14 };
	unsigned short reserveSpriteCount = 16;
	unsigned short usedSpriteCount = 0;
	TextJustification justification = TextJustification::Center;
	unsigned short spriteSheetColumns = 16;

public:
	HRESULT SetFont(std::string filePath);
	void SetText(std::string newText);

	//Sets the minimum amount of sprites to be loaded in memory at any time.
	//Lower values will use less memory but will require extra sprites to be created if number of characters to display exceeds the reserve.
	void SetReserveCount(unsigned short newReserveCount);

	//Sets how the text will justified to the center of the component.
	//Just look at justification in MS Word.
	void SetJustification(TextJustification newJustification);

	//Sets how big in pixels the characters are from the sprite sheet
	//Simular to SetRenderRect of CSpriteComponent
	void SetCharacterSize(XMUINT2 newSize);

	//Set the size of a character when drawn in pixels
	void SetCharacterDrawSize(XMUINT2 newSize);

	//Set how many columns are in the font sprite sheet.
	//If 16 characters across, put 16
	void SetSpriteSheetColumnsCount(unsigned short newColumnsCount);

	const std::string& GetText() const { return text; };
	const unsigned short& GetReserveCount() const { return reserveSpriteCount; };
	const XMUINT2& GetCharacterSize() const { return characterSize; };
	const XMUINT2& GetCharacterDrawSize() const { return characterDrawSize; };
	const unsigned short& SetSpriteSheetColumnsCount() const { return spriteSheetColumns; };

	CTextRenderComponent();
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override;
	virtual ~CTextRenderComponent();
};

