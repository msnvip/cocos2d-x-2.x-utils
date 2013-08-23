//
//  SoundController.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-24.
//
//

#include "SoundController.h"

using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

#define CHECK_INITIALIZED 		\
		if (m_engine == NULL)	\
		{						\
			return;				\
		}						

#define CHECK_INITIALIZED_P(__P__)			\
		if (m_engine == NULL)				\
		{									\
			return __P__;					\
		}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

SoundController * SoundController::sharedSoundController()
{
	static SoundController s_instance;
	return &s_instance;
}

void SoundController::init()
{
	m_engine = SimpleAudioEngine::sharedEngine();
	
	m_fadeType = kFadeType_None;
	m_effectsVolume = m_engine->getEffectsVolume();
	m_BGMVolume = m_engine->getBackgroundMusicVolume();
}

void SoundController::appendMappingFile(CCDictionary * dict)
{
	CCArray * keys = dict->allKeys();
	uint32 count = keys->count();
	for (uint32 i = 0; i < count; ++i)
	{
		CCString * key = dynamic_cast<CCString *>(keys->objectAtIndex(i));
		const char * strKey = key->getCString();
		CCObject * value = dict->objectForKey(strKey);
		m_dict->setObject(value, strKey);
	}
}

uint32 SoundController::playEffectWithKey(const string & key, bool loop)
{
	CHECK_INITIALIZED_P(0xffffffff);
	
	CCString * filename = dynamic_cast<CCString *>(m_dict->objectForKey(key.c_str()));
	if (filename != NULL)
	{
		return m_engine->playEffect((m_subpath + filename->getCString()).c_str(), loop);
	}
	
	return 0xffffffff;
}

void SoundController::playBGMWithKey(const string & key, bool loop)
{
	CHECK_INITIALIZED;
	
	CCString * filename = dynamic_cast<CCString *>(m_dict->objectForKey(key.c_str()));
	if (filename != NULL)
	{
		m_engine->playBackgroundMusic((m_subpath + filename->getCString()).c_str(), loop);
	}
}

void SoundController::fadeOutVolume(float32 duration)
{
	CHECK_INITIALIZED;
	
	m_fadeType = kFadeType_Out;
	m_elapse = 0.0f;
	m_duration = duration;
	m_engine->setEffectsVolume(m_effectsVolume);
	m_engine->setBackgroundMusicVolume(m_BGMVolume);
	
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

void SoundController::fadeInVolume(float32 duration)
{
	CHECK_INITIALIZED;
	
	m_fadeType = kFadeType_In;
	m_elapse = 0.0f;
	m_duration = duration;
	m_engine->setEffectsVolume(0.0f);
	m_engine->setBackgroundMusicVolume(0.0f);
	
	CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

void SoundController::update(float dt)
{
	if (m_fadeType != kFadeType_None)
	{
		m_elapse += dt;
		
		float32 percent = m_elapse / m_duration;
		percent = m_fadeType == kFadeType_Out ? 1.0f - percent : percent;
		m_engine->setBackgroundMusicVolume(m_BGMVolume * percent);
		m_engine->setEffectsVolume(m_effectsVolume * percent);
		
		if (m_elapse >= m_duration)
		{
			m_fadeType = kFadeType_None;
			CCDirector::sharedDirector()->getScheduler()->unscheduleUpdateForTarget(this);
		}
	}
}

const char * SoundController::fileWithKey(const std::string & key)
{
	const CCString * filename = m_dict->valueForKey(key.c_str());
	return string(m_subpath + filename->getCString()).c_str();
}

void SoundController::preloadBackgroundMusic(const char * pszFilePath)
{
	CHECK_INITIALIZED;
	m_engine->preloadBackgroundMusic((m_subpath + pszFilePath).c_str());
}

void SoundController::playBackgroundMusic(const char * pszFilePath, bool bLoop)
{
	CHECK_INITIALIZED;
	m_engine->playBackgroundMusic((m_subpath + pszFilePath).c_str(), bLoop);
}

void SoundController::playBackgroundMusic(const char * pszFilePath)
{
	CHECK_INITIALIZED;
	m_engine->playBackgroundMusic((m_subpath + pszFilePath).c_str());
}

void SoundController::stopBackgroundMusic(bool bReleaseData)
{
	CHECK_INITIALIZED;
	m_engine->stopBackgroundMusic(bReleaseData);
}

void SoundController::stopBackgroundMusic()
{
	CHECK_INITIALIZED;
	m_engine->stopBackgroundMusic();
}

void SoundController::pauseBackgroundMusic()
{
	CHECK_INITIALIZED;
	m_engine->pauseBackgroundMusic();
}

void SoundController::resumeBackgroundMusic()
{
	CHECK_INITIALIZED;
	m_engine->resumeBackgroundMusic();
}

void SoundController::rewindBackgroundMusic()
{
	CHECK_INITIALIZED;
	m_engine->rewindBackgroundMusic();
}

void SoundController::willPlayBackgroundMusic()
{
	CHECK_INITIALIZED;
	m_engine->willPlayBackgroundMusic();
}

bool SoundController::isBackgroundMusicPlaying()
{
	CHECK_INITIALIZED_P(false);
	return m_engine->isBackgroundMusicPlaying();
}

float SoundController::getBackgroundMusicVolume()
{
	CHECK_INITIALIZED_P(0);
	return m_engine->getBackgroundMusicVolume();
}

void SoundController::setBackgroundMusicVolume(float volume)
{
	CHECK_INITIALIZED;
	m_BGMVolume = volume;
	m_engine->setBackgroundMusicVolume(volume);
}

float SoundController::getEffectsVolume()
{
	CHECK_INITIALIZED_P(0);
	return m_engine->getEffectsVolume();
}

void SoundController::setEffectsVolume(float volume)
{
	CHECK_INITIALIZED;
	m_effectsVolume = volume;
	m_engine->setEffectsVolume(volume);
}

uint32 SoundController::playEffect(const char * pszFilePath, bool bLoop)
{
	CHECK_INITIALIZED_P(0xffffffff);
	return m_engine->playEffect((m_subpath + pszFilePath).c_str(), bLoop);
}

uint32 SoundController::playEffect(const char * pszFilePath)
{
	CHECK_INITIALIZED_P(0xffffffff);
	return m_engine->playEffect((m_subpath + pszFilePath).c_str());
}

void SoundController::pauseEffect(uint32 soundID)
{
	CHECK_INITIALIZED;
	m_engine->pauseEffect(soundID);
}

void SoundController::pauseAllEffects()
{
	CHECK_INITIALIZED;
	m_engine->pauseAllEffects();
}

void SoundController::resumeEffect(uint32 soundID)
{
	CHECK_INITIALIZED;
	m_engine->resumeEffect(soundID);
}

void SoundController::resumeAllEffects()
{
	CHECK_INITIALIZED;
	m_engine->resumeAllEffects();
}

void SoundController::stopEffect(uint32 soundID)
{
	CHECK_INITIALIZED;
	m_engine->stopEffect(soundID);
}

void SoundController::stopAllEffects()
{
	CHECK_INITIALIZED;
	m_engine->stopAllEffects();
}

void SoundController::preloadEffect(const char * pszFilePath)
{
	CHECK_INITIALIZED;
	m_engine->preloadEffect((m_subpath + pszFilePath).c_str());
}

void SoundController::unloadEffect(const char * pszFilePath)
{
	CHECK_INITIALIZED;
	m_engine->unloadEffect((m_subpath + pszFilePath).c_str());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

SoundController::SoundController() : m_engine(NULL), m_fadeType(kFadeType_None), m_effectsVolume(0.0f), m_BGMVolume(0.0f)
{
	m_dict = new CCDictionary();
}

SoundController::~SoundController()
{
	m_dict->release(), m_dict = NULL;
}


