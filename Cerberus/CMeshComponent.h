#pragma once
#include "CComponent.h"
#include "CMesh.h"

class CMeshComponent : public CComponent
{
	CMesh* mesh = nullptr;
public:
	CMeshComponent();
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context) override;
	virtual ~CMeshComponent();
};
