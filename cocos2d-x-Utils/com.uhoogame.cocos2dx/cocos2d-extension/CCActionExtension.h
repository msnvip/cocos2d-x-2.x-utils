//
//  CCActionExtension.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-7-15.
//
//

#ifndef __cocos2d_x_Utils__CCActionExtension__
#define __cocos2d_x_Utils__CCActionExtension__

#include "cocos2d.h"

using namespace cocos2d;

/**
 * AnchorPoint  相对坐标动画
 * @author Zhenyu Yao
 */
class CCAnchorPointBy : public CCActionInterval
{
public:
	
	/**
	 * 初始化
	 * @param duration 间隔时间
	 * @param endAnchorPoint 目标位置
	 * @return 初始化成功返回 true, 否则返回 false
	 */
	virtual bool initWithDuration(float duration, const CCPoint & deltaPoint);
	
	virtual CCObject * copyWithZone(CCZone * pZone);
	virtual void startWithTarget(CCNode * pTarget);
	virtual CCActionInterval * reverse();
	virtual void update(float time);
	
	/**
	 * 生成 CCAnchorPointTo 对象
	 * @param duration 持续时间
	 * @param endAnchorPoint 锚点的结束位置
	 * @return CCAnchorPointTo 对象
	 */
	static CCAnchorPointBy * create(float duration, const CCPoint & deltaPoint);
	
protected:
	
	CCPoint m_deltaAnchorPoint;
	CCPoint m_startAnchorPoint;
};

/**
 * CCAnchorPoint 绝对坐标动画
 * @author Zhenyu Yao
 */
class CCAnchorPointTo : public CCAnchorPointBy
{
public:
	
	/**
	 * 初始化
	 * @param duration 持续时间
	 * @param endPoint 终点位置
	 * @return 成功返回 true, 否则返回 false
	 */
	virtual bool initWithDuration(float duration, const CCPoint & endPoint);
	
	virtual CCObject * copyWithZone(CCZone * pZone);
	virtual void startWithTarget(CCNode * pTarget);
	
	/**
	 * 创建 CCAnchorPointTo 对象
	 * @param duration 持续时间
	 * @param endPoint 终点位置
	 * @return 返回 CCAnchorPointTo 对象
	 */
	static CCAnchorPointTo * create(float duration, const CCPoint & endPoint);
	
protected:
	
	CCPoint m_endAnchorPoint;
};


#endif /* defined(__cocos2d_x_Utils__CCActionExtension__) */















































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


