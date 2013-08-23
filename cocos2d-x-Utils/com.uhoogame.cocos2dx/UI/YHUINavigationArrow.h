#ifndef __AndroidaBooM__YHUINavigationArrow__
#define __AndroidaBooM__YHUINavigationArrow__

#include "YHTypes.h"

/**
 * 指引用户操作的箭头
 * @author wangtiwei
 */
class YHUINavigationArrow : public cocos2d::CCSprite
{
public:
	
	typedef enum ActionTag
	{
		kArrowAction_Move,
	}ActionTag;
	
	/// 方向, 指的是箭头相对于在 destRect 的位置
	typedef enum ArrowDirection
	{
		kArrowDirection_Left,		// 在 rect 左边
		kArrowDirection_Right,		// 在 rect 右边
		kArrowDirection_Top,		// 在 rect 上边
		kArrowDirection_Down,		// 在 rect 下边
	}ArrowDirection;
	
public:
	YHUINavigationArrow();
	
	/**
	 * 根据方向和要指向的矩形创建键头
	 */
	static YHUINavigationArrow* createWithDirectionAndDestRect(ArrowDirection direction, cocos2d::CCRect rect = cocos2d::CCRectZero);
	
	/**
	 * 初始化
	 * @param direction 方向
	 * @param rect 指向的矩形位置
	 */
	bool initWithDirectionAndDestRect(ArrowDirection direction, cocos2d::CCRect rect);
	
	////设置方向
	void setDirection(ArrowDirection direction);
	
	////设置目标矩形框
	void setDestRect(cocos2d::CCRect rect);
	
protected:
	
	////开始指引动作
	void startNav();
	
	///停止指引动作
	void stopNav();
	
	////更新
	void updateLayout();
	
private:
	
	///指引方向
	ArrowDirection m_arrowDirection;
	
	///要指向的目标矩形框
	cocos2d::CCRect m_destRect;
};

#endif /*__AndroidaBooM__YHUINavigationArrow__*/


