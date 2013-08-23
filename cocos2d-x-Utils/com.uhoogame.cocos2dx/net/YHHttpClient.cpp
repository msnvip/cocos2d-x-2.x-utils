//
//  YHHttpClient.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-15.
//
//

#include "YHHttpClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHHttpClient::YHHttpClient() :
m_queue(NULL), m_httpClient(NULL)
{
	m_queue = new CCArray();
	
	m_httpClient = CCHttpClient::getInstance();
}

YHHttpClient::~YHHttpClient()
{
	CC_SAFE_RELEASE_NULL(m_queue);
}

void YHHttpClient::sendData(YHByteArray * bytes, CCHttpRequest::HttpRequestType type)
{
	CCHttpRequest * request = new CCHttpRequest();
	request->setRequestType(type);
	request->setUrl(m_url.c_str());
	request->setRequestData((const char *)bytes->getBuffer(), bytes->readableBytes());
	request->setResponseCallback(this, httpresponse_selector(YHHttpClient::onResponseCallBack));
	m_httpClient->send(request);
	request->release();
}

YHByteArray * YHHttpClient::recvData()
{
	YHByteArray * bytes = NULL;
	if (m_queue->count() != 0)
	{
		bytes = (YHByteArray *)m_queue->objectAtIndex(0);
		bytes->retain();
		m_queue->removeObjectAtIndex(0);
	}
	
	return bytes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHHttpClient::onResponseCallBack(cocos2d::extension::CCHttpClient * client,
									  cocos2d::extension::CCHttpResponse * response)
{
	std::vector<char> * rawData = response->getResponseData();
	if (rawData->size() != 0)	// 这里之所以不用 isSuccess() 是因为又是接收到数据, 但是也报错, 所以按是否接收到数据判断是否接收成功
	{
		std::vector<char>::iterator beg = rawData->begin();
		std::vector<char>::iterator end = rawData->end();
		YHByteArray * bytes = new YHByteArray();
		bytes->init(rawData->size());
		for (; beg != end; ++beg)
		{
			bytes->writeChar(*beg);
		}
		m_queue->addObject(bytes);
		bytes->release();
	}
	else
	{
		CCLOG("Http error: %s", response->getErrorBuffer());
	}
}













































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


