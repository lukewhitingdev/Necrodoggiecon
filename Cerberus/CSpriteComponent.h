#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CTexture.h"

class CSpriteComponent : public CComponent
{
	CMesh* mesh = nullptr;
	CTexture* texture = nullptr;
	bool textureLoaded = false;
public:
	CSpriteComponent();
	HRESULT LoadTexture(const wchar_t* filePath);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context) override;
	virtual ~CSpriteComponent();
	virtual XMFLOAT4X4 GetTransform() override;
};
