//
//  YHNetMessageQueue.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-13.
//
//

#ifndef __cocos2d_x_Utils__YHNetMessageQueue__
#define __cocos2d_x_Utils__YHNetMessageQueue__

#include "YHTypes.h"
#include "net/pthreadcc/pthreadcc.h"

/**
 * 网络消息队列. 
 * 可以在不同的线程操作该队列.
 * @author Zhenyu Yao
 */
class YHNetMessageQueue : public cocos2d::CCObject
{
public:
	
	YHNetMessageQueue();
	virtual ~YHNetMessageQueue();

	/// 获得队列头成员
	virtual cocos2d::CCObject * firstObject();
	
	/// 添加成员到队列尾
	virtual void push(cocos2d::CCObject * obj);
	
	/// 从队首删除成员
	virtual void pop();
	
	/// 判断是否有成员
	virtual bool empty();
	
	/// 得到当前成员的数量
	virtual uint32 count();
	
private:
	
	MutualExclusion m_mutex;
	cocos2d::CCArray * m_queue;
};

#endif /* defined(__cocos2d_x_Utils__YHNetMessageQueue__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


