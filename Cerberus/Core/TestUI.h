#pragma once
#include "CEntity.h"

class TestUI : public CEntity
{
	class CSpriteComponent* birb = nullptr;
	class CTextRenderComponent* text1 = nullptr;
	class CTextRenderComponent* text2 = nullptr;
	float timeElapsed = 0;
public:
	TestUI();
	virtual void Update(float deltaTime) override;
	virtual ~TestUI();
};

