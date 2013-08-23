//
//  YHGameLogicPackage.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-12.
//
//

#include "YHGameLogicPackage.h"

USING_NS_CC;

#define ADD_PARAM	uint32 loc = getLastParamLoc(); \
					uint32 len = sizeof(value); \
					YHCommandParam * param = new YHCommandParam(m_bytes, loc, len); \
					m_params->addObject(param); \
					CC_SAFE_RELEASE_NULL(param); \
					increaseParamCount()

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHGameLogicPackage::YHGameLogicPackage(uint16 moduleID, int32 functionID, bool packContentLength) :
m_moduleID(0), m_functionID(0), m_bytes(NULL), m_params(NULL)
{
	m_moduleID = moduleID;
	m_functionID = functionID;
	m_packContentLength = packContentLength;
	
	m_bytes = new YHByteArray();
	m_bytes->init();
	
	// 包头长度
	if (m_packContentLength)
	{
		m_bytes->writeUnsignedInt(0);
	}
	
	m_bytes->writeUnsignedShort(m_moduleID);
	m_bytes->writeInt(m_functionID);
	
	m_params = new CCArray();
	m_paramLenLoc = m_bytes->getWriterIndex();
	m_bytes->writeUnsignedChar(m_params->count());
}

YHGameLogicPackage::YHGameLogicPackage(YHByteArray * bytes)
{
	m_bytes = bytes;
	m_bytes->retain();
	
	m_params = new CCArray();
	
	// module ID
	m_moduleID = m_bytes->readUnsignedShort();
	
	// function ID
	m_functionID = m_bytes->readInt();
	
	// params
	m_paramLenLoc = m_bytes->getReaderIndex();
	uint8 paramsCount = m_bytes->readUnsignedChar();
	uint32 loc = m_bytes->getReaderIndex();
	for (uint8 i = 0; i < paramsCount; ++i)
	{
		uint32 len = m_bytes->getInt(loc);
		loc += sizeof(uint32);
		
		YHCommandParam * param = new YHCommandParam(m_bytes, loc, len);
		m_params->addObject(param);
		CC_SAFE_RELEASE_NULL(param);
		loc += len;
	}
}

YHGameLogicPackage::~YHGameLogicPackage()
{
	CC_SAFE_RELEASE_NULL(m_bytes);
	CC_SAFE_RELEASE_NULL(m_params);
}

void YHGameLogicPackage::writeBytes(void * buf, uint32 len)
{
	uint32 loc = getLastParamLoc();
	YHCommandParam * param = new YHCommandParam(m_bytes, loc, len);
	m_params->addObject(param);
	CC_SAFE_RELEASE_NULL(param);
	increaseParamCount();
	
	m_bytes->writeInt(len);
	m_bytes->writeBytes((char *)buf, len);
}

void YHGameLogicPackage::writeBoolean(bool value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeBoolean(value);
}

void YHGameLogicPackage::writeChar(int8 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeChar(value);
}

void YHGameLogicPackage::writeUnsignedChar(uint8 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeUnsignedChar(value);
}

void YHGameLogicPackage::writeShort(int16 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeShort(value);
}

void YHGameLogicPackage::writeUnsignedShort(uint16 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeUnsignedShort(value);
}

void YHGameLogicPackage::writeInt(int32 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeInt(value);
}

void YHGameLogicPackage::writeUnsignedInt(uint32 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeUnsignedInt(value);
}

void YHGameLogicPackage::writeFloat(float32 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeFloat(value);
}

void YHGameLogicPackage::writeDouble(float64 value)
{
	ADD_PARAM;
	m_bytes->writeInt(len);
	m_bytes->writeDouble(value);
}

void YHGameLogicPackage::readBytes(YHByteArray * bytes)
{
	int len = m_bytes->readInt();
	m_bytes->readBytes(bytes, len);
	m_params->removeObjectAtIndex(0);
}

bool YHGameLogicPackage::readBoolean()
{
	m_bytes->readInt();
	bool value = m_bytes->readBoolean();
	m_params->removeObjectAtIndex(0);
	return value;
}

int8 YHGameLogicPackage::readChar()
{
	m_bytes->readInt();
	int8 value = m_bytes->readChar();
	m_params->removeObjectAtIndex(0);
	return value;
}

uint8 YHGameLogicPackage::readUnsignedChar()
{
	m_bytes->readInt();
	uint8 value = m_bytes->readUnsignedChar();
	m_params->removeObjectAtIndex(0);
	return value;
}

int16 YHGameLogicPackage::readShort()
{
	m_bytes->readInt();
	int16 value = m_bytes->readShort();
	m_params->removeObjectAtIndex(0);
	return value;
}

uint16 YHGameLogicPackage::readUnsignedShort()
{
	m_bytes->readInt();
	uint16 value = m_bytes->readUnsignedShort();
	m_params->removeObjectAtIndex(0);
	return value;
}

int32 YHGameLogicPackage::readInt()
{
	m_bytes->readInt();
	int32 value = m_bytes->readInt();
	m_params->removeObjectAtIndex(0);
	return value;
}

uint32 YHGameLogicPackage::readUnsignedInt()
{
	m_bytes->readInt();
	uint32 value = m_bytes->readUnsignedInt();
	m_params->removeObjectAtIndex(0);
	return value;
}

float32 YHGameLogicPackage::readFloat()
{
	m_bytes->readInt();
	float32 value = m_bytes->readFloat();
	m_params->removeObjectAtIndex(0);
	return value;
}

float64 YHGameLogicPackage::readDouble()
{
	m_bytes->readInt();
	float64 value = m_bytes->readDouble();
	m_params->removeObjectAtIndex(0);
	return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

uint32 YHGameLogicPackage::getLastParamLoc()
{
	uint32 loc = m_packContentLength ? sizeof(int) : 0;
	loc += sizeof(m_moduleID) + sizeof(m_functionID) + sizeof(unsigned char);
	uint32 count = m_params->count();
	for (uint32 i = 0; i < count; ++i)
	{
		// 数据内容的长度参数
		loc += sizeof(int);
		
		// 实际数据内容
		YHCommandParam * param = (YHCommandParam *)m_params->objectAtIndex(i);
		loc += param->getLen();
	}
	return loc;
}

void YHGameLogicPackage::increaseParamCount()
{
	uint8 count = m_bytes->getUnsignedChar(m_paramLenLoc);
	m_bytes->setUnsignedChar(m_paramLenLoc, ++count);
}











































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


