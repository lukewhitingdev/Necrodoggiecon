#include "AssetManager.h"
#include "Utility/DebugOutput/Debug.h"

std::map<std::string, CMesh*> AssetManager::meshes;
std::map<std::string, CTexture*> AssetManager::textures;
std::map<std::string, CAudio*> AssetManager::audios;

CMesh* AssetManager::AddMesh(std::string meshID, CMesh* mesh)
{
	if(meshes.find(meshID) == meshes.end())
	{
		meshes.emplace(std::make_pair(meshID, mesh));
		return mesh;
	}
	return meshes.at(meshID);
}

CMesh* AssetManager::GetMesh(std::string meshID)
{
	// Check if the mesh exists.
	if (meshes.find(meshID) != meshes.end()) 
	{
		return meshes.at(meshID);
	}
	Debug::LogError("[AssetManager] Could not get mesh with ID: %s!. Returning default mesh.", meshID);
	return AssetManager::GetDefaultMesh();
}

CMesh* AssetManager::GetDefaultMesh()
{
	std::string defaultMeshID = "";
	
	// Create the default mesh in the map if we dont have it.
	if (meshes.find(defaultMeshID) == meshes.end())
	{
		meshes.emplace(std::make_pair(defaultMeshID, new CMesh()));
	}
	return meshes.at(defaultMeshID);
}

CTexture* AssetManager::GetTexture(std::string texturePath)
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
		CTexture* texture = new CTexture();
		if (FAILED(hr = texture->LoadTextureDDS(texturePath)))
			Debug::LogHResult(hr, "[AssetManager] Failed to load texture from path: %s", texturePath);

		
		textures.emplace(std::make_pair(texturePath, texture));

		return texture;
	}
}


CTexture* AssetManager::GetTextureWIC(std::string texturePath)
{
	HRESULT hr;
	if (textures.find(texturePath) != textures.end())
	{
		// The texture exists.
		return textures.at(texturePath);
	}
	else
	{
		// The texture doesnt exist so make one.
		CTexture* texture = new CTexture();
		if (FAILED(hr = texture->LoadTextureWIC(texturePath))) //chaged LoadTextureDDS to LoadTextureWIC
			Debug::LogHResult(hr, "[AssetManager] Failed to load texture from path: %s", texturePath);


		textures.emplace(std::make_pair(texturePath, texture));

		return texture;
	}
}


CAudio* AssetManager::AddAudio(std::string audioPath, CAudio* audio)
{
	if(audios.find(audioPath) != audios.end())
	{
		// If we find it in the assetManager return it.
		return audios.at(audioPath);
	}
	else
	{
		// If we dont find it add it to the audio list.
		audios.emplace(std::make_pair(audioPath, audio));
		return audios.at(audioPath);
	}
}

CAudio* AssetManager::GetAudio(std::string audioPath)
{
	if(audios.find(audioPath) != audios.end())
	{
		// The audio exists.
		return audios.at(audioPath);
	}
	else
	{
		// The audio doesnt exist.
		return nullptr;
	}
}

void AssetManager::RemoveAudio(std::string audioPath)
{
	audios.erase(audioPath);
}

void AssetManager::Destroy()
{
	audios.clear();
	textures.clear();
	meshes.clear();
}

void AssetManager::RenderDebugMenu()
{
}
