//
//  YHCommandParam.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-12.
//
//

#ifndef __cocos2d_x_Utils__YHCommandParam__
#define __cocos2d_x_Utils__YHCommandParam__

#include "YHByteArray.h"

/**
 * 为了减少内存的拷贝, 持有 YHByteArray 对象, 对 YHByteArray 的进一步封装, 使 YHByteArray 对象能直接从 loc 位置读取实际使用的数据.
 * 不保证线程安全, 不要将其添加到自动释放池中, 手动 release 生成的对象.
 * @author Zhenyu Yao
 */
class YHCommandParam : public cocos2d::CCObject, public YHIByteBuffer
{
public:
	
	YHCommandParam(YHByteArray * bytes, uint32 loc, uint32 len);
	virtual ~YHCommandParam();
	
	/// 读取数据的起始位
	uint32 getLoc() const
	{
		return m_loc;
	}
	
	/// 能够读取的最大长度
	uint32 getLen() const
	{
		return m_len;
	}
	
public: /* YHIByteBuffer */
	
	virtual unsigned int getCapacity() const
	{
		return m_len;
	}
	
	virtual void setCapacity(unsigned int newCapacity)
	{
		m_len = newCapacity;
	}
	
	virtual void clear()
	{
		CCLOG("YHCommandParam::clean invalid.");
		assert(false);
	}
	
	virtual void discardReadBytes()
	{
		CCLOG("YHCommandParam::discardReadBytes invalid.");
		assert(false);
	}
	
	virtual bool isReadabled()
	{
		return true;
	}
	
	virtual bool isReadabled(unsigned int size)
	{
		return size <= m_len;
	}
	
	virtual bool isWriteable()
	{
		return true;
	}
	
	virtual bool isWriteable(unsigned int size)
	{
		return size <= m_len;
	}
	
	virtual YHByteOrder getOrder()
	{
		return m_bytes->getOrder();
	}
	
	virtual void setOrder(YHByteOrder order)
	{
		m_bytes->setOrder(order);
	}
	
	virtual unsigned int readableBytes()
	{
		return m_len;
	}
	
	virtual unsigned int writeableBytes()
	{
		return m_len;
	}
	
	virtual void writeBytes(YHIByteBuffer * bytes, unsigned int len);
	virtual void writeBytes(char * chars, unsigned int len);
	virtual void writeBoolean(bool value);
	virtual void writeChar(char value);
	virtual void writeUnsignedChar(unsigned char value);
	virtual void writeShort(short value);
	virtual void writeUnsignedShort(unsigned short value);
	virtual void writeInt(int value);
	virtual void writeUnsignedInt(unsigned int value);
	virtual void writeFloat(float value);
	virtual void writeDouble(double value);

	virtual void readBytes(YHIByteBuffer * bytes, unsigned int len);
	virtual void readBytes(char * chars, unsigned int len);
	virtual bool readBoolean();
	virtual char readChar();
	virtual unsigned char readUnsignedChar();
	virtual short readShort();
	virtual unsigned short readUnsignedShort();
	virtual int readInt();
	virtual unsigned int readUnsignedInt();
	virtual float readFloat();
	virtual double readDouble();
	
	virtual void getBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex);
	virtual void getBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex);
	virtual bool getBoolean(unsigned int index);
	virtual char getChar(unsigned int index);
	virtual unsigned char getUnsignedChar(unsigned int index);
	virtual short getShort(unsigned int index);
	virtual unsigned short getUnsignedShort(unsigned int index);
	virtual int getInt(unsigned int index);
	virtual unsigned int getUnsignedInt(unsigned int index);
	virtual float getFloat(unsigned int index);
	virtual double getDouble(unsigned int index);
	
	virtual void setBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex);
	virtual void setBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex);
	virtual void setBoolean(unsigned int index, bool value);
	virtual void setChar(unsigned int index, char value);
	virtual void setUnsignedChar(unsigned int index, unsigned char value);
	virtual void setShort(unsigned int index, short value);
	virtual void setUnsignedShort(unsigned int index, unsigned short value);
	virtual void setInt(unsigned int index, int value);
	virtual void setUnsignedInt(unsigned int index, unsigned int value);
	virtual void setFloat(unsigned int index, float value);
	virtual void setDouble(unsigned int index, double value);
	
public: /* override functions */
	
	cocos2d::CCObject * autorelease()
	{
		// 严禁将该对象放入到自动释放池中
		assert(false);
		return NULL;
	}
	
private:
	
	uint32 m_loc;
	uint32 m_len;
	YHByteArray * m_bytes;
};

#endif /* defined(__cocos2d_x_Utils__YHCommandParam__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


