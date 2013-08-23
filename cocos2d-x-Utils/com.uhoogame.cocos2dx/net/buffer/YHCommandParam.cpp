//
//  YHCommandParam.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-12.
//
//

#include "YHCommandParam.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

YHCommandParam::YHCommandParam(YHByteArray * bytes, uint32 loc, uint32 len)
{
	m_bytes = bytes;
	m_bytes->retain();
	
	m_loc = loc;
	m_len = len;
}

YHCommandParam::~YHCommandParam()
{
	CC_SAFE_RELEASE_NULL(m_bytes);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface - YHIByteBuffer
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHCommandParam::writeBytes(YHIByteBuffer *bytes, unsigned int len)
{
	assert(m_len >= len);
	m_bytes->setBytes(m_loc, bytes, len, 0);
}

void YHCommandParam::writeBytes(char * chars, unsigned int len)
{
	assert(m_len >= len);
	m_bytes->setBytes(m_loc, chars, len, 0);
}

void YHCommandParam::writeBoolean(bool value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setBoolean(m_loc, value);
}

void YHCommandParam::writeChar(char value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setChar(m_loc, value);
}

void YHCommandParam::writeUnsignedChar(unsigned char value)
{
	assert(m_len >= sizeof(unsigned char));
	m_bytes->setUnsignedChar(m_loc, value);
}

void YHCommandParam::writeShort(short value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setShort(m_loc, value);
}

void YHCommandParam::writeUnsignedShort(unsigned short value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setUnsignedShort(m_loc, value);
}

void YHCommandParam::writeInt(int value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setInt(m_loc, value);
}

void YHCommandParam::writeUnsignedInt(unsigned int value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setUnsignedInt(m_loc, value);
}

void YHCommandParam::writeFloat(float value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setFloat(m_loc, value);
}

void YHCommandParam::writeDouble(double value)
{
	assert(m_len >= sizeof(value));
	m_bytes->setDouble(m_loc, value);
}

void YHCommandParam::readBytes(YHIByteBuffer * bytes, unsigned int len)
{
	assert(m_len >= len);
	m_bytes->getBytes(m_loc, bytes, len, 0);
}

void YHCommandParam::readBytes(char * chars, unsigned int len)
{
	assert(m_len >= len);
	m_bytes->getBytes(m_loc, chars, len, 0);
}

bool YHCommandParam::readBoolean()
{
	return m_bytes->getBoolean(m_loc);
}

char YHCommandParam::readChar()
{
	return m_bytes->getChar(m_loc);
}

unsigned char YHCommandParam::readUnsignedChar()
{
	return m_bytes->getUnsignedChar(m_loc);
}

short YHCommandParam::readShort()
{
	return m_bytes->getShort(m_loc);
}

unsigned short YHCommandParam::readUnsignedShort()
{
	return m_bytes->getUnsignedShort(m_loc);
}

int YHCommandParam::readInt()
{
	return m_bytes->getInt(m_loc);
}

unsigned int YHCommandParam::readUnsignedInt()
{
	return m_bytes->getUnsignedInt(m_loc);
}

float YHCommandParam::readFloat()
{
	return m_bytes->getFloat(m_loc);
}

double YHCommandParam::readDouble()
{
	return m_bytes->getDouble(m_loc);
}

void YHCommandParam::getBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex)
{
	m_bytes->getBytes(index, bytes, len, dstIndex);
}

void YHCommandParam::getBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex)
{
	m_bytes->getBytes(index, chars, len, dstIndex);
}

bool YHCommandParam::getBoolean(unsigned int index)
{
	return m_bytes->getBoolean(index);
}

char YHCommandParam::getChar(unsigned int index)
{
	return m_bytes->getChar(index);
}

unsigned char YHCommandParam::getUnsignedChar(unsigned int index)
{
	return m_bytes->getUnsignedChar(index);
}

short YHCommandParam::getShort(unsigned int index)
{
	return m_bytes->getShort(index);
}

unsigned short YHCommandParam::getUnsignedShort(unsigned int index)
{
	return m_bytes->getUnsignedShort(index);
}

int YHCommandParam::getInt(unsigned int index)
{
	return m_bytes->getInt(index);
}

unsigned int YHCommandParam::getUnsignedInt(unsigned int index)
{
	return m_bytes->getUnsignedInt(index);
}

float YHCommandParam::getFloat(unsigned int index)
{
	return m_bytes->getFloat(index);
}

double YHCommandParam::getDouble(unsigned int index)
{
	return m_bytes->getDouble(index);
}

void YHCommandParam::setBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex)
{
	m_bytes->setBytes(index, bytes, len, dstIndex);
}

void YHCommandParam::setBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex)
{
	m_bytes->setBytes(index, chars, len, dstIndex);
}

void YHCommandParam::setBoolean(unsigned int index, bool value)
{
	m_bytes->setBoolean(index, value);
}

void YHCommandParam::setChar(unsigned int index, char value)
{
	m_bytes->setChar(index, value);
}

void YHCommandParam::setUnsignedChar(unsigned int index, unsigned char value)
{
	m_bytes->setUnsignedChar(index, value);
}

void YHCommandParam::setShort(unsigned int index, short value)
{
	m_bytes->setShort(index, value);
}

void YHCommandParam::setUnsignedShort(unsigned int index, unsigned short value)
{
	m_bytes->setUnsignedShort(index, value);
}

void YHCommandParam::setInt(unsigned int index, int value)
{
	m_bytes->setInt(index, value);
}

void YHCommandParam::setUnsignedInt(unsigned int index, unsigned int value)
{
	m_bytes->setUnsignedInt(index, value);
}

void YHCommandParam::setFloat(unsigned int index, float value)
{
	m_bytes->setFloat(index, value);
}

void YHCommandParam::setDouble(unsigned int index, double value)
{
	m_bytes->setDouble(index, value);
}









































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


