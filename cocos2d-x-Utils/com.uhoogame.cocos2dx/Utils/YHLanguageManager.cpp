
#include "YHLanguageManager.h"

using namespace cocos2d;

YHLanguageManager::~YHLanguageManager()
{
	if (m_dict != NULL)
	{
		m_dict->release(), m_dict = NULL;
	}
}

YHLanguageManager * YHLanguageManager::sharedManager()
{
	static YHLanguageManager s_instance;
	return &s_instance;
}

void YHLanguageManager::init(const std::string & filename)
{
	m_dict = CCDictionary::createWithContentsOfFile(filename.c_str());
	m_dict->retain();
}

CCString * YHLanguageManager::textForKey(const char * key)
{
	if (m_dict == NULL)
	{
		return NULL;
	}

	return dynamic_cast<CCString *>(m_dict->objectForKey(key));
}


