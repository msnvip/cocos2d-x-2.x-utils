
#ifndef __YHIFiniteEffect_H__
#define __YHIFiniteEffect_H__

#include "cocos2d.h"
#include "Common/CommonUtils.h"

/**
 * 在限定时间内播放的特效的接口定义
 * @author Zhenyu Yao
 */
class YHIFiniteEffect
{
public:
	
	/**
	 * 判断是否是激活状态
	 */
	virtual bool		isActive() = 0;
	
	/**
	 * 基本参数初始化
	 */
	virtual void		resetBasicParams() = 0;
	
	/**
	 * 重置动画, 同时设定在 finiteAction 运行完毕后, 自动从舞台移除
	 * @param finiteAction 将会运行的动画
	 */
	virtual void		reset(cocos2d::CCFiniteTimeAction * finiteAction) = 0;
	
	/**
	 * 重置动画, 同时运行 actions 个动作, 设定在 duration 时间之后, 自动从舞台移除
	 * @param actions 将会同时运行的 action
	 * @param duration 动画的运行时间
	 */
	virtual void		reset(cocos2d::CCArray * actions, float duration) = 0;
	
	/**
	 * 重置动画, 将在 duration 时间之后, 自动从舞台移除
	 * @param duration 动画运行的时间
	 */
	virtual void		reset(float duration) = 0;
	
	/**
	 * 重置动画, 一般用于自定动画的情况, 自定义的动画编辑写在里面
	 */
	virtual void		reset() = 0;
	
	/**
	 * 重置动画
	 * @param info 动画信息
	 * @param position 初始位置
	 */
	virtual void		reset(const InstantEffectInfo & info, const cocos2d::CCPoint & position) = 0;
	
	/// 自动从父容器中移除
	virtual void		autoRemoveFromParent() = 0;
};

#endif // __YHIFiniteEffect_H__


