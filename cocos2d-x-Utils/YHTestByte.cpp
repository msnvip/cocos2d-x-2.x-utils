//
//  YHTestByte.cpp
//  cocos2d-x-Utils
//
//  Created by Zhenyu Yao on 13-8-10.
//
//

#include <string.h>
#include "YHTestByte.h"
#include "net/buffer/YHByteArray.h"
#include "net/buffer/YHCommandParam.h"
#include "net/buffer/YHGameLogicPackage.h"

void testByteArray()
{
	YHByteArray * bytes = new YHByteArray();
	bytes->init();
	bytes->setOrder(kByteOrder_LittleEndian);
	
	YHByteArray * copied = new YHByteArray();
	copied->init();
	
	CCLOG("capacity: %d", bytes->getCapacity());
	
	char buf[] = "123456";
	bytes->writeBytes(buf, strlen(buf) + 1);
	bytes->writeBoolean(true);
	bytes->writeChar('a');
	bytes->writeUnsignedChar('b');
	bytes->writeShort(-23);
	bytes->writeUnsignedShort(-23);
	bytes->writeInt(-23);
	bytes->writeUnsignedInt(-23);
	bytes->writeFloat(100.001f);
	bytes->writeDouble(100.004);
	
	bytes->discardReadBytes();
	CCLOG("readableBytes: %d", bytes->readableBytes());
	CCLOG("writeableBytes: %d", bytes->writeableBytes());
	
	char tmp[256] = {0, };
//	bytes->readBytes(tmp, strlen(buf) + 1);
	bytes->readBytes(copied, strlen(buf) + 1);
	CCLOG("readBytes: %s", copied->getBuffer());
	CCLOG("readBoolean: %s", bytes->readBoolean() ? "true" : "false");
	CCLOG("readChar: %c", bytes->readChar());
	CCLOG("readUnsignedChar: %c", bytes->readUnsignedChar());
	CCLOG("readShort: %d", bytes->readShort());
	CCLOG("readUnsignedShor: %d", bytes->readUnsignedShort());
	CCLOG("readInt: %d", bytes->readInt());
	CCLOG("readUnsignedInt: %u", bytes->readUnsignedInt());
	CCLOG("readFloat: %f", bytes->readFloat());
	CCLOG("readDouble: %f", bytes->readDouble());
	
	bytes->discardReadBytes();
	CCLOG("readableBytes: %d", bytes->readableBytes());
	CCLOG("writeableBytes: %d", bytes->writeableBytes());
	
	CCLOG("--------------------------------");
	
	unsigned int index = 100;
	bytes->setBytes(index, buf, strlen(buf) + 1, 0); index += strlen(buf) + 1;
	bytes->setBoolean(index++, false);
	bytes->setChar(index++, 'x');
	bytes->setUnsignedChar(index++, 'y');
	bytes->setShort(index, -32); index += 2;
	bytes->setUnsignedShort(index, -32); index += 2;
	bytes->setInt(index, -32); index += 4;
	bytes->setUnsignedInt(index, -32); index += 4;
	bytes->setFloat(index, 123.123f); index += 4;
	bytes->setDouble(index, 321.321); index += 8;
	
	index = 100;
	char buf3[256] = {0, };
	bytes->getBytes(index, buf3, strlen(buf) + 1, 50);
	bytes->getBytes(index, copied, strlen(buf) + 1, 150);
	index += strlen(buf) + 1;
	CCLOG("getBytes: %s", buf3 + 50);
	CCLOG("getBytes: %s", copied->getBuffer() + 150);
	CCLOG("getBoolean: %s", bytes->getBoolean(index) ? "true" : "false"); index++;
	CCLOG("getChar: %c", bytes->getChar(index)); index++;
	CCLOG("getUnsignedChar: %c", bytes->getUnsignedChar(index)); index++;
	CCLOG("getShort: %d", bytes->getShort(index)); index += 2;
	CCLOG("getUnsignedShort: %d", bytes->getUnsignedShort(index)); index += 2;
	CCLOG("getInt: %d", bytes->getInt(index)); index += 4;
	CCLOG("getUnsignedInt: %u", bytes->getUnsignedInt(index)); index += 4;
	CCLOG("getFloat: %f", bytes->getFloat(index)); index += 4;
	CCLOG("getDouble: %f", bytes->getDouble(index)); index += 8;
	
	CCLOG("---------------------------------");
	
	index = 0;
	char buf4[256] = "654321";
	YHCommandParam * param0 = new YHCommandParam(bytes, index, strlen(buf4) + 1);
	param0->writeBytes(buf4, strlen(buf4) + 1);
	param0->readBytes(buf3, strlen(buf) + 1);
	CCLOG("readBytes: %s", buf3);
	
	YHCommandParam * param1 = new YHCommandParam(bytes, param0->getLoc() + param0->getLen(), 1);
	param1->writeBoolean(true);
	CCLOG("readBoolean: %s", param1->readBoolean() ? "true" : "false");
	
	YHCommandParam * param2 = new YHCommandParam(bytes, param1->getLoc() + param1->getLen(), 1);
	param2->writeChar('q');
	CCLOG("readChar: %c", param2->readChar());
	
	YHCommandParam * param3 = new YHCommandParam(bytes, param2->getLoc() + param2->getLen(), 1);
	param3->writeUnsignedChar('z');
	CCLOG("readUnsignedChar: %c", param3->readUnsignedChar());
	
	YHCommandParam * param4 = new YHCommandParam(bytes, param3->getLoc() + param3->getLen(), 2);
	param4->writeShort(0xffff);
	CCLOG("readShort: %d", param4->readShort());
	
	YHCommandParam * param5 = new YHCommandParam(bytes, param4->getLoc() + param4->getLen(), 2);
	param5->writeUnsignedShort(0xffff);
	CCLOG("readUnsignedShort: %d", param5->readUnsignedShort());
	
	YHCommandParam * param6 = new YHCommandParam(bytes, param5->getLoc() + param5->getLen(), 4);
	param6->writeInt(0xffffffff);
	CCLOG("readInt: %d", param6->readInt());
	
	YHCommandParam * param7 = new YHCommandParam(bytes, param6->getLoc() + param6->getLen(), 4);
	param7->writeUnsignedInt(0xffffffff);
	CCLOG("readUnsignedInt: %u", param7->readUnsignedInt());
	
	YHCommandParam * param8 = new YHCommandParam(bytes, param7->getLoc() + param7->getLen(), 4);
	param8->writeFloat(1234.1234f);
	CCLOG("readFloat: %f", param8->readFloat());
	
	YHCommandParam * param9 = new YHCommandParam(bytes, param8->getLoc() + param8->getLen(), 8);
	param9->writeDouble(123456.123456);
	CCLOG("readDouble: %f", param9->readDouble());
	
	CC_SAFE_RELEASE_NULL(bytes);
	CC_SAFE_RELEASE_NULL(param0);
	CC_SAFE_RELEASE_NULL(param1);
	CC_SAFE_RELEASE_NULL(param2);
	CC_SAFE_RELEASE_NULL(param3);
	CC_SAFE_RELEASE_NULL(param4);
	CC_SAFE_RELEASE_NULL(param5);
	CC_SAFE_RELEASE_NULL(param6);
	CC_SAFE_RELEASE_NULL(param7);
	CC_SAFE_RELEASE_NULL(param8);
	CC_SAFE_RELEASE_NULL(param9);
	
	CCLOG("---------------------------------");
	
	YHGameLogicPackage * package = new YHGameLogicPackage(1, 100);
	char buf5[] = "0123456789";
	package->writeBytes(buf5, sizeof(buf5));
	package->writeBoolean(false);
	package->writeChar('g');
	package->writeUnsignedChar('h');
	package->writeShort(1);
	package->writeUnsignedShort(-1);
	package->writeInt(1);
	package->writeUnsignedInt(-1);
	package->writeFloat(123456.654321f);
	package->writeDouble(123456789.987654321);
	
	YHByteArray * sendBytes = package->getSendBytes();
	CCLOG("getSendBytes: %u", sendBytes->readUnsignedInt());
	
	YHGameLogicPackage * package2 = new YHGameLogicPackage(sendBytes);
	CCLOG("moduleID: %d, functionID: %d", package2->getModuleID(), package2->getFunctionsID());
	
	YHByteArray * tmpBytes = new YHByteArray();
	package2->readBytes(tmpBytes);
	CCLOG("readBytes: %s", tmpBytes->getBuffer());
	CCLOG("readBoolean: %s", package2->readBoolean() ? "true" : "false");
	CCLOG("readChar: %c", package2->readChar());
	CCLOG("readUnsignedChar: %c", package2->readUnsignedChar());
	CCLOG("readShort: %d", package2->readShort());
	CCLOG("readUnsignedShort: %d", package2->readUnsignedShort());
	CCLOG("readInt: %d", package2->readInt());
	CCLOG("readUnsignedInt: %u", package2->readUnsignedInt());
	CCLOG("readFloat: %f", package2->readFloat());
	CCLOG("readDouble: %f", package2->readDouble());
	
	CC_SAFE_RELEASE_NULL(package);
	CC_SAFE_RELEASE_NULL(package2);
	CC_SAFE_RELEASE_NULL(tmpBytes);
}












































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


