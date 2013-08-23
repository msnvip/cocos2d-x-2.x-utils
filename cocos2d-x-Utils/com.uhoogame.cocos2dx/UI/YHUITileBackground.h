//
//  YHUITileBackground.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-24.
//
//

#ifndef __AndroidaBooM__YHUITileBackground__
#define __AndroidaBooM__YHUITileBackground__

#include "cocos2d.h"

/**
 * 由1个方块拼接成背景图片
 * 如果是使用 kTileType_2 类型初始化, 则子方块的贴图切块默认为左边; 如果是使用 kTileType_4 类型初始化, 则子方块的贴图切块默认为左上角.
 * @author Zhenyu Yao
 */
class YHUITileBackground : public cocos2d::CCSprite
{
public:
	typedef enum TileType
	{
		kTileType_2,
		kTileType_4,
	}TileType;
	
public:
	
	/// 初始化
	bool							init(TileType tileType, const char * spriteFrameName);
	
	/// 创建 YHUITileBackground 对象
	static YHUITileBackground *		create(TileType tileType, const char * spriteFrameName);
};

#endif /* defined(__AndroidaBooM__YHUITileBackground__) */


