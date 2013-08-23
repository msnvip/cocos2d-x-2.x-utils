//
//  YHSocketRecvManager.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-14.
//
//

#include "YHSocketRecvManager.h"

USING_NS_CC;

#pragma mark - YHSocketRecvThread

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHSocketRecvThread::YHSocketRecvThread(YHSocketRecvManager * manager) :
m_manager(NULL), m_destroy(false)
{
	m_manager = manager;
}

YHSocketRecvThread::~YHSocketRecvThread()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Override Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void * YHSocketRecvThread::Initialise()
{
	m_destroy = false;
	return NULL;
}

void * YHSocketRecvThread::Execute()
{
	bool loop = true;
	while (loop)
	{
		try
		{
			// 接收包头
			YHByteArray header;
			header.init(4);
			m_manager->m_connectManager->connectedSocket()->RecvData(header.getBuffer(), header.getCapacity(), MSG_WAITALL);
			
			uint32 size = header.getUnsignedInt(0);
			
			// 接收实际内容
			YHByteArray * content = new YHByteArray();
			content->init(size);
			m_manager->m_connectManager->connectedSocket()->RecvData(content->getBuffer(), size, MSG_WAITALL);
			content->setWriterIndex(size);
			
			// 将接收到的数据添加进队列
			m_manager->m_mutex.Lock();
			m_manager->m_queue->addObject(content);
			content->release();
			m_manager->m_mutex.Unlock();
		}
		catch (SocketException e)
		{
			m_destroy = true;
			
			m_manager->m_connectManager->close();
			
			m_manager->m_mutex.Lock();
			m_manager->m_queue->removeAllObjects();
			m_manager->m_mutex.Unlock();
			
			CCLOG("%s", (const char *)e);
		}
		catch (ThreadException e)
		{
			CCLOG("%s", (const char *)e);
		}
		
		if (m_destroy)
		{
			loop = false;
		}
	}
	
	return NULL;
}

void YHSocketRecvThread::CleanUp()
{
}

#pragma mark - YHSocketRecvManager

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHSocketRecvManager::YHSocketRecvManager(YHSocketConnectManager * connectManager) :
m_queue(NULL), m_connectManager(NULL), m_thread(NULL)
{
	m_queue = new CCArray();
	
	m_connectManager = connectManager;
	
	m_thread = new YHSocketRecvThread(this);
	m_thread->LaunchThread();
}

YHSocketRecvManager::~YHSocketRecvManager()
{
	m_thread->m_destroy = true;
	CC_SAFE_DELETE(m_thread);
	
	CC_SAFE_RELEASE_NULL(m_queue);
}

YHByteArray * YHSocketRecvManager::recv()
{
	if (m_mutex.TryLock())
	{
		YHByteArray * bytes = NULL;
		if (m_queue->count() != 0)
		{
			bytes = (YHByteArray *)m_queue->objectAtIndex(0);
			bytes->retain();
			m_queue->removeObjectAtIndex(0);
		}
		m_mutex.Unlock();
		
		return bytes;
	}
	
	return NULL;
}









































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


