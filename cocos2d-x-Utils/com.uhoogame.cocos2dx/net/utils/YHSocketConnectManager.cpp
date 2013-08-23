//
//  YHSocketConnectManager.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-8.
//
//

#include "YHSocketConnectManager.h"

using namespace std;
USING_NS_CC;

#pragma mark - YHSocketConnectThread

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void * YHSocketConnectThread::Initialise()
{
	return NULL;
}

void * YHSocketConnectThread::Execute()
{
	m_manager->m_mutex.Lock();
	TCPClientSocket * socket = NULL;
	try
	{
		socket = new TCPClientSocket(m_address, m_port);
		m_manager->setSocket(socket);
	}
	catch (SocketException e)
	{
		delete socket;
		m_manager->setSocket(NULL);
		CCLOG("%s", (const char *)e);
	}
	m_manager->m_mutex.Unlock();
	
	return NULL;
}

void YHSocketConnectThread::CleanUp()
{
}

#pragma mark - YHSocketConnectManager

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHSocketConnectManager::connect(const std::string & aAddress, int port, bool asyn, bool ipv6)
{
	m_mutex.Lock();
	
	if (m_hasConnected)
	{
		return;
	}
	
	// 防止多次调用 connect 方法
	m_hasConnected = true;
	
	if (asyn)
	{
		m_connectThread = new YHSocketConnectThread(this, aAddress, port, ipv6);
		m_connectThread->LaunchThread();
		CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
	}
	else
	{
		TCPClientSocket * socket = NULL;
		try
		{
			IPAddress address;
			address.SetHostName(aAddress.c_str(), ipv6);
			socket = new TCPClientSocket(address, port);
			setSocket(socket);
		}
		catch (SocketException e)
		{
			delete socket;
			setSocket(NULL);
			CCLOG("%s", (const char *)e);
		}
		
		invokeConnectedCallback();
	}
	
	m_mutex.Unlock();
}

void YHSocketConnectManager::close()
{
	CC_SAFE_DELETE(m_connectThread);
	
	m_mutex.Lock();
	if (m_socket != NULL)
	{
		delete m_socket;
		setSocket(NULL);
	}
	m_mutex.Unlock();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHSocketConnectManager::update(float dt)
{
	// 连接上远程终端的处理
	if (m_connectThread != NULL && !m_connectThread->ThreadRunning())
	{
		CC_SAFE_DELETE(m_connectThread);
		invokeConnectedCallback();
	}
	
	// 关闭连接后的处理
	if (m_isHappenClose)
	{
		m_isHappenClose = false;
		invokeCloseCallback();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHSocketConnectManager::setSocket(TCPClientSocket * socket)
{
	m_socket = socket;
	
	if (m_socket == NULL)
	{
		if (m_hasConnected && !m_isHappenClose)
		{
			m_isHappenClose = true;
		}
		
		m_hasConnected = false;
	}
}

void YHSocketConnectManager::invokeConnectedCallback()
{
	if (m_openTarget != NULL && m_openSelector != NULL)
	{
		(m_openTarget->*m_openSelector)(this);
	}
}

void YHSocketConnectManager::invokeCloseCallback()
{
	if (m_closeTarget != NULL && m_closeSelector != NULL)
	{
		(m_closeTarget->*m_closeSelector)(this);
	}
}










































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


