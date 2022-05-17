#include "DialogueUI.h"




DialogueUI::DialogueUI()
{
	spriteComponent = AddComponent<CSpriteComponent>();

	spriteComponent->LoadTextureWIC("Resources/darkBackground.png");

	//Setup Background Sprite
	auto width = Engine::windowWidth;
	auto height = Engine::windowHeight * UIHeightPercent;
	spriteComponent->SetRenderRect(XMUINT2(width, height));
	spriteComponent->SetSpriteSize(XMUINT2(width, height));
	spriteComponent->SetAnchor(XMFLOAT2(0, 1));
	float UIHeight = GetUIHeight();
	spriteComponent->SetPosition(0, UIHeight, 1);

	//Setup TextRenderComponents
	auto trc = AddComponent<CTextRenderComponent>();
	textRenderComponents.push_back(trc);

	maxCharactersInRow = width / (textRenderComponents[0]->GetCharacterSize().x * 2);
	rowHeight = textRenderComponents[0]->GetCharacterSize().y + rowPadding;
	maxRowCount = (height / rowHeight) * 0.5f;

	textRenderComponents.clear();
	for (int i = 0; i < maxRowCount; i++)
	{
		auto trc = AddComponent<CTextRenderComponent>();
		textRenderComponents.push_back(trc);
	}

	//textRenderComponents[0]->SetText("abc");
	//UpdateTextComponentPosition(textRenderComponents[0], 1);

	for (int i = 0; i < textRenderComponents.size(); i++)
	{
		textRenderComponents[i]->SetText("mynamejeff" + std::to_string(i));
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
	}

	Debug::Log(std::to_string(maxCharactersInRow).c_str());
	Debug::Log(std::to_string(maxRowCount).c_str());

	std::string str = "This system will contain the players’ input. This input will then be passed down to the currently attached character. This will allow us to have multiple characters with setting up input on each of them, as well as this, it will make it so that we can swap between characters mid-level easily. ";
	SetText(str, false);

	for (CComponent* e : components)
		e->ui = true;
}

void DialogueUI::UpdateTextComponentPosition(CTextRenderComponent* textComponent, int row)
{
	int charCount = textComponent->GetText().size();
	XMUINT2 charSize = textComponent->GetCharacterDrawSize();

	int xPos = -(Engine::windowWidth * 0.5f) + (charSize.x * 0.5f * (charCount + 1));
	int yPos = (GetUIHeight() * 0.5f) - charSize.y - (rowHeight * 2 * (row));
	textComponent->SetPosition(xPos, yPos, 0);
}

float DialogueUI::GetUIHeight()
{
	float height = Engine::windowHeight * UIHeightPercent;
	return -(Engine::windowHeight * 0.5f) + (height * 0.5f);
}

DialogueUI::~DialogueUI()
{
}

void DialogueUI::Update(float deltaTime)
{
	if (!needsUpdate) return;

	timer += deltaTime;
	if (timer >= 1 / charactersPerSecond)
	{
		displayingText.append(reserveText.substr(0,1));
		reserveText.erase(0, 1);
		timer = 0;
		UpdateText();
		if (reserveText.length() == 0)
			needsUpdate = false;
	}
}


void DialogueUI::UpdateText()
{
	ClearText();
	int rowsNeeded = ceil(displayingText.length() / maxCharactersInRow);

	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = displayingText.substr(size_t(maxCharactersInRow) * i, size_t(maxCharactersInRow) * (i + 1));
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
	}
}

void DialogueUI::SetText(std::string newText, bool instantDisplay)
{
	ClearText();
	displayingText = "";
	reserveText = newText;
	needsUpdate = true;
	if (!instantDisplay) return;

	int rowsNeeded = ceil(reserveText.length() / maxCharactersInRow);

	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = reserveText.substr(0, maxCharactersInRow);
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
		reserveText.erase(0, maxCharactersInRow);
		displayingText.append(rowText);
	}
	needsUpdate = false;
}

void DialogueUI::ClearText()
{
	
	for (CTextRenderComponent* t : textRenderComponents)
	{
		t->SetText("");
	}
}
