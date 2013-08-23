#ifndef __AndroidaBoom_YHAnimationCache__
#define __AndroidaBoom_YHAnimationCache__

#include "cocos2d.h"
#include "YHAnimationHelper.h"

/**
 * 管理 CCAnimation 对象, 首先负责加载动画的配置文件, 然后可以根据动画的 key 得到指定的 CCAnimation 对象
 * @wangtiwei
 */
class YHAnimationCache
{
public:
	~YHAnimationCache(void);
	
	/// 单例模式, 获得全局 YHAnimationCache 对象
	static YHAnimationCache *	sharedAnimationCache();
	
	/// 添加动画定义到字典中
	void						addAnimations(cocos2d::CCDictionary * dict);
	
	/**
	 * 根据动画名得到动画, 以 ver2 方式解析动画.
	 * 该方法没有调用 CCAnimationCache, 不会将 CCAnimation 放入到 CCAnimationCache 中.
	 * @param key 动画在字典中的键名
	 * @return CCAnimation 动画
	 */
	cocos2d::CCAnimation *		animationForKey_Ver2(const std::string & key);
	
	/**
	 * 根据动画名得到动画, 以 ver1 方式解析动画
	 * 该方法没有调用 CCAnimationCache, 不会将 CCAnimation 放入到 CCAnimationCache 中.
	 * @param key 动画在字典中的键名
	 * @return CCAnimation 动画
	 */
	cocos2d::CCAnimation *		animationForKey_Ver1(const std::string & key);
	
	/**
	 * 根据 animationForKey_Ver2 获得动画, 会优先从 CCAnimationCache 搜索是否有该动画, 如果没有该动画再创建动画, 否则从 CCAnimationCache 中获得动画
	 * @param key 动画在字典中的名字
	 * @return CCAnimation 对象
	 */
	cocos2d::CCAnimation *		animationForKeyFromCache_Ver2(const std::string & key);
	
	/**
	 * 根据 animationForKey_Ver1 获得动画, 会优先从 CCAnimationCache 搜索是否有该动画, 如果没有该动画再创建动画, 否则从 CCAnimationCache 中获得动画
	 * @param key 动画在字典中的名字
	 * @return CCAnimation 对象
	 */
	cocos2d::CCAnimation *		animationForKeyFromCache_Ver1(const std::string & key);
	
	/**
	 * 根据动画名生成动画对应的 CCAnimate 对象, 该方法会调用 animationForKeyFromCache 方法
	 * @param key 动画名
	 * @return CCAnimate 对象
	 */
	cocos2d::CCAnimate *		animateForKey(const std::string & key, bool isVer2 = true);
	
	/**
	 * 根据动画名生成对应的 CCRepeatForever 的对象, 它包装了 CCAnimate, 使其无限重复, 该方法会调用 animationForKeyFromCache 方法
	 * @param key 动画名
	 * @return CCRepeatForever 对象
	 */
	cocos2d::CCRepeatForever *	foreverAnimateForKey(const std::string & key, bool isVer2 = true);
	
	/// 清空所有缓存的 CCAnimation 对象
	void						cleanAllAnimations();
	
	/// 获得存放动画定义的字典
	cocos2d::CCDictionary *		getAnimationFileDic() const { return m_animationFileDic; }
	
private:
	YHAnimationCache(void);
	
	/// 动画文件数据字典
	cocos2d::CCDictionary *						m_animationFileDic;
};

#endif /*__AndroidaBoom_YHAnimationCache__*/


