#ifndef __AndroidaBooM_YHTimer__
#define __AndroidaBooM_YHTimer__

#include "YHTypes.h"

/**
 * 计时器接口
 * @wangtiwei
 */
class YHITimer
{
public:
	
	/// 获得当前已经经过的时间
	virtual float32 getElapse() = 0;
	
	/// 检测计时器当前是否在运行
	virtual bool getRunning() = 0;
	
	/// 获取/设置计时间隔. 在设置 interval 值之后, 计时器将复位停止, 并且需要手动调用重新启动.
	virtual void setInterval(float32 interval) = 0;
	virtual float32 getInterval() = 0;
	
	/// 判断是否到达时间
	virtual bool isTimeOut() = 0;
	
	/// 更新计时器, 到达时间返回 YES, 否则返回 NO
	virtual bool updateTimer(float32 dt) = 0;
	
	/// 重新开始计时
	virtual void start() = 0;
	
	/// 重置计时器, 需要手动调用 start 或者 resume 才能启动计时器
	virtual void reset() = 0;
	
	/// 暂停计时器
	virtual void pause() = 0;
	
	/// 由于之前暂停, 继续计时器
	virtual void resume() = 0;
};

/**
 * 计时器
 * @wangtiwei
 */
class YHTimer : public cocos2d::CCObject, public YHITimer
{
public:
	
	/// 生成一个 YHTimer 对象
	static YHTimer * timer();
	
	/// 产生一个 YHTimer 对象
	static YHTimer * timerWithInterval(float32 interval);
	
public:
	virtual ~YHTimer();
	
	/// 初始化
	bool init();
	
	/// 初始化
	bool initWithInterval(float32 interval);
	
	/////重载函数
	virtual float32 getElapse() { assert(m_isActive); return m_elapse; }
	virtual bool getRunning() { assert(m_isActive); return m_running; }
	virtual void setInterval(float32 interval) { assert(m_isActive); m_interval = interval;reset(); }
	virtual float32 getInterval() { assert(m_isActive); return m_interval; }
	virtual bool isTimeOut();
	virtual bool updateTimer(float32 dt);
	virtual void start();
	virtual void reset();
	virtual void pause();
	virtual void resume();
	
private:
	float32 m_interval;
	float32 m_elapse;
	bool m_running;
	bool m_isActive;
	
	friend class YHTimerCache;
};

/**
 * 计时器缓存类
 * @author Zhenyu Yao
 */
class YHTimerCache
{
public:
	
	/// 单例模式, 获得唯一的 YHTimerCache 对象
	static YHTimerCache * sharedTimerCache();
	
	/**
	 * 生成计时器, 生成前调用 YHTimer 的 init 方法
	 */
	YHTimer *			createTimer();
	
	/**
	 * 生成计时器, 生成前调用 YHTimer 的 initWithInterval 方法
	 */
	YHTimer *			createTimerWithInterval(float32 interval);
	
	/**
	 * createTimer 之后, 必须调用此方法销毁计时器
	 * @param pTimer 销毁的计时器
	 */
	void				destroyTimer(YHTimer * pTimer);
	
private:
	YHTimerCache();
	~YHTimerCache();
	
private:
	cocos2d::CCSet *	m_timerCache;
};

#endif /*__AndroidaBooM_YHTimer__*/


