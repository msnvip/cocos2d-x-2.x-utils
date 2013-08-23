//
//  YHTestSocket.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-13.
//
//

#include "YHTestSocket.h"
#include "YHSocketConnectManager.h"
#include "YHSocketClient.h"
#include "YHHttpClient.h"
#include "YHGameLogicPackage.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define ADDRESS "192.168.1.136"
#define PORT 8000

/**
 * 测试 socket 的类
 * @author Zhenyu Yao
 */
class YHTestObject : public cocos2d::CCObject
{
	
public:
	
	YHTestObject()
	{
		m_client = new YHSocketClient();
		m_client->connect(ADDRESS, PORT, true);
		
		m_httpClient = new YHHttpClient();
		m_httpClient->setURL("http://192.168.1.136:8001/");
	}
	
	~YHTestObject()
	{
		CC_SAFE_RELEASE_NULL(m_client);
		CC_SAFE_RELEASE_NULL(m_httpClient);
	}
	
	void update(float dt)
	{
		static uint32 s_count = 0;
		static uint32 s_module = 0;
		static uint32 s_sendCnt = 0;
		static uint32 s_recvCnt = 0;
		
		if (s_count++ > 90)
		{
			s_count = 0;
			if (m_client->isConnected())
			{
				YHGameLogicPackage package = YHGameLogicPackage(s_module, s_module);
				++s_module;
				
				char str[] = "one piece";
				package.writeBytes(str, sizeof(str));
				package.writeBoolean(true);
				package.writeChar('a');
				package.writeUnsignedChar('b');
				package.writeShort(-1);
				package.writeUnsignedShort(-1);
				package.writeInt(-1);
				package.writeUnsignedInt(-1);
				package.writeFloat(1234.1234f);
				package.writeDouble(123456.123456);
//				m_client->send(package.getSendBytes());
				++s_sendCnt;
			}
			
			YHGameLogicPackage package = YHGameLogicPackage(s_sendCnt, s_sendCnt, false);
			char str[] = "one piece";
			package.writeBytes(str, sizeof(str));
			package.writeBoolean(true);
			package.writeChar('a');
			package.writeUnsignedChar('b');
			package.writeShort(-1);
			package.writeUnsignedShort(-1);
			package.writeInt(-1);
			package.writeUnsignedInt(-1);
			package.writeFloat(1234.1234f);
			package.writeDouble(123456.123456);
			m_httpClient->sendData(package.getSendBytes(), CCHttpRequest::kHttpPost);
		}
		
//		YHByteArray * bytes = m_client->recv();
		YHByteArray * bytes = m_httpClient->recvData();
		if (bytes != NULL)
		{
			++s_recvCnt;
			
			YHGameLogicPackage package = YHGameLogicPackage(bytes);
			YHByteArray tmp;
			package.readBytes(&tmp);
			CCLOG("readBytes: %s", tmp.getBuffer());
			CCLOG("readBoolean: %s", package.readBoolean() ? "true" : "false");
			CCLOG("readChar: %c", package.readChar());
			CCLOG("readUnsignedChar: %c", package.readUnsignedChar());
			CCLOG("readShort: %d", package.readShort());
			CCLOG("readUnsignedShort: %d", package.readUnsignedShort());
			CCLOG("readInt: %d", package.readInt());
			CCLOG("readUnsignedInt: %u", package.readUnsignedInt());
			CCLOG("readFloat: %f", package.readFloat());
			CCLOG("readDouble: %f", package.readDouble());
			
			bytes->release();
			
			CCLOG("---- sendCnt=%u, recvCnt=%u ----", s_sendCnt, s_recvCnt);
		}
	}
	
private:
	
	YHSocketClient * m_client;
	YHHttpClient * m_httpClient;
};

void testSocket()
{
	YHTestObject * obj = new YHTestObject();
	obj->autorelease();
	CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(obj, 0, false);
}












































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


