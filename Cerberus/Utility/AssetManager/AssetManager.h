#pragma once
#include "CMesh.h"
#include "CTexture.h"
#include "Utility/Audio/CAudio.h"
#include "Utility/DebugOutput/Debug.h"
#include <string>
#include <sstream>
#include <map>

// TODO: Implement this

class AssetManager
{
public:
	static CMesh AddMesh(std::string meshID, CMesh mesh);
	static CMesh GetMesh(std::string meshID);
	static CTexture GetTexture(std::string texturePath);
	static CAudio GetAudio(std::string audioPath);

private:
	static std::map<std::string, CMesh> meshes;
	static std::map<std::string, CTexture> textures;
	static std::map<std::string, CAudio> audios;
};

