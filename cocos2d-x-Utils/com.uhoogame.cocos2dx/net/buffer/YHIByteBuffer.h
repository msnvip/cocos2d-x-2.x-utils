//
//  YHIByteBuffer.h
//  BSD Socket Client
//
//  Created by Zhenyu Yao on 13-7-2.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#ifndef BSD_Socket_Client_YHIByteBuffer_h
#define BSD_Socket_Client_YHIByteBuffer_h

/**
 * 字节序格式
 * @author Zhenyu Yao
 */
typedef enum YHByteOrder
{
	kByteOrder_BigEndian,			// 大端字节序列
	kByteOrder_LittleEndian,		// 小端字节序列
	
}YHByteOrder;

/**
 * YHIByteBuffer 提供连续可随机访问的字节序列数组操作. 
 * +----------------------------------------+----------------------------------------+----------------------------------------+
 * |                                        |                                        |                                        |
 * |      discardable bytes                 |           readable bytes               |            writeable bytes             |
 * |                                        |                                        |                                        |
 * +----------------------------------------+----------------------------------------+----------------------------------------+
 * |										|
 * 0				<=					readerIndex				<=				writerIndex				<=					capacity
 *
 * readable bytes (可读字节, 实际的内容)
 * 这一段是存放实际内容的地方. 任何 read 或者 skip 操作都将增加 readerIndex, 如果没有足够的内容可读, 将导致程序崩溃. 默认的 readerIndex 值为 0.
 *
 * writeable bytes (可写字节)
 * 这一段字节是没有定义并且需要被填充的空白区域. 任何 write 操作都将增加 writerIndex 的值. 如果没有足够的空间可写, 将导致程序崩溃, writeBytes 方法除外.
 * 默认的 writerIndex 值为 0.
 * 
 * discardable bytes
 * 这一段包含的是已经读过的字节. 最初, 该段的大小是 0. 通过调用 discardReadBytes() 方法将已经读过的字节转化成未使用的区域. 如下:
 * Before discardReadBytes()
 * +----------------------------------------+----------------------------------------+----------------------------------------+
 * |                                        |                                        |                                        |
 * |      discardable bytes                 |           readable bytes               |            writeable bytes             |
 * |                                        |                                        |                                        |
 * +----------------------------------------+----------------------------------------+----------------------------------------+
 * |										|
 * 0				<=					readerIndex				<=				writerIndex				<=					capacity
 *
 * After discardReadBytes()
 * +----------------------------------------+---------------------------------------------------------------------------------+
 * |                                        |                                        										  |
 * |           readable bytes               |            		writeable bytes (got more space)							  |
 * |                                        |																				  |
 * +----------------------------------------+---------------------------------------------------------------------------------+
 * |										|
 * readerIndex (0)			<=			writerIndex (decreased)								<=								capacity
 *
 * @author Zhenyu Yao
 */
class YHIByteBuffer
{
public:
	
	/**
	 * 获得 buufer 能够容纳字节的数量
	 */
	virtual unsigned int						getCapacity() const = 0;
	
	/**
	 * 调整 buffer 的大小. 
	 * 如果 newCapacity 小于当前的 capacity, 那么这个 buffer 的内容将被截断. 
	 * 如果 newCapacity 大于当前 capacity, 当前的 buffer 将增加 newCapacity - currentCapacity 长度的容量.
	 */
	virtual void								setCapacity(unsigned int newCapacity) = 0;
	
	/**
	 * 设置 readerIndex 和 writerIndex 的数值为 0
	 */
	virtual void								clear() = 0;
	
	/**
	 * 废弃 0 到 readerIndex 之间的字节
	 */
	virtual void								discardReadBytes() = 0;
	
	/**
	 * 判断 writerIndex - readerIndex 是否大于 0
	 */
	virtual bool								isReadabled() = 0;
	
	/**
	 * 判断 writerIndex - (readerIndex + size) 是否大于等于 0
	 */
	virtual bool								isReadabled(unsigned int size) = 0;
	
	/**
	 * 判断 capacity - writerIndex 是否大于 0
	 */
	virtual bool								isWriteable() = 0;
	
	/**
	 * 判断 capacity - (writerIndex + size) 是否大于等于 0
	 */
	virtual bool								isWriteable(unsigned int size) = 0;
	
	/**
	 * 返回这个 buffer 的字节序列
	 */
	virtual YHByteOrder							getOrder() = 0;
	
	/**
	 * 设置 buffer 存储字节序, 默认 Big Endian (大端) 字节序列. 
	 */
	virtual void								setOrder(YHByteOrder order) = 0;
	
	/**
	 * 还可读的字节序列, writerIndex - readerIndex
	 */
	virtual unsigned int						readableBytes() = 0;
	
	/**
	 * 还可写的字节序列, capacity - writerIndex
	 */
	virtual unsigned int						writeableBytes() = 0;
	
	/**
	 * 从当前 buffer 中读取 length 长度的字节数. 
	 * @param bytes 将数据读入的 YHIByteBuffer 对象.
	 * @param length 将要读取的字节长度, 0 表示读取所有的可用数据.
	 */
	virtual void								readBytes(YHIByteBuffer * bytes, unsigned int length) = 0;
	
	/**
	 * 从当前 buffer 中读取 length 长度字节数.
	 * @param chars 将数据读入的字节数组
	 * @param length 将要读取字节的长度, 0 表示读取所有可用的数据.
	 */
	virtual void								readBytes(char * chars, unsigned int length) = 0;
	
	/// 读取 bool
	virtual bool								readBoolean() = 0;
	
	/// 读取 char
	virtual char								readChar() = 0;
	
	/// 读取 unsigned char
	virtual unsigned char						readUnsignedChar() = 0;
	
	/// 读取 short
	virtual short								readShort() = 0;
	
	/// 读取 unsigned short
	virtual unsigned short						readUnsignedShort() = 0;
	
	/// 读取 int
	virtual int									readInt() = 0;
	
	/// 读取 unsigned int
	virtual unsigned int						readUnsignedInt() = 0;
	
	/// 读取 float
	virtual float								readFloat() = 0;
	
	/// 读取 double
	virtual double								readDouble() = 0;
	
	/**
	 * 将 bytes 中 length 长度的字节写入到当前 buffer 中. 如果可写的空间不够, 那么将自动扩充空间.
	 * @param bytes 提供写入数据的 YHIByteBuffer 对象.
	 * @param length 写入数据的长度.
	 */
	virtual void								writeBytes(YHIByteBuffer * bytes, unsigned int length) = 0;
	
	/**
	 * 将 chars 中 length 长度的字节写入到当前 buffer 中. 如果可写的空间不够, 那么将自动扩充空间.
	 * @param chars 提供写入数据的 YHIByteBuffer 对象.
	 * @param length 写入数据的长度.
	 */
	virtual void								writeBytes(char * chars, unsigned int length) = 0;
	
	/// 写入 bool
	virtual void								writeBoolean(bool value) = 0;
	
	/// 写入 char
	virtual void								writeChar(char value) = 0;
	
	/// 写入 unsigned char
	virtual void								writeUnsignedChar(unsigned char value) = 0;
	
	/// 写入 short
	virtual void								writeShort(short value) = 0;
	
	/// 写入 unsigned short
	virtual void								writeUnsignedShort(unsigned short value) = 0;
	
	/// 写入 int
	virtual void								writeInt(int value) = 0;
	
	/// 写入 unsigned int
	virtual void								writeUnsignedInt(unsigned int value) = 0;
	
	/// 写入 float
	virtual void								writeFloat(float value) = 0;
	
	/// 写入 double
	virtual void								writeDouble(double value) = 0;
	
	/* ---- set/get 将不给变 readerIndex 和 writerIndex 的值, 使用绝对 index 访问. ---- */
	
	/**
	 * 从当前 buffer 中读取数据到 bytes 中
	 * @param index 从当前 buffer 的 index 处读取数据
	 * @param bytes 被写入数据的 buffer
	 * @param len 数据的长度
	 * @param dstIndex 从 bytes 的 index 处写入数据
	 */
	virtual void								getBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex) = 0;
	
	/**
	 * 从当前 buffer 中读取数据到 chars 中
	 * @param index 从当前 buffer 的 index 处读取数据
	 * @param chars 被写入数据的 char 数组
	 * @param len 数据的长度
	 * @param dstIndex 从 chars 的 index 处写入数据
	 */
	virtual void								getBytes(unsigned int index, char * chars, unsigned int len, unsigned int dstIndex) = 0;
	
	/// 从 index 处读取 boolean
	virtual bool								getBoolean(unsigned int index) = 0;
	
	/// 从 index 处读取 char
	virtual char								getChar(unsigned int index) = 0;
	
	/// 从 index 处读取 unsigned char
	virtual unsigned char						getUnsignedChar(unsigned int index) = 0;
	
	/// 从 index 处读取 short
	virtual short								getShort(unsigned int index) = 0;
	
	/// 从 index 处读取 unsigned short
	virtual unsigned short						getUnsignedShort(unsigned int index) = 0;
	
	/// 从 index 处读取 int
	virtual int									getInt(unsigned int index) = 0;
	
	/// 从 index 处读取 unsigned int
	virtual unsigned int						getUnsignedInt(unsigned int index) = 0;
	
	/// 从 index 处读取 float
	virtual float								getFloat(unsigned int index) = 0;
	
	/// 从 index 处读取 double
	virtual double								getDouble(unsigned int index) = 0;
	
	/**
	 * 从 bytes 中写入数据到当前 buffer 中
	 * @param index 从当前 buffer 的 index 处写入数据
	 * @param bytes 读取数据的 buffer
	 * @param len 数据的长度
	 * @param dstIndex 从 bytes 的 index 处开始读取数据
	 */
	virtual void								setBytes(unsigned int index, YHIByteBuffer * bytes, unsigned int len, unsigned int dstIndex) = 0;
	
	/**
	 * 从 chars 中写入数据到当前 buffer 中
	 * @param index 从当前 buffer 的 index 处写入数据
	 * @param chars 读取数据的 chars 数组
	 * @param len 数据的长度
	 * @param dstIndex 从 chars 的 index 处开始读取数据
	 */
	virtual void								setBytes(unsigned int index, char * chars, unsigned len, unsigned int dstIndex) = 0;
	
	/// 从 index 处写入 bool
	virtual void								setBoolean(unsigned int index, bool value) = 0;
	
	/// 从 index 处写入 char
	virtual void								setChar(unsigned int index, char value) = 0;
	
	/// 从 index 处写入 unsigned char
	virtual void								setUnsignedChar(unsigned int index, unsigned char value) = 0;
	
	/// 从 index 处写入 short
	virtual void								setShort(unsigned int index, short value) = 0;
	
	/// 从 index 处写入 unsigned short
	virtual void 								setUnsignedShort(unsigned int index, unsigned short value) = 0;
	
	/// 从 index 处写入 int
	virtual void								setInt(unsigned int index, int value) = 0;
	
	/// 从 index 处写入 unsigned int
	virtual void								setUnsignedInt(unsigned int index, unsigned int value) = 0;
	
	/// 从 index 处写入 float
	virtual void								setFloat(unsigned int index, float value) = 0;
	
	/// 从 index 处写入 double
	virtual void								setDouble(unsigned int index, double value) = 0;
};

#endif















































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


