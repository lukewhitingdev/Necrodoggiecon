/*****************************************************************//**
 * \file   AssetManager.h
 * \brief  A asset manager that holds assets to be retreived. This avoids the overhead of making duplicate assets across the program.
 * 
 * \author Luke Whiting.
 * \date   May 2022
 *********************************************************************/

#pragma once
#include "Cerberus\Core\Structs\CMesh.h"
#include "Cerberus\Core\Structs\CTexture.h"
#include "Cerberus/Core/Utility/Audio/CAudio.h"
#include <string>
#include <sstream>
#include <map>

class AssetManager
{
public:
	static CMesh* AddMesh(std::string meshID, CMesh* mesh);
	static CMesh* GetMesh(std::string meshID);
	static CMesh* GetDefaultMesh();
	static CTexture* GetTexture(std::string texturePath);
	static CTexture* GetTextureWIC(std::string texturePath);
	static CAudio* AddAudio(std::string audioPath, CAudio* audio);
	static CAudio* GetAudio(std::string audioPath);
	static void RemoveAudio(std::string audioPath);

	static void Destroy();

private:
	static std::map<std::string, CMesh*> meshes;
	static std::map<std::string, CTexture*> textures;
	static std::map<std::string, CAudio*> audios;
};

