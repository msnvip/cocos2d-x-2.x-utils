//
//  YHSocketSendManager.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-13.
//
//

#ifndef __cocos2d_x_Utils__YHSocketSendManager__
#define __cocos2d_x_Utils__YHSocketSendManager__

#include "cocos2d.h"
#include "YHNetMessageQueue.h"
#include "net/pthreadcc/pthreadcc.h"
#include "net/socketcc/socketcc.h"
#include "net/buffer/YHByteArray.h"

class YHSocketSendManager;
class YHSocketConnectManager;

/**
 * socket 发送线程
 * @author Zhenyu Yao
 */
class YHSocketSendThread : public ThreadBase
{
	
public:
	
	YHSocketSendThread(YHSocketSendManager * manager);
	virtual ~YHSocketSendThread();
	
public: /* override functions */
	
	void * Initialise();
	void * Execute();
	void CleanUp();
	
private:
	
	bool m_destroy;
	YHSocketSendManager * m_manager;
	
	friend class YHSocketSendManager;
};

/**
 * Socket 消息发送管理器
 * @author Zhenyu Yao
 */
class YHSocketSendManager : public cocos2d::CCObject
{
	
public:
	
	YHSocketSendManager(YHSocketConnectManager * connectManager);
	virtual ~YHSocketSendManager();
	
	/**
	 * 发送字节流
	 * @param bytes 发送的子节流
	 */
	void send(YHByteArray * bytes);
	
private:
	
	cocos2d::CCArray * m_queue;						// 存放消息的队列
	Condition m_condition;							// 条件互斥量
	
	YHSocketSendThread * m_thread;					// 发送信息的线程
	
	YHSocketConnectManager * m_connectManager;		// socket 链接管理器
	
	friend class YHSocketSendThread;
};

#endif /* defined(__cocos2d_x_Utils__YHSocketSendManager__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


