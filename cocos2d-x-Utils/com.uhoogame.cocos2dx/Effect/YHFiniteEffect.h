
#ifndef __YHFiniteEffect_H__
#define __YHFiniteEffect_H__

#include "YHIFiniteEffect.h"
#include "Common/CommonUtils.h"

using namespace cocos2d;

/**
 * 默认限定特效播放的实现
 * @author Zhenyu Yao
 */
class YHDefaultFiniteEffect : public CCSprite, public YHIFiniteEffect
{
public: /** Create Functions **/
	YHDefaultFiniteEffect() : m_active(false) {}
	~YHDefaultFiniteEffect() { this->cleanup(); }
	
	CCSPRITE_CREATE_FUNCTIONS(YHDefaultFiniteEffect);
	
public: /* Override Functions */
	
	virtual void		setParent(CCNode* parent);
	
public: /** YHIFiniteEffect **/
	virtual bool		isActive() { return m_active; }
	virtual void		resetBasicParams();
	virtual void		reset(cocos2d::CCFiniteTimeAction * finiteAction);
	virtual void		reset(cocos2d::CCArray * actions, float duration);
	virtual void		reset(float duration);
	virtual void		reset();
	virtual void		reset(const InstantEffectInfo & info, const cocos2d::CCPoint & position);
	virtual void		autoRemoveFromParent();
	
protected:
	
	/// 动画播放结束回调函数
	virtual void		onFinishHandler();
	
private:
	bool				m_active;
};

#endif // __YHFiniteEffect_H__


