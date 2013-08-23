//
//  YHUISpriteNumber.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-25.
//
//

#ifndef __AndroidaBooM__YHUISpriteNumber__
#define __AndroidaBooM__YHUISpriteNumber__

#include "YHTypes.h"
#include "YHISpriteNumber.h"

/**
 * 数字贴图, 不能向该容器内添加其他的显示对象
 * 贴图样式: ICON 12345
 * @author Zhenyu Yao
 */
class YHUISpriteNumber : public YHISpriteNumber
{
public:
	
	/// 使用 Texture2D 生成 YHUISpriteNumber 对象
	static YHUISpriteNumber * 		create(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
										   const cocos2d::CCSize & fontSize, const float32 interval);
	
	/// 使用 CCSpriteFrame 生成 YHUISpriteNumber 对象
	static YHUISpriteNumber *		create(cocos2d::CCSpriteFrame * spriteFrame,
										   const cocos2d::CCSize & fontSize, const float32 interval);
	
	/// 从 CCSpriteFrameCache 中找到 CCSpriteFrame 对象, 生成 YHUISpriteNumber 对象
	static YHUISpriteNumber *		create(const char * spriteFrameName,
										   const cocos2d::CCSize & fontSize, const float32 interval);
	
public:
	YHUISpriteNumber();
	virtual ~YHUISpriteNumber();
	
	/// 使用 Texture2D 初始化
	virtual bool					init(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
										 const cocos2d::CCSize & fontSize, const float32 interval);
	
	/// 使用 CCSpriteFrame 对象初始化
	virtual bool					init(cocos2d::CCSpriteFrame * spriteFrame,
										 const cocos2d::CCSize & fontSize, const float32 interval);
	
	/// 从 CCSpriteFrameCahce 中找到 CCSpriteFrame 对象初始化
	virtual bool					init(const char * spriteFrameName,
										 const cocos2d::CCSize & fontSize, const float32 interval);
	
	virtual void					setNumber(uint32 number);
	virtual void					setNumber(const std::string & strNumbers);
	virtual void					setIcon(cocos2d::CCSprite * icon);
	virtual void					setAlignType(AlignType alignType);
	virtual void 					setInterval(float32 interval);
	virtual void					setIconInterval(float32 interval);
	virtual float32					getNumberFontWidth();
	virtual void					layout();

	cocos2d::CCArray*				getNumbers(){return m_numbers;}

public: /** 重写基类的方法 **/

	virtual void					setColor(const cocos2d::ccColor3B& color3);
	virtual void					setOpacity(GLubyte opacity);
	
protected:
	
	/// 计算贴图的起点位置
	virtual float32					calculateBeginX();
	
	/// 创建显示的 CCSprite 对象
	cocos2d::CCSprite *				createSprite(uint32 num);
	
protected:
	cocos2d::CCSprite *				m_icon;
	cocos2d::CCSet *				m_caches;
	cocos2d::CCArray *				m_numbers;
	cocos2d::CCPoint				m_offset;
	cocos2d::CCSize					m_fontSize;
	float32							m_interval;
	float32							m_iconInterval;				// Icon 与接下来第一个字符间的距离, 默认等于 0
	AlignType						m_alignType;
};

#endif /* defined(__AndroidaBooM__YHUISpriteNumber__) */


