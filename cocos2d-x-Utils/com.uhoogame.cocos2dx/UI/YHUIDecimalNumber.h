//
//  YHUIDecimalNumber.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-25.
//
//

#ifndef __AndroidaBooM__YHUIDecimalNumber__
#define __AndroidaBooM__YHUIDecimalNumber__

#include "YHTypes.h"
#include "YHISpriteNumber.h"

class YHUISpriteNumber;

/**
 * 带有小数点数字显示, 小数点末尾的 0 将被忽略掉.
 * 显示规则例子, places = 2
 * 			0				0
 *			4				0.04
 *			40				0.4
 *			44				0.44
 *			400				4
 *			404				4.04
 *			440				4.4
 *			444				4.44
 * @author Zhenyu Yao
 */
class YHUIDecimalNumber : public YHISpriteNumber
{
public:
	
	/// 使用 CCTexture2D 对象生成
	static YHUIDecimalNumber *						create(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
														   const cocos2d::CCSize & fontSize, const float32 interval,
														   cocos2d::CCSprite *iconDot);
	
	/// 使用 CCSpriteFrame 对象生成
	static YHUIDecimalNumber *						create(cocos2d::CCSpriteFrame * spriteFrame,
														   const cocos2d::CCSize & fontSize, const float32 interval,
														   cocos2d::CCSprite * iconDot);
	
	/// 从 CCSpriteFrameName 中找到 spriteFrameName 对应的 CCSpriteFrame 对象生成
	static YHUIDecimalNumber *						create(const char * spriteFrameName,
														   const cocos2d::CCSize & fontSize, const float32 interval,
														   cocos2d::CCSprite * iconDot);
	
public:
	
	YHUIDecimalNumber() :
	m_integers(NULL),
	m_decimals(NULL),
	m_iconDot(NULL),
	m_fontSize(cocos2d::CCSizeZero),
	m_interval(0),
	m_alignType(kAlignType_Left),
	m_iconContentWidth(0),
	m_places(2)
	{};
	virtual ~YHUIDecimalNumber()
	{};
	
	/// 使用 CCTexture2D 对象初始化
	virtual bool							init(cocos2d::CCTexture2D * tex, const cocos2d::CCPoint & offset,
												 const cocos2d::CCSize & fontSize, const float32 interval,
												 cocos2d::CCSprite * iconDot);
	
	/// 使用 CCSpriteFrame 对象初始化
	virtual bool							init(cocos2d::CCSpriteFrame * spriteFrame,
												 const cocos2d::CCSize & fontSize, const float32 interval,
												 cocos2d::CCSprite * iconDot);
	
	/// 从 CCSpriteFrameName 中找到 spriteFrameName 对应的 CCSpriteFrame 对象初始化
	virtual bool							init(const char * spriteFrameName,
												 const cocos2d::CCSize & fontSize, const float32 interval,
												 cocos2d::CCSprite * iconDot);
	
	/// 设置显示小数的位数, 但是需要再次调用 setNumber 方法之后, 才会更新显示的数据, 否则不会更新显示
	virtual void							setPlaces(uint32 places);
	
public: /** 重写基类方法 **/
	
	virtual void							setColor(const cocos2d::ccColor3B& color3);
	virtual void							setOpacity(GLubyte opacity);

public:
	
	virtual void							setNumber(uint32 number);
	virtual void							setNumber(const std::string & strNumbers);
	virtual void							setIcon(cocos2d::CCSprite * icon);
	virtual void 							setAlignType(AlignType alignType);
	virtual void							setInterval(float32 interval);
	virtual void							setIconInterval(float32 iconInterval);
	virtual float32							getNumberFontWidth();
	virtual void							layout();
	
private:
	
	/**
	 * 获得整数部分字符串
	 * @param num 全部数字
	 * @return 整数部分字符串
	 */
	std::string								getIntegerString(uint32 num);
	
	/**
	 * 获得整数部分字符串
	 * @param strNumbers 全部数字
	 * @return 整数部分字符串
	 */
	std::string								getIntegerString(const std::string & strNumbers);
	
	/**
	 * 获得小数部分字符串
	 * @param num 全部数字
	 * @return 小数部分字符串
	 */
	std::string								getDecimalString(uint32 num);
	
	/**
	 * 获得小数部分字符串
	 * @param strNumbers 全部数字的字符串
	 * @return 小数部分字符串
	 */
	std::string								getDecimalString(const std::string & strNumbers);
	
protected:
	
	/// 判断是否存在小数
	bool									hasDecimals() const;
	
protected:
	
	YHUISpriteNumber *						m_integers;
	YHUISpriteNumber *						m_decimals;
	cocos2d::CCSprite *						m_iconDot;
	cocos2d::CCSize							m_fontSize;
	float32									m_interval;
	AlignType								m_alignType;
	float32									m_iconContentWidth;
	uint32									m_places;					// 显示小数点的位数, 默认是 2 位
};

#endif /* defined(__AndroidaBooM__YHUIDecimalNumber__) */


