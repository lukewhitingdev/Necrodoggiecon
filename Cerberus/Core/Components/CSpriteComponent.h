/*****************************************************************//**
 * \file   CSpriteComponent.h
 * \brief  A component for loading and displaying a 2D texture in world space as part of CEntity.
 * 
 * \author Arrien Bidmead
 * \date   January 2022
 *********************************************************************/

#pragma once
#include "Cerberus\Core\CComponent.h"
#include "Cerberus\Core\Structs\CMesh.h"
#include "Cerberus\Core\Structs\CTexture.h"
#include "Cerberus\Core\Structs\CMaterial.h"

/**
 * A component for loading and displaying a 2D texture in world space as part of CEntity.
 */
class CSpriteComponent : public CComponent
{
	CMesh* mesh = nullptr;
	CMaterial* material = nullptr;
	CTexture* texture = nullptr;

	XMUINT2 renderRect;
	XMFLOAT2 textureOffset = { 0,0 };
	XMUINT2 spriteSize;
	XMFLOAT4 tint = { 0,0,0,0 };

public:

	/**
	 * Used to resize the portion of the texture you want to display on the sprite in pixels.
	 * Use to set the size of a selection of a sprite sheet.
	 */
	virtual void SetRenderRect(const XMUINT2& newSize);

	/**
	 * The offset in pixels of where the sprite should start rendering in the texture.
	 * Use this for selecting a section of a sprite sheet.
	 * By default set to 0,0.
	 */
	void SetTextureOffset(const XMFLOAT2& newOffset);

	/**
	 * The size of the ingame sprite in pixels.
	 * Set automatically on texture load.
	 */
	virtual void SetSpriteSize(const XMUINT2& newSize) { spriteSize = newSize; };

	/**
	 * Set the color tint of the sprite in RGBA.
	 */
	void SetTint(const XMFLOAT4& newTint);

	virtual void SetUseTranslucency(const bool& newTranslucency) override;

	/**
	 * Loads the texture from a file.
	 * MUST use the .dds file type.
	 */
	HRESULT LoadTexture(const std::string& filePath);

	/**
	 * Loads the texture from a file.
	 * MUST use BMP, JPEG, PNG, TIFF, GIF, or HD Photo file types.
	 */
	HRESULT LoadTextureWIC(const std::string& filePath);

	const XMUINT2& GetRenderRect() const { return renderRect; };
	const XMFLOAT2& GetTextureOffset() const { return textureOffset; };
	const XMUINT2& GetSpriteSize() const { return spriteSize; };
	const XMFLOAT4& GetTint() const { return tint; };
	const XMUINT2& GetTextureSize() const { if (texture != nullptr) return texture->textureSize; else return { 0,0 }; };
	virtual XMFLOAT4X4 GetTransform() override;

	CSpriteComponent();
	virtual void Update(float deltaTime) override;
	virtual void Draw(ID3D11DeviceContext* context, const XMFLOAT4X4& parentMat, ConstantBuffer cb, ID3D11Buffer* constantBuffer) override;
	virtual ~CSpriteComponent();
};
