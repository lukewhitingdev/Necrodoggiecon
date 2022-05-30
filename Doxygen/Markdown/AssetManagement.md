# Asset Manager

## Managing Assets within the engine.

The asset manager was created to allow for many sprites to be drawn to the screen without a enourmous overhead. This was done by only allocating memory once for a specific object. This means that all sprites in the scene can use the same mesh data and the engine doesnt have to re-generate the mesh data everytime a new object wishes to be spawned. Instead the engine polls the asset manager and the manager retreives the data and passes it onto the caller. The caller can then instanciate objects with the data from the asset manager and skip the overhead of making stack memory itself. Furthermore, this has been extended for Audio and Textures to allow for those assets to be polled in a similar way.

## Relating Classes:

-   [AssetManager](https://github.com/lukewhitingdev/Necrodoggiecon/blob/57046ed2e0a56e2bc1db4d80ddb107e72a69795f/Cerberus/Core/Utility/AssetManager/AssetManager.h)