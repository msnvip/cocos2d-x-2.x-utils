//
//  YHByteArray.cpp
//  BSD Socket Client
//
//  Created by Zhenyu Yao on 13-7-2.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#include "YHByteArray.h"
#include <assert.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
// Interface - YHIByteBuffer
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHByteArray::setCapacity(unsigned int newCapacity)
{
	if (m_buffer == NULL)
	{
		m_buffer = new YHMemory(newCapacity);
	}
	
	if (newCapacity > getCapacity())
	{
		m_buffer->enlarge(newCapacity - getCapacity());
	}
	else if (newCapacity < getCapacity())
	{
		m_buffer->realloc(newCapacity, true);
		
		if (m_writerIndex > newCapacity)
		{
			m_writerIndex = newCapacity;
		}
		
		if (m_readerIndex > m_writerIndex)
		{
			m_readerIndex = m_writerIndex;
		}
	}
}

void YHByteArray::discardReadBytes()
{
	unsigned len = m_writerIndex - m_readerIndex;
	unsigned char * data = getBuffer();
	memmove(data, data + m_readerIndex, len);
	m_readerIndex = 0;
	m_writerIndex = len;
}

void YHByteArray::readBytes(YHIByteBuffer * bytes, unsigned int length)
{
	assert(isReadabled(length));
	
	YHByteArray * byteArray = dynamic_cast<YHByteArray *>(bytes);
	if (byteArray != NULL)
	{	
		// 如果是 0, 则读取所有可读的数据
		if (length == 0)
		{
			length = readableBytes();
		}
		
		// 判断 bytes 是否可装那么多的字节, 如果 bytes 装不下 length 长度的字节, 则扩充 bytes 的 capacity.
		if (byteArray->writeableBytes() < length)
		{
			byteArray->setCapacity(byteArray->getCapacity() + (length - byteArray->writeableBytes()));
		}
		
		// 复制数据
		memmove(byteArray->getBuffer() + byteArray->m_writerIndex, getBuffer() + m_readerIndex, length);
		
		// 被写入的 YHByteArray 对象 writerIndex 增加
		byteArray->m_writerIndex += length;
		
		// 当前的 YHByteArray 对象 readerIndex 增加
		m_readerIndex += length;
	}
}

void YHByteArray::readBytes(char * chars, unsigned int length)
{
	assert(isReadabled(length));
	
	if (length == 0)
	{
		length = readableBytes();
	}
	
	memmove(chars, getBuffer() + m_readerIndex, length);
	
	m_readerIndex += length;
}

bool YHByteArray::readBoolean()
{
	assert(isReadabled(1));
	bool result = getBuffer()[m_readerIndex] != 0;
	++m_readerIndex;
	return result;
}

char YHByteArray::readChar()
{
	assert(isReadabled(1));
	char value = getBuffer()[m_readerIndex];
	++m_readerIndex;
	return value;
}

unsigned char YHByteArray::readUnsignedChar()
{
	assert(isReadabled(1));
	unsigned char value = getBuffer()[m_readerIndex];
	++m_readerIndex;
	return value;
}

short YHByteArray::readShort()
{
	assert(isReadabled(2));
	short value = 0;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		value = (unsigned int)data[m_readerIndex + 0] << 8 | (unsigned int)data[m_readerIndex + 1];
	}
	else
	{
		value = (unsigned int)data[m_readerIndex + 0] | (unsigned int)data[m_readerIndex + 1] << 8;
	}
	
	m_readerIndex += 2;

	return value;
}

unsigned short YHByteArray::readUnsignedShort()
{
	return readShort();
}

int YHByteArray::readInt()
{
	assert(isReadabled(4));
	
	int value = 0;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		value = (unsigned int)data[m_readerIndex + 0] << 24
				| (unsigned int)data[m_readerIndex + 1] << 16
				| (unsigned int)data[m_readerIndex + 2] << 8
				| (unsigned int)data[m_readerIndex + 3];
	}
	else
	{
		value = (unsigned int)data[m_readerIndex + 0]
				| (unsigned int)data[m_readerIndex + 1] << 8
				| (unsigned int)data[m_readerIndex + 2] << 16
				| (unsigned int)data[m_readerIndex + 3] << 24;
	}
	
	m_readerIndex += 4;
	
	return value;
}

unsigned int YHByteArray::readUnsignedInt()
{
	return readInt();
}

float YHByteArray::readFloat()
{
	assert(isReadabled(4));
	
	float value = 0.0f;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		unsigned char * tmp = (unsigned char *)&value;
		memcpy(tmp + 3, data + m_readerIndex + 0, 1);
		memcpy(tmp + 2, data + m_readerIndex + 1, 1);
		memcpy(tmp + 1, data + m_readerIndex + 2, 1);
		memcpy(tmp + 0, data + m_readerIndex + 3, 1);
	}
	else
	{
		memcpy(&value, data + m_readerIndex, 4);
	}
	
	m_readerIndex += 4;
	
	return value;
}

double YHByteArray::readDouble()
{
	assert(isReadabled(8));
	
	double value = 0.0;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		unsigned char * tmp = (unsigned char *)&value;
		memcpy(tmp + 7, data + m_readerIndex + 0, 1);
		memcpy(tmp + 6, data + m_readerIndex + 1, 1);
		memcpy(tmp + 5, data + m_readerIndex + 2, 1);
		memcpy(tmp + 4, data + m_readerIndex + 3, 1);
		memcpy(tmp + 3, data + m_readerIndex + 4, 1);
		memcpy(tmp + 2, data + m_readerIndex + 5, 1);
		memcpy(tmp + 1, data + m_readerIndex + 6, 1);
		memcpy(tmp + 0, data + m_readerIndex + 7, 1);
	}
	else
	{
		memcpy(&value, data + m_readerIndex, 8);
	}
	
	m_readerIndex += 8;
	
	return value;
}

void YHByteArray::writeBytes(YHIByteBuffer * bytes, unsigned int length)
{
	checkCapacity(length);
	YHByteArray * byteArray = dynamic_cast<YHByteArray *>(bytes);
	if (byteArray != NULL)
	{
		bytes->readBytes(this, length);
	}
}

void YHByteArray::writeBytes(char * chars, unsigned int length)
{
	checkCapacity(length);
	
	memmove(getBuffer() + m_writerIndex, chars, length);
	
	m_writerIndex += length;
}

void YHByteArray::writeBoolean(bool value)
{
	checkCapacity(sizeof(value));
	getBuffer()[m_writerIndex++] = value;
}

void YHByteArray::writeChar(char value)
{
	checkCapacity(sizeof(value));
	getBuffer()[m_writerIndex++] = value;
}

void YHByteArray::writeUnsignedChar(unsigned char value)
{
	checkCapacity(sizeof(value));
	getBuffer()[m_writerIndex++] = value;
}

void YHByteArray::writeShort(short value)
{
	checkCapacity(sizeof(value));
	
	if (m_order == kByteOrder_BigEndian)
	{
		getBuffer()[m_writerIndex + 0] = value >> 8;
		getBuffer()[m_writerIndex + 1] = value;
	}
	else
	{
		getBuffer()[m_writerIndex + 0] = value;
		getBuffer()[m_writerIndex + 1] = value >> 8;
	}
	
	m_writerIndex += 2;
}

void YHByteArray::writeUnsignedShort(unsigned short value)
{
	writeShort(value);
}

void YHByteArray::writeInt(int value)
{
	checkCapacity(sizeof(value));
	
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		data[m_writerIndex + 0] = value >> 24;
		data[m_writerIndex + 1] = value >> 16;
		data[m_writerIndex + 2] = value >> 8;
		data[m_writerIndex + 3] = value;
	}
	else
	{
		data[m_writerIndex + 0] = value;
		data[m_writerIndex + 1] = value >> 8;
		data[m_writerIndex + 2] = value >> 16;
		data[m_writerIndex + 3] = value >> 24;
	}
	
	m_writerIndex += 4;
}

void YHByteArray::writeUnsignedInt(unsigned int value)
{
	writeInt(value);
}

void YHByteArray::writeFloat(float value)
{
	checkCapacity(sizeof(value));
	
	unsigned char tmp[4] = {0, };
	memcpy(tmp, &value, 4);
	
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		data[m_writerIndex + 0] = tmp[3];
		data[m_writerIndex + 1] = tmp[2];
		data[m_writerIndex + 2] = tmp[1];
		data[m_writerIndex + 3] = tmp[0];
	}
	else
	{
		data[m_writerIndex + 0] = tmp[0];
		data[m_writerIndex + 1] = tmp[1];
		data[m_writerIndex + 2] = tmp[2];
		data[m_writerIndex + 3] = tmp[3];
	}
	
	m_writerIndex += 4;
}

void YHByteArray::writeDouble(double value)
{
	checkCapacity(sizeof(value));
	
	unsigned char tmp[8] = {0, };
	memcpy(tmp, &value, 8);
	
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		data[m_writerIndex + 0] = tmp[7];
		data[m_writerIndex + 1] = tmp[6];
		data[m_writerIndex + 2] = tmp[5];
		data[m_writerIndex + 3] = tmp[4];
		data[m_writerIndex + 4] = tmp[3];
		data[m_writerIndex + 5] = tmp[2];
		data[m_writerIndex + 6] = tmp[1];
		data[m_writerIndex + 7] = tmp[0];
	}
	else
	{
		memcpy(data + m_writerIndex, tmp, 8);
	}
	
	m_writerIndex += 8;
}

void YHByteArray::getBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex)
{
	assert(index + len <= getCapacity());
	assert(dstIndex + len <= bytes->getCapacity());
	
	YHByteArray * byteArray = dynamic_cast<YHByteArray *>(bytes);
	if (byteArray != NULL)
	{
		memmove(byteArray->getBuffer() + dstIndex, getBuffer() + index, len);
	}
}

void YHByteArray::getBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex)
{
	assert(index + len <= getCapacity());
	
	memmove(chars + dstIndex, getBuffer() + index, len);
}

bool YHByteArray::getBoolean(unsigned int index)
{
	assert(index + sizeof(bool) <= getCapacity());
	
	bool value = 0;
	memmove(&value, getBuffer() + index, sizeof(bool));
	return value;
}

char YHByteArray::getChar(unsigned int index)
{
	assert(index + sizeof(char) <= getCapacity());
	
	char value = 0;
	memmove(&value, getBuffer() + index, sizeof(char));
	return value;
}

unsigned char YHByteArray::getUnsignedChar(unsigned int index)
{
	assert(index + sizeof(unsigned char) <= getCapacity());
	
	unsigned char value = 0;
	memmove(&value, getBuffer() + index, sizeof(unsigned char));
	return value;
}

short YHByteArray::getShort(unsigned int index)
{
	assert(index + sizeof(short) <= getCapacity());
	
	short value = 0;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		value = (unsigned short)(data[index + 0]) << 8 | (unsigned short)(data[index + 1]);
	}
	else
	{
		memmove(&value, data + index, sizeof(short));
	}
	return value;
}

unsigned short YHByteArray::getUnsignedShort(unsigned int index)
{
	return getShort(index);
}

int YHByteArray::getInt(unsigned int index)
{
	assert(index + sizeof(int) <= getCapacity());
	
	int value = 0;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		value = (unsigned int)(data[index + 0]) << 24
				| (unsigned int)(data[index + 1]) << 16
				| (unsigned int)(data[index + 2]) << 8
				| (unsigned int)(data[index + 3]);
	}
	else
	{
		memmove(&value, data + index, sizeof(int));
	}
	return value;
}

unsigned int YHByteArray::getUnsignedInt(unsigned int index)
{
	return getInt(index);
}

float YHByteArray::getFloat(unsigned int index)
{
	assert(index + sizeof(float) <= getCapacity());
	
	float value = 0;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		unsigned char tmp[4] = {0, };
		tmp[0] = data[index + 3];
		tmp[1] = data[index + 2];
		tmp[2] = data[index + 1];
		tmp[3] = data[index + 0];
		memmove(&value, tmp, 4);
	}
	else
	{
		memmove(&value, data + index, 4);
	}
	return value;
}

double YHByteArray::getDouble(unsigned int index)
{
	assert(index + sizeof(double) <= getCapacity());
	
	double value = 0;
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		unsigned char tmp[8] = {0, };
		tmp[0] = data[index + 7];
		tmp[1] = data[index + 6];
		tmp[2] = data[index + 5];
		tmp[3] = data[index + 4];
		tmp[4] = data[index + 3];
		tmp[5] = data[index + 2];
		tmp[6] = data[index + 1];
		tmp[7] = data[index + 0];
		memmove(&value, tmp, 8);
	}
	else
	{
		memmove(&value, data + index, 8);
	}
	return value;
}

void YHByteArray::setBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex)
{
	assert(index + len <= getCapacity());
	assert(dstIndex + len <= bytes->getCapacity());
	
	YHByteArray * byteArray = dynamic_cast<YHByteArray *>(bytes);
	if (byteArray != NULL)
	{
		memmove(getBuffer() + index, byteArray->getBuffer() + dstIndex, len);
	}
}

void YHByteArray::setBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex)
{
	assert(index + len <= getCapacity());
	
	memmove(getBuffer() + index, chars + dstIndex, len);
}

void YHByteArray::setBoolean(unsigned int index, bool value)
{
	assert(index + sizeof(bool) <= getCapacity());
	
	memmove(getBuffer() + index, &value, sizeof(bool));
}

void YHByteArray::setChar(unsigned int index, char value)
{
	assert(index + sizeof(char) <= getCapacity());
	
	memmove(getBuffer() + index, &value, sizeof(char));
}

void YHByteArray::setUnsignedChar(unsigned int index, unsigned char value)
{
	assert(index + sizeof(unsigned char) <= getCapacity());
	
	memmove(getBuffer() + index, &value, sizeof(unsigned char));
}

void YHByteArray::setShort(unsigned int index, short value)
{
	assert(index + sizeof(short) <= getCapacity());
	
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		data[index + 0] = value >> 8;
		data[index + 1] = value;
	}
	else
	{
		memmove(data + index, &value, sizeof(short));
	}
}

void YHByteArray::setUnsignedShort(unsigned int index, unsigned short value)
{
	setShort(index, value);
}

void YHByteArray::setInt(unsigned int index, int value)
{
	assert(index + sizeof(int) <= getCapacity());
	
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		data[index + 0] = value >> 24;
		data[index + 1] = value >> 16;
		data[index + 2] = value >> 8;
		data[index + 3] = value;
	}
	else
	{
		memmove(data + index, &value, sizeof(int));
	}
}

void YHByteArray::setUnsignedInt(unsigned int index, unsigned int value)
{
	setInt(index, value);
}

void YHByteArray::setFloat(unsigned int index, float value)
{
	assert(index + sizeof(float) <= getCapacity());
	
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		unsigned char tmp[4] = {0, };
		memmove(tmp, &value, 4);
		data[index + 0] = tmp[3];
		data[index + 1] = tmp[2];
		data[index + 2] = tmp[1];
		data[index + 3] = tmp[0];
	}
	else
	{
		memmove(data + index, &value, 4);
	}
}

void YHByteArray::setDouble(unsigned int index, double value)
{
	assert(index + 8 <= getCapacity());
	
	unsigned char * data = getBuffer();
	if (m_order == kByteOrder_BigEndian)
	{
		unsigned char tmp[8] = {0, };
		memmove(tmp, &value, 8);
		data[index + 0] = tmp[7];
		data[index + 1] = tmp[6];
		data[index + 2] = tmp[5];
		data[index + 3] = tmp[4];
		data[index + 4] = tmp[3];
		data[index + 5] = tmp[2];
		data[index + 6] = tmp[1];
		data[index + 7] = tmp[0];
	}
	else
	{
		memmove(data + index, &value, 8);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////////////////////////////////////////////////////////////

void YHByteArray::checkCapacity(unsigned int size)
{
	if (!isWriteable(size))
	{
		setCapacity(getCapacity() + size + MEMORY_DEFAULT_SIZE);
	}
}










































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


