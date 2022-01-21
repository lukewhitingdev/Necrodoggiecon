#pragma once
#include "CEntity.h"

class TestUI : public CEntity
{
	class CSpriteComponent* birb = nullptr;
	class CTextRenderComponent* text1 = nullptr;
	class CTextRenderComponent* text2 = nullptr;
	class CTextRenderComponent* text3 = nullptr;
	float timeElapsed = 0;
	float timeElapsed2 = 0;

	const char* texts[7] =
	{
		"Whatsup.",
		"Hi.",
		"Why are you ignoring me?",
		"Dont forget to hydrate.",
		"Pretty sus tbh.",
		"Hint: there are no hints here.",
		"Have you tried like not doing that?",
	};
public:
	TestUI();
	virtual void Update(float deltaTime) override;
	virtual ~TestUI();
};

