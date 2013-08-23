//
//  YHSocketSendManager.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-13.
//
//

#include "YHSocketSendManager.h"
#include "YHSocketConnectManager.h"

USING_NS_CC;

#pragma mark - YHSocketSendThread

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHSocketSendThread::YHSocketSendThread(YHSocketSendManager * manager) :
m_manager(NULL), m_destroy(false)
{
	m_manager = manager;
}

YHSocketSendThread::~YHSocketSendThread()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void * YHSocketSendThread::Initialise()
{
	m_destroy = false;
	return NULL;
}

void * YHSocketSendThread::Execute()
{
	bool loop = true;
	
	while(loop)
	{
		try
		{
			m_manager->m_condition.LockMutEx();
			
			// 如果没有消息等待发送, 则等待, 添加消息后, 该线程将被唤醒
			while (m_manager->m_queue->count() == 0)
			{
				m_manager->m_condition.Wait();
				
				if (m_destroy)
				{
					m_manager->m_condition.UnlockMutEx();
					return NULL;
				}
			}
			
			YHByteArray * bytes = (YHByteArray *)m_manager->m_queue->objectAtIndex(0);
			bytes->retain();
			m_manager->m_queue->removeObjectAtIndex(0);
			
			m_manager->m_condition.UnlockMutEx();
			
			// 阻塞, 将消息发送出去
			m_manager->m_connectManager->connectedSocket()->SendData(bytes->getBuffer(), bytes->readableBytes());
			bytes->release();
			
			if (m_destroy)
			{
				loop = false;
			}
		}
		catch (SocketException e)
		{
			m_manager->m_connectManager->close();
			
			m_manager->m_condition.LockMutEx();
			m_manager->m_queue->removeAllObjects();
			m_manager->m_condition.UnlockMutEx();
			
			CCLOG("%s", (const char *)e);
			loop = false;
		}
		catch (ThreadException e)
		{
			CCLOG("%s", (const char *)e);
		}
	}
	
	return NULL;
}

void YHSocketSendThread::CleanUp()
{
}

#pragma mark - YHSocketSendManager

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHSocketSendManager::YHSocketSendManager(YHSocketConnectManager * connectManager) :
m_queue(NULL), m_thread(NULL), m_connectManager(NULL)
{
	m_queue = new CCArray();
	
	m_connectManager = connectManager;
	
	m_thread = new YHSocketSendThread(this);
	m_thread->LaunchThread();
}

YHSocketSendManager::~YHSocketSendManager()
{
	m_condition.LockMutEx();
	m_condition.Signal();
	m_thread->m_destroy = true;
	m_condition.UnlockMutEx();
	CC_SAFE_DELETE(m_thread);
	
	m_condition.LockMutEx();
	CC_SAFE_RELEASE_NULL(m_queue);
	m_condition.UnlockMutEx();
}

void YHSocketSendManager::send(YHByteArray * bytes)
{
	m_condition.LockMutEx();
	
	if (m_connectManager->connectedSocket() != NULL)
	{
		m_queue->addObject(bytes);
		m_condition.Signal();
	}
	
	m_condition.UnlockMutEx();
}












































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


