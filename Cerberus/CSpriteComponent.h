#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CTexture.h"
#include "CMaterial.h"

//A component for loading and displaying a 2D texture in world space as part of CEntity
class CSpriteComponent : public CComponent
{
	CMesh* mesh = nullptr;
	CTexture* texture = nullptr;
	CMaterial* material = nullptr;

	XMUINT2 renderRect;
	XMFLOAT2 textureOffset = { 0,0 };
	XMUINT2 spriteSize;
public:
	//Used to resize the portion of the sprite you want to display
	//Use to set the size of a selection of a sprite sheet
	void SetRenderRect(XMUINT2 newSize);

	//The offset in pixels of where the sprite should start rendering in the texture
	//Use this for selecting a section of a sprite sheet
	//By default set to 0,0
	void SetTextureOffset(XMFLOAT2 newOffset);

	//The size of the ingame sprite in pixels
	//Set automatically on texture load
	void SetSpriteSize(XMUINT2 newSize) { spriteSize = newSize; };

	XMUINT2 GetRenderRect() { return renderRect; };
	XMFLOAT2 GetTextureOffset() { return textureOffset; };
	XMUINT2 GetSpriteSize() { return spriteSize; };

	CSpriteComponent();
	HRESULT LoadTexture(std::string filePath);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context) override;
	virtual ~CSpriteComponent();
	virtual XMFLOAT4X4 GetTransform() override;
};
