#pragma once
#include "CMesh.h"
#include "CTexture.h"
#include "Utility/Audio/CAudio.h"
#include <string>
#include <sstream>
#include <map>

// TODO: Implement this

class AssetManager
{
public:
	static CMesh* AddMesh(std::string meshID, CMesh* mesh);
	static CMesh* GetMesh(std::string meshID);
	static CMesh* GetDefaultMesh();
	static CTexture* GetTexture(std::string texturePath);
	static CAudio* AddAudio(std::string audioPath, CAudio* audio);
	static CAudio* GetAudio(std::string audioPath);
	static void RemoveAudio(std::string audioPath);

	static void Destroy();

	static void RenderDebugMenu();

private:
	static std::map<std::string, CMesh*> meshes;
	static std::map<std::string, CTexture*> textures;
	static std::map<std::string, CAudio*> audios;
};

