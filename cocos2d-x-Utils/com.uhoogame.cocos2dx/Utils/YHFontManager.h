
#ifndef __YHFontManager_H__
#define __YHFontManager_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
 * 字体管理类
 * @author Zhenyu Yao
 */
class YHFontManager
{
public:
	
	/// 单例模式, 获得唯一的 YHFontManager 对象
	static YHFontManager *	defaultFontManager();
	
	/// 初始化
	void					init(const std::string & filename);
	
	/// 获得字体的名字
	const char *			fontNameForKey(const char * key);
	
private:
	YHFontManager();
	~YHFontManager();
	
private:
	CCDictionary *			m_dict;
};

#endif // __YHFontManager_H__


