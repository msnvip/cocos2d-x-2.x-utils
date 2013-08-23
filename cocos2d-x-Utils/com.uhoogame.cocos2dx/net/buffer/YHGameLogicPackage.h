//
//  YHGameLogicPackage.h
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-12.
//
//

#ifndef __cocos2d_x_Utils__YHGameLogicPackage__
#define __cocos2d_x_Utils__YHGameLogicPackage__

#include "YHTypes.h"
#include "YHCommandParam.h"

/**
 * 游戏逻辑使用数据包. writeXXX 的操作将会添加一个 YHCommandParam 对象, readXXX 的操作将会删除一个 YHCommandParam 对象.
 * writeXXX/readXXX 的操作顺序是对应的. 例如: 如果首先调用 writeBoolean, 那么对应的也必须首先调用  readBoolean 读取对应的数值.
 * 数据包传输格式为:
 * 			unsigned short -> module ID: 模块号 ID
 *			int -> function ID: 模块下对应的功能号 ID
 *			unsigned char 功能参数个数;
 *				- int 参数0 数据长度;
 *				- 参数0 实际内容;
 * @author Zhenyu Yao
 */
class YHGameLogicPackage : public cocos2d::CCObject
{
	
public:
	
	/**
	 * 发送数据时调用的构造函数
	 * @param moduleID 模块ID
	 * @param functionID 功能ID
	 * @param packContentLength 是否需要包装包内容的长度
	 */
	YHGameLogicPackage(uint16 moduleID, int32 functionID, bool packContentLength = true);
	
	/**
	 * 接收数据时调用的构造函数
	 * @param bytes 接收到的数据流
	 */
	YHGameLogicPackage(YHByteArray * bytes);
	
	virtual ~YHGameLogicPackage();
	
	/// 获得模块的 ID 号
	uint16 getModuleID() const
	{
		return m_moduleID;
	}
	
	/// 获得功能的 ID 号
	int32 getFunctionID() const
	{
		return m_functionID;
	}
	
	/// 发送到网络的数据流, 包括包长度域, 返回的 YHByteArray 对象直接压入 socket 发送队列
	YHByteArray * getSendBytes() const
	{
		if (m_packContentLength)
		{
			m_bytes->setUnsignedInt(0, m_bytes->readableBytes() - 4);
		}
		return m_bytes;
	}
	
	/// 获得 index 指定的 YHCommandParam 对象
	YHCommandParam * getParamAtIndex(uint32 index)
	{
		return (YHCommandParam *)m_params->objectAtIndex(index);
	}
	
	/// 添加数据流类型的参数, 操作后参数个数 +1
	void writeBytes(void * buf, uint32 len);
	
	/// 添加 boolean 类型的参数, 操作后参数个数 +1
	void writeBoolean(bool value);
	
	/// 添加 char 类型的参数, 操作后参数个数 +1
	void writeChar(int8 value);
	
	/// 添加 unsigned char 类型的参数, 操作后参数个数 +1
	void writeUnsignedChar(uint8 value);
	
	/// 添加 short 类型的参数, 操作后参数个数 +1
	void writeShort(int16 value);
	
	/// 添加 unsigned short 类型的参数, 操作后参数个数 +1
	void writeUnsignedShort(uint16 value);
	
	/// 添加 int 类型参数, 操作后参数个数 +1
	void writeInt(int32 value);
	
	/// 添加 unsigned int 类型参数, 操作后参数个数 +1
	void writeUnsignedInt(uint32 value);
	
	/// 添加 float 类型参数, 操作后参数个数 +1
	void writeFloat(float32 value);
	
	/// 添加 double 类型参数, 操作后参数个数 +1
	void writeDouble(float64 value);
	
	/// 读取数据流类型参数, 操作后参数个数 -1
	void readBytes(YHByteArray * bytes);
	
	/// 读取 boolean 类型参数, 操作后参数个数 -1
	bool readBoolean();
	
	/// 读取 char 类型参数, 操作后参数个数 -1
	int8 readChar();
	
	/// 读取 unsigned char 类型参数, 操作后参数个数 -1
	uint8 readUnsignedChar();
	
	/// 读取 short 类型参数, 操作后参数个数 -1
	int16 readShort();
	
	/// 读取 unsigned short 类型参数, 操作后参数个数 -1
	uint16 readUnsignedShort();
	
	/// 读取 int 类型参数, 操作后参数个数 -1
	int32 readInt();
	
	/// 读取 unsigned int 参数类型, 操作后参数个数 -1
	uint32 readUnsignedInt();
	
	/// 读取 float 类型参数, 操作后参数个数 -1
	float32 readFloat();
	
	/// 读取 double 类型参数, 操作后参数个数 -1
	float64 readDouble();
	
private:
	
	/// 获得最后一个参数的在 m_bytes 中的首地址
	uint32 getLastParamLoc();
	
	/// 当 writeXXX 时, 增加参数的计数个数
	void increaseParamCount();
	
private:
	
	bool m_packContentLength;
	uint16 m_moduleID;
	int32 m_functionID;
	uint32 m_paramLenLoc;
	YHByteArray * m_bytes;
	cocos2d::CCArray * m_params;
};

#endif /* defined(__cocos2d_x_Utils__YHGameLogicPackage__) */














































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


