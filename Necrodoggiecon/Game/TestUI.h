#pragma once
#include "Cerberus\Core\CEntity.h"
#include <array>
#include "Cerberus/Core/Components/CCameraComponent.h"

class TestUI : public CEntity
{
	class CAnimationSpriteComponent* birb = nullptr;
	class CTextRenderComponent* text1 = nullptr;
	class CTextRenderComponent* text2 = nullptr;
	class CTextRenderComponent* text3 = nullptr;
	class CTextRenderComponent* textFPS = nullptr;
	float timeElapsed = 0;
	float textTimer = 0;
	float fpsTimer = 0;
	unsigned int framesTotal = 0;

	const std::array<const char*, 6> texts =
	{
		"Wow",
		"Amazing",
		"Awesome",
		"Nice One",
		"uwu",
		"Good Job",
	};

	CCameraComponent* camera;
public:
	TestUI();
	virtual void Update(float deltaTime) override;
	virtual ~TestUI();

	void SetCamera(CCameraComponent* cam);
};

