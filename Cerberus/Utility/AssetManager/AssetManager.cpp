#include "AssetManager.h"
#include <locale>

std::map<std::string, CMesh> AssetManager::meshes;
std::map<std::string, CTexture> AssetManager::textures;
std::map<std::string, CAudio> AssetManager::audios;

CMesh AssetManager::AddMesh(std::string meshID, CMesh mesh)
{
	if(meshes.find(meshID) == meshes.end())
	{
		meshes.emplace(std::make_pair(meshID, mesh));
		return mesh;
	}
	return meshes.at(meshID);
}

CMesh AssetManager::GetMesh(std::string meshID)
{
	if (meshes.find(meshID) != meshes.end()) 
	{
		// The mesh exists.
		return meshes.at(meshID);
	}
	return CMesh();
}

CTexture AssetManager::GetTexture(std::string texturePath)
{
	HRESULT hr;
	if(textures.find(texturePath) != textures.end())
	{
		// The texture exists.
		return textures.at(texturePath);
	}
	else
	{
		// The texture doesnt exist so make one.
		CTexture texture = CTexture();
		if (FAILED(hr = texture.LoadTextureDDS(texturePath)))
			Debug::LogHResult(hr, "[AssetManager] Failed to load texture from path: %s", texturePath);

		return texture;
	}
}

CAudio AssetManager::GetAudio(std::string audioPath)
{
	if(audios.find(audioPath) != audios.end())
	{
		// The audio exists.
		return audios.at(audioPath);
	}
	else
	{
		// The audio doesnt exist.
		return CAudio();
	}
}
