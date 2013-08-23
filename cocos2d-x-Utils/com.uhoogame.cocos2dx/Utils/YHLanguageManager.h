
#ifndef __YHLanguageManager_H__
#define __YHLanguageManager_H__

#include "cocos2d.h"

/**
 * 语言管理器. 类似字典的功能, 输入键, 查询到键对应的字符串信息. 在初始化的使用装载供查询的配置文件.
 * @author Zhenyu Yao
 */
class YHLanguageManager
{
public:
	static YHLanguageManager * sharedManager();
	
	/// 初始化
	void					init(const std::string & filename);
	
	/// 查询 key 对应的字符串
	cocos2d::CCString *		textForKey(const char * key);
	
private:
	YHLanguageManager() : m_dict(NULL) {}
	~YHLanguageManager();
	
	cocos2d::CCDictionary *			m_dict;
};

#endif // __YHLanguageManager_H__


