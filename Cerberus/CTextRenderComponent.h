#pragma once
#include "CSpriteComponent.h"

class CTextRenderComponent : public CComponent
{
	std::string text = "";
	std::string font = "Resources\\Man.dds";
	std::vector<CSpriteComponent*> sprites;
public:
	CTextRenderComponent();
	HRESULT SetFont(std::string filePath);
	void SetText(std::string newText);
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, XMFLOAT4X4 parentMat, ConstantBuffer& cb, ID3D11Buffer* constantBuffer) override;
	virtual ~CTextRenderComponent();
	//virtual XMFLOAT4X4 GetTransform() override;
};

