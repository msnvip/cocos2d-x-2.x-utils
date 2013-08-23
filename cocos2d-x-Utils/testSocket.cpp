//
//  testSocket.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-16.
//
//

#include "testSocket.h"

#include "YHClient.h"
#include "YHByteArray.h"
#include "DataPacket.h"
#include "cocos2d.h"
#include "TestHttp.h"


static const char* serverIP = "192.168.1.120";
static const unsigned short serverPORT = 8888;

void testSocket()
{
	std::queue<YHClient*> clients;
	for (int i=0; i<50; ++i)
	{
		YHClient* client = new YHClient();
		client->setRemoteSocketServer(serverIP, serverPORT);
		client->connectServerAsynchronous((AsynCallBack)(&YHClient::connectCall));
		//client->connectServerSynchronous();
		
		clients.push(client);
		
	}
	
	for (int i=0; i<clients.size();)
	{
		YHClient* client = clients.front();
		//sleep(1);
		for (int i=0; i<1; ++i)
		{
			unsigned long pSize;
			uint8_t *pBuffer = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("Role.png", "rb", &pSize);
			
			uint8_t head[4] = {0xff,0xff,0xff,0xff};
			
			YHByteArray* bytes = new YHByteArray();
			bytes->writeBytes((char*)head, 4);
			uint8_t sizeBuf[4];
			FromInt(pSize, sizeBuf);
			bytes->writeBytes((char*)sizeBuf, 4);
			bytes->writeBytes((char*)pBuffer, pSize);
			client->sendBytes(bytes->m_buffer, bytes->m_capacity);
		}
		//sleep(5);
		//delete client;
		clients.pop();
	}
	
}

void testHttp()
{
	YHClient* client = new YHClient();
	TestHttp* testHttp = new TestHttp();
	client->setRemoteHttpServer(serverIP, 8090);
	for (int i=0; i<100; ++i)
	{
		client->sendHttpPost("user=wtw", testHttp, callfuncND_selector(TestHttp::httpCallBack));
		
	}
	
}