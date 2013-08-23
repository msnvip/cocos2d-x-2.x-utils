//
//  YHSocketRecvManager.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-14.
//
//

#ifndef __cocos2d_x_Utils__YHSocketRecvManager__
#define __cocos2d_x_Utils__YHSocketRecvManager__

#include "cocos2d.h"
#include "YHSocketConnectManager.h"
#include "net/buffer/YHByteArray.h"
#include "net/pthreadcc/pthreadcc.h"
#include "net/socketcc/socketcc.h"

class YHSocketRecvManager;

/**
 * socket 接收数据的线程
 * @author Zhenyu Yao
 */
class YHSocketRecvThread : public ThreadBase
{
public:
	
	YHSocketRecvThread(YHSocketRecvManager * manager);
	~YHSocketRecvThread();
	
public: /* override functions */
	
	void * Initialise();
	void * Execute();
	void CleanUp();
	
private:
	
	bool m_destroy;
	YHSocketRecvManager * m_manager;
	
	friend class YHSocketRecvManager;
};

/**
 * socket 的接收数据包管理器
 * @author Zhenyu Yao
 */
class YHSocketRecvManager : public cocos2d::CCObject
{

public:
	
	YHSocketRecvManager(YHSocketConnectManager * connectManager);
	virtual ~YHSocketRecvManager();
	
	/// 从队列中获得存入的数据, 返回的 YHByteArray 对象在使用完之后必须手动调用 release() 方法
	YHByteArray * recv();
	
private:
	
	cocos2d::CCArray * m_queue;						// 接收消息的队列
	MutualExclusion m_mutex;
	
	YHSocketConnectManager * m_connectManager;		// socket 连接管理器
	
	YHSocketRecvThread * m_thread;					// 接收线程
	
	friend class YHSocketRecvThread;
};

#endif /* defined(__cocos2d_x_Utils__YHSocketRecvManager__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


