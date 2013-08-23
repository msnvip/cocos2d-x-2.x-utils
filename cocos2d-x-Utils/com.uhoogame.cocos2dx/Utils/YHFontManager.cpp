
#include "YHFontManager.h"

YHFontManager * YHFontManager::defaultFontManager()
{
	static YHFontManager s_instance;
	return &s_instance;
}

void YHFontManager::init(const std::string & filename)
{
	m_dict = CCDictionary::createWithContentsOfFile(filename.c_str());
	CC_SAFE_RETAIN(m_dict);
}

const char * YHFontManager::fontNameForKey(const char * key)
{
	return (dynamic_cast<CCString *>(m_dict->objectForKey(key)))->getCString();
}

YHFontManager::YHFontManager() : m_dict(NULL) 
{
}

YHFontManager::~YHFontManager() 
{
	CC_SAFE_RELEASE(m_dict);
}


