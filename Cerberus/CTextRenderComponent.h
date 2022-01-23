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
	XMFLOAT2 anchor = { 0.5,0.5 };
	XMFLOAT2 lastResolution = { 0,0 };
public:
	unsigned short spriteSheetWidth = 16;
	TextJustification justification = TextJustification::Center;

	HRESULT SetFont(std::string filePath);
	void SetText(std::string newText);
	void SetReserveCount(unsigned short newReserveCount);

	//Sets the region of the screen a UI element will be "anchored" to.
	//{0,0} - top left, {1,1} - bottom right.
	//Used for making UI elements stick to the edge of the screen when the window is resized
	void SetAnchor(XMFLOAT2 newAnchor) { anchor = newAnchor; updateTransform = true; }

	const XMFLOAT2& GetAnchor() const { return anchor; }


	CTextRenderComponent();
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override;
	virtual ~CTextRenderComponent();
	virtual XMFLOAT4X4 GetTransform() override;
};

