#include "DialogueUI.h"




DialogueUI::DialogueUI()
{
	textBackground = AddComponent<CSpriteComponent>();
	textBackground->LoadTextureWIC("Resources/darkBackground.png");
	nameBackground = AddComponent<CSpriteComponent>();
	nameBackground->LoadTextureWIC("Resources/darkBackground.png");
	nameTextRenderComponent = AddComponent<CTextRenderComponent>();

	//Setup Background Sprite
	auto width = Engine::windowWidth;
	auto height = Engine::windowHeight * UIHeightPercent;
	textBackground->SetRenderRect(XMUINT2(width, height));
	textBackground->SetSpriteSize(XMUINT2(width, height));
	textBackground->SetAnchor(XMFLOAT2(0, 1));
	float UIHeight = GetUIHeight();
	textBackground->SetPosition(0, UIHeight, 1);

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
		trc->SetReserveCount(maxCharactersInRow);
		textRenderComponents.push_back(trc);
	}

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
	if (!isUpdating) return;

	timer += deltaTime;
	if (timer >= 1 / charactersPerSecond)
	{
		displayingText.append(reserveText.substr(0,1));
		reserveText.erase(0, 1);
		timer = 0;
		UpdateText();
		if (reserveText.length() == 0)
			isUpdating = false;
	}
}


void DialogueUI::UpdateText()
{
	ClearText();
	int rowsNeeded = ceil(displayingText.length() / maxCharactersInRow);
	if (rowsNeeded >= textRenderComponents.size())
		rowsNeeded = textRenderComponents.size() - 1;

	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = displayingText.substr(size_t(maxCharactersInRow) * i, size_t(maxCharactersInRow) * (i + 1));
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);

		if (i == rowsNeeded && rowText.length() >= maxCharactersInRow)
			isUpdating = false;
	}
}

void DialogueUI::SetText(std::string newText, bool instantDisplay)
{
	ClearText();
	displayingText = "";
	reserveText = newText;
	isUpdating = true;
	if (!instantDisplay) return;

	int rowsNeeded = ceil(reserveText.length() / maxCharactersInRow);
	if (rowsNeeded > textRenderComponents.size())
		rowsNeeded = textRenderComponents.size() - 1;


	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = reserveText.substr(0, maxCharactersInRow);
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
		reserveText.erase(0, maxCharactersInRow);
		displayingText.append(rowText);
	}
	isUpdating = false;
}

void DialogueUI::SetName(std::string newName)
{
	nameText = newName;
	nameTextRenderComponent->SetText(nameText);

	auto charSize = nameTextRenderComponent->GetCharacterDrawSize();
	int width = charSize.x * (nameText.length() + 1);
	int height = charSize.y * 1.5f;
	nameBackground->SetRenderRect(XMUINT2(width, height));
	nameBackground->SetSpriteSize(XMUINT2(width, height));
	nameBackground->SetAnchor(XMFLOAT2(0, 1));

	int xPos = -(Engine::windowWidth * 0.5f) + (charSize.x * 0.5f * (nameText.length() + 1));
	int uiHeight = (GetUIHeight() * 0.5f - height * 0.5f) + 2; 
	nameBackground->SetPosition(xPos, uiHeight, 1);

	nameTextRenderComponent->SetPosition(xPos, uiHeight, 0);
}

void DialogueUI::ClearText()
{
	
	for (CTextRenderComponent* t : textRenderComponents)
	{
		t->SetText("");
	}
}

void DialogueUI::Complete()
{
	isUpdating = false;
	displayingText.append(reserveText);
	UpdateText();
}

void DialogueUI::CompletePage()
{
	ClearText();
	displayingText.append(reserveText);
	reserveText = displayingText;
	displayingText = "";
	int rowsNeeded = ceil(reserveText.length() / maxCharactersInRow);
	if (rowsNeeded >= textRenderComponents.size())
		rowsNeeded = textRenderComponents.size() - 1;

	for (int i = 0; i <= rowsNeeded; i++)
	{
		std::string rowText = reserveText.substr(0, maxCharactersInRow);
		textRenderComponents[i]->SetText(rowText);
		UpdateTextComponentPosition(textRenderComponents[i], i + 1);
		reserveText.erase(0, maxCharactersInRow);
		displayingText.append(rowText);
	}
	isUpdating = false;
}

bool DialogueUI::IsComplete()
{
	if (!isUpdating && reserveText.size() == 0)
		return true;
	return false;
}

void DialogueUI::Advance()
{
	displayingText.clear();
	isUpdating = true;
}

void DialogueUI::ToggleDrawing(bool shouldDraw)
{
	for (CComponent* e : components)
		e->shouldDraw = shouldDraw;
}

