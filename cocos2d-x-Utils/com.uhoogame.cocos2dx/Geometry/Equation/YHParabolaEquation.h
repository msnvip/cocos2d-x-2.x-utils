//
//  YHParabolaEquation.h
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-3-1.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#ifndef __GeometryLibrary__YHParabolaEquation__
#define __GeometryLibrary__YHParabolaEquation__

#include "YHGeometry.h"

/**
 * 抛物线方程式
 * @author Zhenyu Yao
 */
class YHParabolaEquation
{
	
public:
	
	/**
	 * 估算实体在间隔时间内移动到的位置
	 * @param entity 实体
	 * @param dt 间隔时间
	 * @return 估算的位置
	 * @author Zhenyu Yao
	 */
	YHVector2				estimatePosition(const YHEntity & entity, float dt) const;
	
	/**
	 * 计算到达 y 点需要的时间
	 * @param entity 移动的实体
	 * @param y 到达的纵向位置
	 * @return YHVector2 对象, 到达指定点需要的时间, x 表示 x1, y 表示 x2, 负数表示无效的时间
	 * @author Zhenyu Yao
	 */
	YHVector2				estimateVerticalTime(const YHEntity & entity, float y) const;
	
	/**
	 * 计算到达 x 点需要的时间
	 * @param entity 移动的实体
	 * @param x 到达的水平位置
	 * @return YHVector2 对象, 到达指定点需要的时间, x 表示 x1, y 表示 x2, 负数表示无效的时间
	 * @author Zhenyu Yao
	 */
	YHVector2				estimateHorizontalTime(const YHEntity & entity, float x) const;

	/**
	 * 估计两个实体的碰撞时间, 如果返回的结果 YHVector2 对象的 x, y 值都是 -1.0f 那么表示两个实体不会碰撞
	 * @param entityA 实体A
	 * @param entityB 实体B
	 * @return YHVector2 对象, 发生碰撞的时间, x 表示 x1, y 表示 x2, 负数表示无效的时间
	 * @author Zhenyu Yao
	 */
	YHVector2				estimateContactTime(const YHEntity & entityA, const YHEntity & entityB) const;
	
	/**
	 * 预估当 First 和 Sceond 需要碰撞时, first 的纵向发射速度
	 * @param first 第一个实体, 如果 first 和 second 会碰撞, 那么将会修改 first 的纵向速度, 否则将不会对 first 做任何修改
	 * @param second 第二个实体
	 * @param vel 计算出的 Y 轴速度, 可能含有两个值, getX(), getY() 各标识一个值
	 * @return 如果会发生碰撞则返回 true, 否则返回 false
	 * @author Zhenyu Yao
	 */
	bool					estimateFirstEntityVelYWhenContact(const YHEntity & first, const YHEntity & second, YHVector2 & vel) const;
	
	/**
	 * 计算在指定时间内, 到达指定位置需要的速度
	 * @param entity 实体
	 * @param time 指定的时间
	 * @param target 指定的位置
	 * @param vertical true 垂直坐标系, false 水平坐标系
	 * @return 计算出的速度
	 */
	float					estimateVel(const YHEntity & entity, float time, float target, bool vertical) const;
	
private:
	
	/**
	 * 比较浮点数是否相等
	 * @param value1 比较数值 1
	 * @param value2 比较数值 2
	 * @param digitNumber 取小数点后的位数
	 * @return 相等返回 true, 否则返回 false
	 */
	bool					equalToFloat(float value1, float value2, int digitNumber) const;

	/**
	 * 解一元二次不等式方程 ax(2) + bx + c = 0
	 * @param a 方程式中的 a
	 * @param b 方程式中的 b
	 * @param c 方程式中的 c
	 * @param root 方程式的根, x1: getX(), x2: getY()
	 * @return true 表示有根, false 表示无方程根
	 */
	bool					sloveQuadratic(float a, float b, float c, YHVector2 & root) const;
	
	/**
	 * 求一元二次方程的结果 ax(2) + bx + c = 0
	 * @param a 方程式中的 a 
	 * @param b 方程式中的 b
	 * @param c 方程式中的 c
	 * @param x 方式式中的 x
	 * @return 方程的结果
	 */
	float					sloveQuadraticResult(float a, float b, float c, float x) const;

};

/**
 * 使用欧拉积分方式计算的方程式
 * @author Zhenyu Yao
 */
class YHParabolaEulerEquation : public YHParabolaEquation
{
public:
	YHVector2			estimatePosition(const YHEntity & entity, float dt) const;
};

/**
 * 使用 RK2 方式计算方程式
 * @author Zhenyu Yao
 */
class YHParabolaRK2Equation : public YHParabolaEquation
{
public:
	YHVector2			estimatePosition(const YHEntity & entity, float dt) const;
};

/**
 * 使用 RK4 方式计算方程式
 * @author Zhenyu Yao
 */
class YHParabolaRK4Equation : public YHParabolaEquation
{
public:
	YHVector2			estimatePosition(const YHEntity & entity, float dt) const;
};

#endif /* defined(__GeometryLibrary__YHParabolaEquation__) */

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


