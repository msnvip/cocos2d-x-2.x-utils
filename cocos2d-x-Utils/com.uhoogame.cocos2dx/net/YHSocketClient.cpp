//
//  YHSocketClient.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-13.
//
//

#include "YHSocketClient.h"

USING_NS_CC;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHSocketClient::YHSocketClient() :
m_connectManager(NULL), m_sendManager(NULL), m_recvManager(NULL),
m_openTarget(NULL), m_openSelector(NULL),
m_closeTarget(NULL), m_closeSelector(NULL)
{
	m_connectManager = new YHSocketConnectManager();
	m_connectManager->setConnectedCallback(this, callfuncO_selector(YHSocketClient::onConnectedHandler));
	m_connectManager->setClosedCallback(this, callfuncO_selector(YHSocketClient::onClosedHandler));
}

YHSocketClient::~YHSocketClient()
{
	m_connectManager->setConnectedCallback(NULL, NULL);
	m_connectManager->close();
	
	CC_SAFE_RELEASE_NULL(m_sendManager);
	CC_SAFE_RELEASE_NULL(m_recvManager);
	CC_SAFE_RELEASE_NULL(m_connectManager);
}

void YHSocketClient::setConnectedCallBack(cocos2d::CCObject * target, cocos2d::SEL_CallFuncO selector)
{
	m_openTarget = target;
	m_openSelector = selector;
}

void YHSocketClient::setCloseCallBack(cocos2d::CCObject *target, cocos2d::SEL_CallFuncO selector)
{
	m_closeTarget = target;
	m_closeSelector = selector;
}

void YHSocketClient::connect(const std::string & address, int port, bool asyn, bool ipv6)
{
	m_connectManager->connect(address, port, asyn, ipv6);
}

void YHSocketClient::close()
{
	m_connectManager->close();
}

void YHSocketClient::send(YHByteArray * bytes)
{
	if (m_sendManager != NULL)
	{
		m_sendManager->send(bytes);
	}
}

YHByteArray * YHSocketClient::recv()
{
	if (m_recvManager != NULL)
	{
		return m_recvManager->recv();
	}
	
	return NULL;
}

const std::string YHSocketClient::getRemoteName()
{
	try
	{
		if (m_connectManager->connectedSocket() == NULL)
		{
			return std::string("");
		}
		
		IPAddress & address = m_connectManager->connectedSocket()->RemoteIPAddress();
		return std::string(address.GetHostName());
	}
	catch (SocketException e)
	{
		CCLOG("%s", (const char *)e);
		return std::string("");
	}
}

int YHSocketClient::getRemotePort()
{
	try
	{
		if (m_connectManager->connectedSocket() == NULL)
		{
			return -1;
		}
		
		return m_connectManager->connectedSocket()->RemotePortNumber();
	}
	catch (SocketException e)
	{
		CCLOG("%s", (const char *)e);
		return -1;
	}
}

const std::string YHSocketClient::getLocalName()
{
	try
	{
		if (m_connectManager->connectedSocket() == NULL)
		{
			return std::string("");
		}
		
		IPAddress & address = m_connectManager->connectedSocket()->LocalIPAddress();
		return std::string(address.GetHostName());
	}
	catch (SocketException e)
	{
		CCLOG("%s", (const char *)e);
		return std::string("");
	}
}

int YHSocketClient::getLocalPort()
{
	try
	{
		if (m_connectManager->connectedSocket() == NULL)
		{
			return -1;
		}
		
		return m_connectManager->connectedSocket()->LocalPortNumber();
	}
	catch (SocketException e)
	{
		CCLOG("%s", (const char *)e);
		return -1;
	}
}

bool YHSocketClient::isConnected()
{
	return m_connectManager->connectedSocket() != NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHSocketClient::onConnectedHandler(cocos2d::CCObject * sender)
{
	if (isConnected())
	{
		m_sendManager = new YHSocketSendManager(m_connectManager);
		
		m_recvManager = new YHSocketRecvManager(m_connectManager);
	}
	
	if (m_openTarget != NULL && m_openSelector != NULL)
	{
		(m_openTarget->*m_openSelector)(this);
	}
}

void YHSocketClient::onClosedHandler(cocos2d::CCObject * sender)
{
	if (m_closeTarget != NULL && m_closeSelector != NULL)
	{
		(m_closeTarget->*m_closeSelector)(this);
	}
}






































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


