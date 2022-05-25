#include "AssetManager.h"
#include "Cerberus/Core/Utility/DebugOutput/Debug.h"

std::map<std::string, CMesh*> AssetManager::meshes;
std::map<std::string, CTexture*> AssetManager::textures;
std::map<std::string, CAudio*> AssetManager::audios;

/**
 * Adds a CMesh to the asset manager.
 * 
 * \param meshID the meshID that is used to retreive the mesh later.
 * \param mesh the mesh that you wish to store.
 * \return CMesh pointer to the stored mesh.
 */
CMesh* AssetManager::AddMesh(std::string meshID, CMesh* mesh)
{
	if(meshes.find(meshID) == meshes.end())
	{
		meshes.emplace(std::make_pair(meshID, mesh));
		return mesh;
	}
	return meshes.at(meshID);
}

/**
 * Returns the mesh in the asset manager if it exists.
 * 
 * \param meshID the meshID of the mesh you wish to retreive.
 * \return a pointer to the mesh that was retreived.
 */
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

/**
 * Returns the default mesh held within the asset manager.
 * 
 * \return the default mesh held within the manager
 */
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

/**
 * Returns a texture at a specified texture path.
 * 
 * \param texturePath the texture path that you wish to retreive.
 * \return a pointer to the retreived texture.
 */
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
		{
			Debug::LogHResult(hr, "[AssetManager] Failed to load texture from path: %s", texturePath.c_str());
			return nullptr;
		}

		
		textures.emplace(std::make_pair(texturePath, texture));

		return texture;
	}
}

/**
 * Returns a texture at a specified texture path.
 *
 * \param texturePath the texture path that you wish to retreive.
 * \return a pointer to the retreived texture.
 */
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
		if (FAILED(hr = texture->LoadTextureWIC(texturePath))) 
		{
			Debug::LogHResult(hr, "[AssetManager] Failed to load texture from path: %s", texturePath.c_str());
			return nullptr;
		}


		textures.emplace(std::make_pair(texturePath, texture));

		return texture;
	}
}

/**
 * Adds a audio clip to the asset manager.
 * 
 * \param audioPath the audio path you wish to add
 * \param audio a pointer to the audio that you wish to store.
 * \return returns a pointer to the stored audio.
 */
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

/**
 * Returns a stored audio at a path.
 * 
 * \param audioPath the path of the audio you wish to retreive.
 * \return a pointer to the retreived audio.
 */
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

/**
 * Removes a audio from the asset manager.
 * 
 * \param audioPath the audio path that you wish to remove.
 */
void AssetManager::RemoveAudio(std::string audioPath)
{
	audios.erase(audioPath);
}
/**
 * Destroys the asset manager.
 * 
 */
void AssetManager::Destroy()
{
	audios.clear();
	textures.clear();
	meshes.clear();
}
