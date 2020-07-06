#pragma once
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

#pragma comment (lib,"fmod_vc.lib")

#include <string>
#include <unordered_map>

class SoundEffect
{
public:
	class Sound
	{
		friend class SoundEffect;
	public:
		enum class Type
		{
			BGM,
			EFFECT
		};
	private:
		FMOD::System* pSystem;
		FMOD::Sound* pSound;
		FMOD::Channel* pChannel;

		Type type;
		float volume;
		unsigned int length;
	};

	std::unordered_map<std::wstring, Sound*>	soundList;
	FMOD::System* pSystem;

	Sound* currentBgm;

public:
	SoundEffect();
	~SoundEffect();

	void Update();

	bool Load(std::wstring filePath, Sound::Type type);
	void Play(std::wstring key);
	void Stop(std::wstring key);
	void Paues(std::wstring key);
	void VolumeUp(std::wstring key, float fSecondPerFrame);
	void VolumeDown(std::wstring key, float fSecondPerFrame);
	void SetGlobalVolume(float volume);
};

using SFXType = SoundEffect::Sound::Type;