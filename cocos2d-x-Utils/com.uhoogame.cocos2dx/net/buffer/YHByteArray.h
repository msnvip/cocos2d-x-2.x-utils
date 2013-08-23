//
//  YHByteArray.h
//  BSD Socket Client
//
//  Created by Zhenyu Yao on 13-7-2.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#ifndef __BSD_Socket_Client__YHByteArray__
#define __BSD_Socket_Client__YHByteArray__

#include "YHIByteBuffer.h"
#include "YHAllocator.h"

/**
 * YHByteArray 对 YHIByteBuffer 的实现, order 默认为 BigEndian
 * 不保证线程安全, 不要将其添加到自动释放池中, 手动 release 生成的对象. 
 * @author Zhenyu Yao
 */
class YHByteArray : public cocos2d::CCObject, public YHIByteBuffer
{
	
public:
	
	YHByteArray()
	{
		m_writerIndex = 0;
		m_readerIndex = 0;
		m_order = kByteOrder_BigEndian;
		m_buffer = NULL;
	}
	
	~YHByteArray()
	{
		CC_SAFE_RELEASE_NULL(m_buffer);
	}
	
	/// 初始化
	virtual bool init(unsigned int size = MEMORY_DEFAULT_SIZE)
	{
		setCapacity(size);
		return true;
	}
	
	virtual unsigned char * getBuffer()
	{
		return m_buffer == NULL ? NULL : (unsigned char *)m_buffer->getData();
	}
	
	virtual unsigned int getReaderIndex()
	{
		return m_readerIndex;
	}
	
	virtual void setReaderIndex(unsigned int index)
	{
		assert(index >= 0);
		assert(index <= m_writerIndex);
		m_readerIndex = index;
	}
	
	// getter/setter writerIndex
	virtual unsigned int getWriterIndex()
	{
		return m_writerIndex;
	}
	
	virtual void setWriterIndex(unsigned int index)
	{
		assert(index >= m_readerIndex);
		assert(index <= getCapacity());
		m_writerIndex = index;
	}
	
public: /* 实现 YHIByteBuffer 接口 */
	
	unsigned int getCapacity() const
	{
		return m_buffer != NULL ? m_buffer->getLength() : 0;
	}
	
	void setCapacity(unsigned int newCapacity);
	
	void clear()
	{
		m_writerIndex = 0;
		m_readerIndex = 0;
	}
	
	void discardReadBytes();
	
	bool isReadabled()
	{
		return m_writerIndex > m_readerIndex;
	}
	
	bool isReadabled(unsigned int size)
	{
		return m_writerIndex >= m_readerIndex + size;
	}
	
	bool isWriteable()
	{
		return getCapacity() > m_writerIndex;
	}
	
	bool isWriteable(unsigned int size)
	{
		return getCapacity() >= m_writerIndex + size;
	}
	
	YHByteOrder getOrder()
	{
		return m_order;
	}
	
	void setOrder(YHByteOrder order)
	{
		m_order = order;
	}
	
	unsigned int readableBytes()
	{
		if (isReadabled())
		{
			return m_writerIndex - m_readerIndex;
		}
		
		return 0;
	}
	
	unsigned int writeableBytes()
	{
		if (isWriteable())
		{
			return getCapacity() - m_writerIndex;
		}
		
		return 0;
	}
	
	void readBytes(YHIByteBuffer * bytes, unsigned int length);
	void readBytes(char * chars, unsigned int length);
	bool readBoolean();
	char readChar();
	unsigned char readUnsignedChar();
	short readShort();
	unsigned short readUnsignedShort();
	int readInt();
	unsigned int readUnsignedInt();
	float readFloat();
	double readDouble();
	
	void writeBytes(YHIByteBuffer * bytes, unsigned int length);
	void writeBytes(char * chars, unsigned int length);
	void writeBoolean(bool value);
	void writeChar(char value);
	void writeUnsignedChar(unsigned char value);
	void writeShort(short value);
	void writeUnsignedShort(unsigned short value);
	void writeInt(int value);
	void writeUnsignedInt(unsigned int value);
	void writeFloat(float value);
	void writeDouble(double value);
	
	void getBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex);
	void getBytes(unsigned int index, char * chars, unsigned int len, unsigned int detIndex);
	bool getBoolean(unsigned int index);
	char getChar(unsigned int index);
	unsigned char getUnsignedChar(unsigned int index);
	short getShort(unsigned int index);
	unsigned short getUnsignedShort(unsigned int index);
	int getInt(unsigned int index);
	unsigned int getUnsignedInt(unsigned int index);
	float getFloat(unsigned int index);
	double getDouble(unsigned int index);
	
	void setBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex);
	void setBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex);
	void setBoolean(unsigned int index, bool value);
	void setChar(unsigned int index, char value);
	void setUnsignedChar(unsigned int index, unsigned char value);
	void setShort(unsigned int index, short value);
	void setUnsignedShort(unsigned int index, unsigned short value);
	void setInt(unsigned int index, int value);
	void setUnsignedInt(unsigned int index, unsigned int value);
	void setFloat(unsigned int index, float value);
	void setDouble(unsigned int index, double value);
	
public: /* override functions */
	
	cocos2d::CCObject * autorelease()
	{
		// 严禁将该对象添加到自动释放池
		assert(false);
		return NULL;
	}
	
private:
	
	/**
	 * 检测当前的容量是否够用, 如果不够, 则扩展当前容量
	 * @param size 待使用的容量
	 */
	void checkCapacity(unsigned int size);
	
private:
	
	unsigned int			m_writerIndex;
	unsigned int			m_readerIndex;
	YHByteOrder				m_order;
	YHMemory *				m_buffer;
};

#endif /* defined(__BSD_Socket_Client__YHByteArray__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


