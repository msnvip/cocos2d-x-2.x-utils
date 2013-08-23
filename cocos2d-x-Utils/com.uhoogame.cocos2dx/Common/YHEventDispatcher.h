//
//  YHEventDispatcher.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-13.
//
//

#ifndef __AndroidaBooM__YHEventDispatcher__
#define __AndroidaBooM__YHEventDispatcher__

#include <map>
#include <string>
#include <vector>

#include "YHTypes.h"

using namespace std;
using namespace cocos2d;

class YHEvent;
class YHEventListener;
class YHEventDispatcher;

/**
 * 事件对象
 * @author Zhenyu Yao
 */
class YHEvent : public YHObject
{
public:
	YHEvent(string & type);
	YHEvent(const string & type);
	virtual ~YHEvent() {}
	
	/// 事件类型
	string				getType() const { return m_type; }
	
	/// 派发事件的对象
	YHObject *			getTarget() const { return m_target; }
	
	/// 附件用户数据, 用户自定义, 不负责内存管理
	void *				getUserData() const { return m_userData; }
	void				setUserData(void * userData) { m_userData = userData; }
	
private:
	string					m_type;
	YHObject *				m_target;
	void *					m_userData;
	
	friend class YHEventDispatcher;
};

/**
 * 事件侦听器
 * @author Zhenyu Yao
 */
class YHEventListener : public YHObject
{
public:
	YHEventListener(cocos2d::CCObject * aListener, ListenerSelector aSelector) 
	{
		assert(aListener != NULL);
		listener = aListener;
		selector = aSelector;
	}
	
	~YHEventListener() 
	{
		CCLog("---- YHEventListener dealloc ----");
	};
	
private:
	cocos2d::CCObject *			listener;
	ListenerSelector			selector;
	
	friend class YHEventDispatcher;
};

/**
 * 事件派发器操作接口
 * @author Zhenyu Yao
 */
class YHIEventDispatcher
{
public:
	/**
	 * 添加事件侦听器. 对同一事件类型, 添加之前已经添加过的相同的侦听器对象和侦听调用函数, 将添加不进.
	 * 注意: 调用了 addEventListener 方法之后, 在 aListener 调用析构函数之前, 必须手动调用 removeEventListener 方法移除添加的侦听器, 否则程序会出现 bug 或者 crash.
	 * @param type 事件类型
	 * @param aListener 侦听对象
	 * @param aSelector 侦听对象调用的侦听函数
	 */
	virtual void addEventListener(const string & type, cocos2d::CCObject * aListener, ListenerSelector aSelector) = 0;

	/**
	 * 派发事件
	 * @param aEvent 派发的事件
	 */
	virtual void dispatchEvent(YHEvent * aEvent) = 0;

	/**
	 * 移除该事件的所有侦听器
	 * @param type 事件类型
	 */
	virtual void removeEventListener(const string & type) = 0;

	/**
	 * 从所有事件中移除侦听对象
	 * @param aListener 侦听对象
	 */
	virtual void removeEventListener(cocos2d::CCObject * aListener) = 0;

	/**
	 * 移除事件对应的侦听器
	 * @param type 事件类型
	 * @param aListener 侦听对象
	 */
	virtual void removeEventListener(const string & type, cocos2d::CCObject * aListener) = 0;

	/**
	 * 判断是否侦听了该事件
	 * @param type 事件类型 
	 * @return 有对象侦听该事件返回 true, 否则返回 false
	 */
	virtual bool hasEventListener(const string & type) = 0;
};

/**
 * 事件派发器
 * @author Zhenyu Yao
 */
class YHEventDispatcher : public YHObject, public YHIEventDispatcher
{
public:
	YHEventDispatcher();
	virtual ~YHEventDispatcher();
	
public: /** YHIEventDispatcher **/
	
	virtual void addEventListener(const string & type, cocos2d::CCObject * aListener, ListenerSelector aSelector);
	virtual void dispatchEvent(YHEvent * aEvent);
	virtual void removeEventListener(const string & type);
	virtual void removeEventListener(cocos2d::CCObject * aListener);
	virtual void removeEventListener(const string & type, cocos2d::CCObject * aListener);
	virtual bool hasEventListener(const string & type);
	
private:
	
	vector<multimap<string, YHEventListener *>::iterator>	findListeners(cocos2d::CCObject * listener);
	vector<multimap<string, YHEventListener *>::iterator>	findListeners(const string & type, cocos2d::CCObject * listener);
	void													deleteListeners(vector<multimap<string, YHEventListener *>::iterator> & delListeners);
	
private:

	multimap<string, YHEventListener *>						m_listeners;

};

/**
 * 默认事件派发器. 以单例模式返回唯一的实例, 让其他的类不用继承 YHEventDispatcher 也能派发事件, 非线程安全.
 * @author Zhenyu Yao
 */
class YHDefaultEventDispatcher : public YHEventDispatcher
{
public:
	static YHDefaultEventDispatcher * defaultEventDispatcher();
	
private:
	YHDefaultEventDispatcher() {}
	virtual ~YHDefaultEventDispatcher() {}
};

#endif /* defined(__AndroidaBooM__YHEventDispatcher__) */


