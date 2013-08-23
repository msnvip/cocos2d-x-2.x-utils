//
//  ResourceManager.cpp
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-23.
//
//

#include "ResourceManager.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

const string SpriteFramesResourceManager::Event_LoadCompleted("event_load_completed");

void SpriteFramesResourceManager::addResource(const string & resourceName)
{
	m_waittingLoadResources.insert(resourceName);
}

void SpriteFramesResourceManager::addResources(const set<string> & resourceNames)
{
	set<string>::iterator beg = resourceNames.begin();
	set<string>::iterator end = resourceNames.end();
	for (; beg != end; ++beg)
	{
		m_waittingLoadResources.insert(*beg);
	}
}

void SpriteFramesResourceManager::removeResource(const string & resourceName)
{
	m_waittingLoadResources.erase(resourceName);
}

void SpriteFramesResourceManager::removeResources(const set<string> & resourceNames)
{
	set<string>::iterator beg = resourceNames.begin();
	set<string>::iterator end = resourceNames.end();
	for (; beg != end; ++beg)
	{
		m_waittingLoadResources.erase(*beg);
	}
}

void SpriteFramesResourceManager::loading()
{
	if (!complete())
	{
		set<string>::iterator beg = m_waittingLoadResources.begin();
		
		string file = *beg + ".plist";
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(file.c_str());
		
		m_loadedResources.insert(*beg);
		m_waittingLoadResources.erase(beg);
		
		if (m_waittingLoadResources.size() == 0)
		{
			DIRECT_DISPATCH_EVENT(Event_LoadCompleted);
		}
	}
}

void SpriteFramesResourceManager::unload()
{
	set<string>::iterator beg = m_loadedResources.begin();
	set<string>::iterator end = m_loadedResources.end();
	for (; beg != end; ++beg)
	{
		string plistfile = *beg + ".plist";
		string pngfile = *beg + ".png";
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(plistfile.c_str());
		CCTextureCache::sharedTextureCache()->removeTextureForKey(pngfile.c_str());
	}
}


