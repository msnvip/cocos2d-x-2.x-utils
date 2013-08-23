//
//  YHEntity.h
//  GeometryLibrary
//
//  Created by Zhenyu Yao on 13-2-28.
//  Copyright (c) 2013年 Zhenyu Yao. All rights reserved.
//

#ifndef __GeometryLibrary__YHEntity__
#define __GeometryLibrary__YHEntity__

#include "YHVector2.h"

class YHEntity
{
	
public:
	
	/* 构造函数 */
	
	YHEntity() {}
	YHEntity(YHVector2 & pos, YHVector2 & vel, YHVector2 & acc) { m_pos = pos; m_vel = vel; m_acc = acc; }
	YHEntity(const YHVector2 & pos, const YHVector2 & vel, const YHVector2 & acc) { m_pos = pos; m_vel = vel; m_acc = acc; }
	
	/* 获取/设置属性 */
	
	YHVector2				getPos() const { return m_pos; }
	YHVector2 &				getPos() { return m_pos; }
	YHVector2				getVel() const { return m_vel; }
	YHVector2 &				getVel() { return m_vel; }
	YHVector2				getAcc() const { return m_acc; }
	YHVector2 & 			getAcc() { return m_acc; }
	float					getX() const { return m_pos.getX(); }
	float					getY() const { return m_pos.getY(); }
	float					getVelX() const { return m_vel.getX(); }
	float					getVelY() const { return m_vel.getY(); }
	float					getAccX() const { return m_acc.getX(); }
	float					getAccY() const { return m_acc.getY(); }
	
	void					setPos(const YHVector2 & pos) { m_pos = pos; }
	void					setVel(const YHVector2 & vel) { m_vel = vel; }
	void					setAcc(const YHVector2 & acc) { m_acc = acc; }
	void					setPosX(float x) { m_pos.setX(x); }
	void					setPosY(float y) { m_pos.setY(y); }
	void					setVelX(float vx) { m_vel.setX(vx); }
	void					setVelY(float vy) { m_vel.setY(vy); }
	void					setAccX(float ax) { m_acc.setX(ax); }
	void					setAccY(float ay) { m_acc.setY(ay); }
	
	/**
	 * 使用欧拉积分方式 - 更新
	 * @param dt 间隔时间
	 * @author Zhenyu Yao
	 */
	void					updateWithEuler(float dt);
	
	/**
	 * 使用龙格库塔二阶积分 - 更新
	 * @param dt 间隔时间
	 * @author Zhenyu Yao
	 */
	void					updateWithRK2(float dt);
	
	/**
	 * 使用龙格库塔四阶积分 = 更新
	 * @param dt 间隔时间
	 * @author Zhenyu Yao
	 */
	void					updateWithRK4(float dt);
	
	/**
	 * 使用欧拉积分方式预估位置
	 * @param dt 间隔时间
	 * @return 预估的位置
	 * @author Zhenyu Yao
	 */
	YHVector2				estimatePositionWithEuler(float dt) const;
	
	/**
	 * 使用龙格库塔二阶积分方式预估位置
	 * @param dt 间隔时间
	 * @return 预估的位置
	 * @author Zhenyu Yao
	 */
	YHVector2				estimatePositionWithRK2(float dt) const;
	
	/**
	 * 使用龙格库塔四阶积分方式预估位置
	 * @param dt 间隔时间
	 * @return 预估的位置
	 * @author Zhenyu Yao
	 */
	YHVector2				estimatePositionWithRK4(float dt) const;
	
	/**
	 * 创建 YHEntity 副本
	 * @return 对当前对象复制的副本
	 * @author Zhenyu Yao
	 */
	YHEntity				clone() const;
	
private:
	
	/**
	 * 使用欧拉积分方式计算
	 * @param pos 位置
	 * @param vel 速度
	 * @param acc 加速度
	 * @param dt 间隔时间
	 * @author Zhenyu Yao
	 */
	void					calculateWithEuler(YHVector2 & pos, YHVector2 & vel, YHVector2 & acc, float dt) const;
	
	/**
	 * 使用龙格库塔二阶积分方式计算
	 * @param pos 位置
	 * @param vel 速度
	 * @param acc 加速度
	 * @param dt 间隔时间
	 * @author Zhenyu Yao
	 */
	void					calculateWithRK2(YHVector2 & pos, YHVector2 & vel, YHVector2 & acc, float dt) const;
	
	/**
	 * 使用龙格库塔四阶积分方式计算
	 * @param pos 位置
	 * @param vel 速度
	 * @param acc 加速度
	 * @param dt 间隔时间
	 * @author Zhenyu Yao
	 */
	void					calculateWithRK4(YHVector2 & pos, YHVector2 & vel, YHVector2 & acc, float dt) const;
	
	/**
	 * 获得新的加速度
	 * @param pos 位置
	 * @param vel 速度
	 * @param acc 加速度
	 * @param dt 间隔时间
	 * @return YHVector2 对象, 新的加速度
	 * @author Zhenyu Yao
	 */
	YHVector2				acceleration(const YHVector2 & pos, const YHVector2 & vel, const YHVector2 & acc, float dt) const;
	
	YHVector2				m_pos;
	YHVector2				m_vel;
	YHVector2				m_acc;
	
};

#endif /* defined(__GeometryLibrary__YHEntity__) */

////////////////////////////////////////////////////////////////////////////////////////////////////
// end file


