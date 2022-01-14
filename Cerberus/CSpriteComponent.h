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
public:
	//size of the render rectangle on screen, set automatically when texture is loaded
	//set yourself if you want to do spritesheets/ animation
	void SetRenderRect(XMUINT2 newSize);
	XMUINT2 GetRenderRect();

	void SetTextureOffset(XMFLOAT2 newOffset);
	XMFLOAT2 GetTextureOffset();

	XMUINT2 spriteSize;

	CSpriteComponent();
	HRESULT LoadTexture(std::string filePath);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context) override;
	virtual ~CSpriteComponent();
	virtual XMFLOAT4X4 GetTransform() override;
};
