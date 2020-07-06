#include "SoundEffect.h"

SoundEffect::SoundEffect()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(32, FMOD_INIT_NORMAL, 0);
}

SoundEffect::~SoundEffect()
{
	std::unordered_map<std::wstring, Sound*>::iterator it;
	for (it = soundList.begin(); it != soundList.end(); it++)
	{
		Sound* ptrSound = it->second;
		delete ptrSound;
	}
	soundList.clear();
	pSystem->close();
	pSystem->release();
}

void SoundEffect::Update()
{
	pSystem->update();
}

bool SoundEffect::Load(std::wstring filePath, Sound::Type type)
{
	std::wstring key;

	int x = filePath.find_last_of('/');
	for (x++; x < filePath.length(); x++)
		key.push_back(filePath[x]);

	std::string tmpPath;
	tmpPath.assign(filePath.begin(), filePath.end());

	Sound* ptrSound = new Sound;
	ptrSound->pSystem = pSystem;

	if (ptrSound->pSystem->createSound( tmpPath.c_str(),
		FMOD_DEFAULT, 0, &(ptrSound->pSound))
		== FMOD_OK)
	{
		ptrSound->type = type;
		ptrSound->pSound->getLength(&ptrSound->length, FMOD_TIMEUNIT_MS);
		soundList.insert(std::make_pair(key, ptrSound));
		return true;
	}

	delete ptrSound;
	return false;
}

void SoundEffect::Play(std::wstring key)
{
	std::unordered_map<std::wstring, Sound*>::iterator it;
	it = soundList.find(key);
	if (it == soundList.end()) return;

	if (it->second->type == Sound::Type::BGM)
	{
		currentBgm = it->second;
		it->second->pSound->setMode(FMOD_LOOP_NORMAL);
	}
	it->second->pSystem->playSound(it->second->pSound, 0, false, &it->second->pChannel);
}

void SoundEffect::Stop(std::wstring key)
{
	std::unordered_map<std::wstring, Sound*>::iterator it;
	it = soundList.find(key);
	if (it == soundList.end()) return;

	it->second->pChannel->stop();
}

void SoundEffect::Paues(std::wstring key)
{
	std::unordered_map<std::wstring, Sound*>::iterator it;
	it = soundList.find(key);
	if (it == soundList.end()) return;

	bool paused = false;
	it->second->pChannel->getPaused(&paused);
	it->second->pChannel->setPaused(!paused);
}

void SoundEffect::VolumeUp(std::wstring key, float fSecondPerFrame)
{
	std::unordered_map<std::wstring, Sound*>::iterator it;
	it = soundList.find(key);
	if (it == soundList.end()) return;

	it->second->volume += 0.1f * fSecondPerFrame;
	if (it->second->volume > 1.0f) it->second->volume = 1.0f;
	it->second->pChannel->setVolume(it->second->volume);
}

void SoundEffect::VolumeDown(std::wstring key, float fSecondPerFrame)
{
	std::unordered_map<std::wstring, Sound*>::iterator it;
	it = soundList.find(key);
	if (it == soundList.end()) return;

	it->second->volume -= 0.1f * fSecondPerFrame;
	if (it->second->volume < 0.0f) it->second->volume = 0.0f;
	it->second->pChannel->setVolume(it->second->volume);
}

void SoundEffect::SetGlobalVolume(float volume)
{
	std::unordered_map<std::wstring, Sound*>::iterator it;
	for (it = soundList.begin(); it != soundList.end(); it++)
	{
		it->second->pChannel->setVolume(volume);
	}
}