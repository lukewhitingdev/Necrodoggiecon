#pragma once
#include "CComponent.h"
#include "CMesh.h"

class CSpriteComponent : public CComponent
{
	CMesh* mesh = nullptr;
public:
	CSpriteComponent();
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context) override;
	virtual ~CSpriteComponent();
};
