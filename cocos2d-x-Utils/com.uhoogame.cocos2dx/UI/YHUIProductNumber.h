//
//  YHUIProductNumber.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-26.
//
//

#ifndef __AndroidaBooM__YHUIProductNumber__
#define __AndroidaBooM__YHUIProductNumber__

#include "YHUISpriteNumber.h"

/**
 * 带乘号的数字
 * @author Zhenyu Yao
 */
class YHUIProductNumber : public YHUISpriteNumber
{
public:
	
	YHUIProductNumber() : m_iconProduct(NULL), m_productInterval(0) {}
	~YHUIProductNumber() {}
	
	/// 使用 CCTexture2D 对象生成
	static YHUIProductNumber *		create(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
										   const cocos2d::CCSize & fontSize, const float32 interval,
										   cocos2d::CCSprite * product);
	
	/// 使用 CCSpriteFrame 对象生成
	static YHUIProductNumber *		create(cocos2d::CCSpriteFrame * spriteFrame,
										   const cocos2d::CCSize & fontSize, const float32 interval,
										   cocos2d::CCSprite * product);
	
	/// 从 CCSpriteFrameCache 中找到 spriteFrameName 对应的 CCSpriteFrame 对象生成
	static YHUIProductNumber *		create(const char * spriteFrameName,
										   const cocos2d::CCSize & fontSize, const float32 interval,
										   cocos2d::CCSprite * product);
	
	/// 使用 Texture 初始化
	virtual bool					init(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
										 const cocos2d::CCSize & fontSize, const float32 interval,
										 cocos2d::CCSprite * product);
	
	/// 使用 CCSpriteFrame 对象初始化
	virtual bool					init(cocos2d::CCSpriteFrame * spriteFrame,
										 const cocos2d::CCSize & fontSize, const float32 interval,
										 cocos2d::CCSprite * product);
	
	/// 从 CCSpriteFrameCache 中找到 spriteFrameName 对应的 CCSpriteFrame 对象初始化
	virtual bool					init(const char * spriteFrameName,
										 const cocos2d::CCSize & fontSize, const float32 interval,
										 cocos2d::CCSprite * product);
	
	/// 设置 x 号与数字贴图的间隔
	virtual void					setProductInterval(float32 productInterval);
	
	/** 重写 YHUISpriteNumber 的方法 **/
	virtual float32					getNumberFontWidth();
	virtual void					layout();
	virtual void					setColor(const cocos2d::ccColor3B& color3);
	virtual void					setOpacity(GLubyte opacity);

private:
	
	cocos2d::CCSprite *				m_iconProduct;
	float32							m_productInterval;		// 默认为 interval
};

#endif /* defined(__AndroidaBooM__YHUIProductNumber__) */


