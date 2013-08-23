//
//  YHSocketConnectManager.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-8.
//
//

#ifndef __cocos2d_x_Utils__YHSocketConnectHelper__
#define __cocos2d_x_Utils__YHSocketConnectHelper__

#include <string>
#include "YHTypes.h"
#include "net/socketcc/socketcc.h"

class YHSocketConnectManager;

/**
 * socket 连接线程
 * @author Zhenyu Yao
 */
class YHSocketConnectThread : public ThreadBase
{
public:
	
	YHSocketConnectThread(YHSocketConnectManager * manager, const std::string & address, int port, bool ipv6) :
	m_manager(NULL)
	{
		m_manager = manager;
		
		m_address.SetHostName(address.c_str(), ipv6);
		m_port = port;
	}
	
	~YHSocketConnectThread()
	{
	}
	
protected:
	
	virtual void *			Initialise();
	virtual void *			Execute();
	virtual void 			CleanUp();
	
private:
	
	YHSocketConnectManager * m_manager;
	IPAddress m_address;
	int m_port;
	
	friend YHSocketConnectManager;
};

/**
 * 管理 socket 的连接和断开. 每次成功连接之后, 再调用 connectedSocket 获得连接成功的 TCPClientSocket 对象.
 * 连接可以使用 connect 实现同步/异步连接远程终端的功能.
 * 如果已经连接上, 那么必须手动调用 close 方法关闭连接后, 再调用 connect 建立新的连接, 否则在连接状态调用 connect 方法无任何反应.
 * 删除该对象的时候, 必须记得设置 setConnectedCallback/setClosedCallback 设置回调对象和函数为 NULL
 * @author Zhenyu Yao
 */
class YHSocketConnectManager : public cocos2d::CCObject
{
public:
	
	YHSocketConnectManager() :
	m_socket(NULL),
	m_openTarget(NULL), m_openSelector(NULL),
	m_closeTarget(NULL), m_closeSelector(NULL),
	m_connectThread(NULL),
	m_hasConnected(false), m_isHappenClose(false)
	{
	}
	
	~YHSocketConnectManager()
	{
		CC_SAFE_DELETE(m_connectThread);
		CC_SAFE_DELETE(m_socket);
	}
	
	/// 获得链接的 TCPClientSocket 对象, 如果没有和远程终端连接, 返回 NULL
	TCPClientSocket * connectedSocket()
	{
		return m_socket;
	}

	/**
	 * 设置当调用 connect 后的回调函数
	 * @param target 调用回调函数的对象
	 * @param aSelector 回调对象调用的函数, 回调函数接收一个参数, 该参数是当前对象
	 */
	void setConnectedCallback(cocos2d::CCObject * target, cocos2d::SEL_CallFuncO aSelector)
	{
		m_mutex.Lock();
		m_openTarget = target;
		m_openSelector = aSelector;
		m_mutex.Unlock();
	}
	
	/**
	 * 设置当 socket 断开时的回调函数
	 * @param target 调用回调函数的对象
	 * @param aSelector 回调对象调用的函数, 回调函数接收一个参数, 该参数是当前对象
	 */
	void setClosedCallback(cocos2d::CCObject * target, cocos2d::SEL_CallFuncO aSelector)
	{
		m_mutex.Lock();
		m_closeTarget = target;
		m_closeSelector = aSelector;
		m_mutex.Unlock();
	}
	
	/**
	 * 连接远程终端主机, 该函数只能在游戏主线程中调用. 
	 * 在调用 connect 方法之后, 除非异常或者调用了 close 方法, 否则之后调用 connect 方法都不会有任何反应.
	 * @param address 远程终端 url 地址
	 * @param port 远程终端端口号
	 * @param asyn 是否异步连接, true 为异步连接, false 表示同步连接
	 */
	void connect(const std::string & address, int port, bool asyn = false, bool ipv6 = false);
	
	/// 关闭 socket. 如果 socket 没有连接, 将不发生任何事情.
	void close();
	
public: /* override functions */
	
	virtual void update(float dt);
	
private:
	
	/// setter socket
	void setSocket(TCPClientSocket * socket);
	
	/// 连接回调
	void invokeConnectedCallback();
	
	/// 关闭回调
	void invokeCloseCallback();
	
private:
	
	TCPClientSocket * m_socket;					// 连接远程终端的 socket
	
	YHSocketConnectThread * m_connectThread;	// 异步连接的线程
	
	MutualExclusion m_mutex;					// 当前对象的互斥量
	
	cocos2d::CCObject * m_openTarget;			// 无论连接成功还是失败的回调对象
	cocos2d::SEL_CallFuncO m_openSelector;		// 回调对象调用的函数
	cocos2d::CCObject * m_closeTarget;			// 关闭连接时的回调对象
	cocos2d::SEL_CallFuncO m_closeSelector;		// 回调对象调用的函数
	
	bool m_hasConnected;						// 是否连接到远程终端
	bool m_isHappenClose;						// 是否刚刚断开连接
	
	friend class YHSocketConnectThread;
};

#endif /* defined(__cocos2d_x_Utils__YHSocketConnectManager__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


