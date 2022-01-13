#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CTexture.h"

//A component for loading and displaying a 2D texture in world space as part of CEntity
class CSpriteComponent : public CComponent
{
	CMesh* mesh = nullptr;
	CTexture* texture = nullptr;
	bool textureLoaded = false;

	XMUINT2 renderRect;
public:
	//size of the render rectangle on screen, set automatically when texture is loaded
	//set yourself if you want to do spritesheets/ animation
	void SetRenderRect(XMUINT2 newSize);
	XMUINT2 GetRenderRect();

	XMUINT2 spriteSize;

	CSpriteComponent();
	HRESULT LoadTexture(const wchar_t* filePath);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context) override;
	virtual ~CSpriteComponent();
	virtual XMFLOAT4X4 GetTransform() override;
};
