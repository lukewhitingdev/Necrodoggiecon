# Audio

## Adding, Playing and Managing Audio

The audio system manages all audio in the game and abstracts away FMOD's lower level API. The audio manager also interfaces with the AssetManager to make sure that duplicate audio doesnt create unnecessary memory when not required. The audio manager is used heavily by audio emitters as a high-level abstraction to the audio system and FMOD. Furthermore, there are smaller classes used to store Audio data in a OOP way. For instance CAudio encapsulates all FMOD data into a easy to remove / change class, CEmitter operates in the same way but holds a CAudio reference and the range + other features of the emitter.

## Audio Emitters

Audio Emitters are a component within the engine. This component is responsible for interfacing with the audio system to play audio at a certain location. The audio system keeps track of all emitters within the scene and attenuates them accordingly to allow for psuedo-3D audio.

## Architecture

![The General Architecture](/Doxygen/Images/AudioSystemDiagram.png)

## Relating Classes:

-   AudioController
-   CAudio
-   CEmitter

-   CAudioEmitterComponent