
#ifndef __YHEffectGenerator_H__
#define __YHEffectGenerator_H__

#include "cocos2d.h"
#include "cocos2d-extension/CCSpecialSprite.h"
#include "YHFiniteEffect.h"

using namespace std;
using namespace cocos2d;

/**
 * 特效动画的定义类型
 * @author Zhenyu Yao
 */
typedef enum _YHEffectDefineType_
{
	kEffectDefineType_Piece1,		// 由 1 个特效组合
	kEffectDefineType_Piece2,		// 由 2 个特效组合, 默认原始图的切片是右边
	kEffectDefineType_Piece4,		// 由 3 个特效组合, 默认原始图的切片是右上角
}YHEffectDefineType;

/**
 * 特效动画的定义器, 从 CCDictionary 解析出的数据放入到 YHEffectDefiner 对象中
 * @author Zhenyu Yao
 */
class YHEffectDefiner : public CCObject
{
public:
	YHEffectDefiner(YHEffectDefineType type, const char * name) : m_type(type), m_animationName(name) {}
	YHEffectDefiner(CCDictionary * dict);
	~YHEffectDefiner() {}
	
	/// 获得特效定义的类型
	YHEffectDefineType		getType() const { return m_type; }
	
	/// 获得/设置特效定义的类型
	const char *			getAnimationName() const { return m_animationName.c_str(); }
	void					setAnimationName(const char * name) { m_animationName = name; }
	
private:
	YHEffectDefineType		m_type;
	std::string				m_animationName;
};

/**
 * 特效工厂类, 主要负责生成带有动画效果的 CCSprite 对象
 * @author Zhenyu Yao
 */
class YHEffectFactory
{
public:
	
	YHEffectFactory();
	~YHEffectFactory();
	
	/// 从缓存中获得 YHEffectDefiner 对象
	YHEffectDefiner *			effectDefinerForKey(const string & key);
	
	/// 将 YHEffectDefiner 对象放入到缓存中
	void						addEffectDefiner(const string & key, YHEffectDefiner * definer);
	
	/// 清空缓存中的所有 YHEffectDefiner 对象
	void						cleanAllEffectDefiners();
	
	/// 清空缓存中所有的 CCSprite 对象
	void						cleanAllSprites();
	
	/// cleanAllEffectDefiners + cleanAllSprites
	void						cleanAll();
	
	/// 根据特效的名字得到特效的 CCSprite 对象
	CCSprite *					effectSpriteForKey(const string & key);
	
	/// 根据 YHEffectDefiner 得到特效的 CCSprite 对象
	CCSprite *					effectSpriteForDefiner(const YHEffectDefiner * definer);
	
private:
	
	/// 从缓存中获得 YHDefaultFiniteEffect 对象
	YHDefaultFiniteEffect *		finiteEffectFromCache();
	
private:
	CCDictionary *				m_definerCache;
	CCSet *						m_effectCache;
};

#endif // __YHEffectGenerator_H__


