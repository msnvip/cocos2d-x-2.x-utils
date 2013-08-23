//
//  YHUIPercentNumber.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-26.
//
//

#ifndef __AndroidaBooM__YHUIPercentNumber__
#define __AndroidaBooM__YHUIPercentNumber__

#include "YHUIDecimalNumber.h"

/**
 * 百分比数字显示
 * @author Zhenyu Yao
 */
class YHUIPercentNumber : public YHUIDecimalNumber
{
public:
	
	/// 使用 CCTexture2D 创建  YHUIPercentNumber 对象
	static YHUIPercentNumber *		create(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
										   const cocos2d::CCSize & fontSize, const float32 interval,
										   cocos2d::CCSprite * iconDot, cocos2d::CCSprite * iconPercent);
	
	/// 使用 CCSpriteFrame 创建  YHUIPercentNumber 对象
	static YHUIPercentNumber *		create(cocos2d::CCSpriteFrame * spriteFrame,
										   const cocos2d::CCSize & fontSize, const float32 interval,
										   cocos2d::CCSprite * iconDot, cocos2d::CCSprite * iconPercent);
	
	/// 从 CCSpriteFrameCache 中找到 spriteFrameName 对应的 CCSpriteFrame 对象创建 YHUIPercentNumber 对象
	static YHUIPercentNumber *		create(const char * spriteFrameName,
										   const cocos2d::CCSize & fontSize, const float32 interval,
										   cocos2d::CCSprite * iconDot, cocos2d::CCSprite * iconPercent);
	
public:
	
	YHUIPercentNumber() :
	m_iconPercent(NULL),
	m_percentInterval(0)
	{}
	~YHUIPercentNumber()
	{}
	
	/// 使用 CCTexture2D 初始化
	virtual bool					init(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
										 const cocos2d::CCSize & fontSize, const float32 interval,
										 cocos2d::CCSprite * iconDot, cocos2d::CCSprite * iconPercent);
	
	/// 使用 CCSpriteFrame 初始化
	virtual bool					init(cocos2d::CCSpriteFrame * spriteFrame,
										 const cocos2d::CCSize & fontSize, const float32 interval,
										 cocos2d::CCSprite * iconDot, cocos2d::CCSprite * iconPercent);
	
	/// 从 CCSpriteFrameCache 中找到 spriteFrameName 对应的 CCSpriteFrame 对象初始化
	virtual bool					init(const char * spriteFrameName,
										 const cocos2d::CCSize & fontSize, const float32 interval,
										 cocos2d::CCSprite * iconDot, cocos2d::CCSprite * iconPercent);
	
	/// 设置数字与百分号之间的间隔
	virtual void					setPercentInterval(float32 interval);
	
public: /** Override Functions **/
	
	virtual float32					getNumberFontWidth();
	virtual void					layout();
	virtual void					setColor(const cocos2d::ccColor3B& color3);
	virtual void					setOpacity(GLubyte opacity);
	
private:
	cocos2d::CCSprite *				m_iconPercent;
	float32							m_percentInterval;
};

#endif /* defined(__AndroidaBooM__YHUIPercentNumber__) */


