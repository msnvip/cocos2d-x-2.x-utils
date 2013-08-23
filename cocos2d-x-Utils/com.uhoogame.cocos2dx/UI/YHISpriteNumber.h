//
//  YHISpriteNumber.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-26.
//
//

#ifndef __AndroidaBooM__YHISpriteNumber__
#define __AndroidaBooM__YHISpriteNumber__

#include "YHTypes.h"

/**
 * 数字显示内容的接口
 * @author Zhenyu Yao
 */
class YHISpriteNumber : public cocos2d::CCSprite
{
public:
	
	/// 对齐方式
	typedef enum AlignType
	{
		kAlignType_Left,		// 左对齐, 默认左对齐
		kAlignType_Center,		// 居中
		kAlignType_Right,		// 右对齐
	}AlignType;
	
public:
	
	virtual ~YHISpriteNumber() { this->cleanup(); }
	
	/**
	 * 设置显示的数字
	 */
	virtual void				setNumber(uint32 number) = 0;
	
	/**
	 * 设置显示的数字, strNumbers 里面的字符串只能包含 0-9 的 ASCII 码
	 */
	virtual void				setNumber(const std::string & strNumbers) = 0;
	
	/**
	 * 设置显示的 Icon, 传入 NULL 的时候, 表示取消 Icon 显示图标
	 */
	virtual void				setIcon(cocos2d::CCSprite * icon) = 0;
	
	/**
	 * 设置对齐方式
	 */
	virtual void				setAlignType(AlignType alignType) = 0;
	
	/**
	 * 设置数字间间隔
	 */
	virtual void				setInterval(float32 interval) = 0;
	
	/**
	 * 设置 Icon 与数字间间隔
	 */
	virtual void				setIconInterval(float32 iconInterval) = 0;
	
	/**
	 * 获得显示内容的宽度
	 */
	virtual float32				getNumberFontWidth() = 0;
	
	/**
	 * 排列布局
	 */
	virtual void				layout() = 0;
	
};

#endif /* defined(__AndroidaBooM__YHISpriteNumber__) */


