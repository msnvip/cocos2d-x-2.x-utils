
#ifndef __YHIMessageBox_H__
#define __YHIMessageBox_H__

/**
 * 响应弹出窗口操作的接口
 * @author Zhenyu Yao
 */
class YHIMessageBox
{
public:
	
	/// 确认
	virtual void confirm(void * sender) = 0;
	
	/// 取消
	virtual void cancel(void * sender) = 0;
};

#endif // __YHIMessageBox_H__


