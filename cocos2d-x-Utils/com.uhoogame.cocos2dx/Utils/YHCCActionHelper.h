//
//  YHCCActionHelper.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-29.
//
//

#ifndef __AndroidaBooM__YHCCActionHelper__
#define __AndroidaBooM__YHCCActionHelper__

#include "cocos2d.h"

/**
 * 创建 CCAction 对象的辅助类
 * @author Zhenyu Yao
 */
class YHCCActionHelper
{
public:
	
	/**
	 * 创建循环播放的缩放动画
	 * @param initScale 初始大小
	 * @param finishScale 结束大小
	 * @param duration 1次循环的持续时间
	 * @param pNode 运行动画的节点
	 */
	static void		runNormalForeverScale(float initScale, float finishScale, float duration, cocos2d::CCNode * pNode);
	
	/**
	 * 间隔一段时间运行一次动画
	 * @param interval 间隔时间
	 * @param animation 运行的动画
	 * @param pSprite 运行动画的 CCSprite 对象
	 */
	static void		runIntervalForeverAnimation(float interval, cocos2d::CCAnimation * animation, cocos2d::CCSprite * pSprite);		
};

#endif /* defined(__AndroidaBooM__YHCCActionHelper__) */


