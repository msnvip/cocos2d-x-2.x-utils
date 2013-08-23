//
//  SoundController.h
//  AndroidaBooM
//
//  Created by Zhenyu Yao on 13-4-24.
//
//

#ifndef __AndroidaBooM__SoundController__
#define __AndroidaBooM__SoundController__

#include "SimpleAudioEngine.h"
#include "YHTypes.h"

/**
 * 音频控制器类, 对 SimpleAudioEngine 的再一次封装, 其实主要是为了实现淡入/淡出音效效果而封装的
 * @author Zhenyu Yao
 */
class SoundController : public cocos2d::CCObject
{
	
public: /** Functions **/
	
	static SoundController * 			sharedSoundController();
	
	~SoundController();
	
	/// 初始化
	void								init();
	
	/// 子路径, 在读取实际的音频文件时, 传给 SimpleAudioEngine 的路径是 subpath + filename
	std::string							getSubPath() { return m_subpath; }
	void								setSubPath(const std::string & subpath) { m_subpath = subpath; }
	
	/**
	 * 添加映射表. 映射表主要是对实际文件的一层间接调用, 可以通过使用 playEffectWithKey 和 playBGMWithKey 两个函数的 key 参数从映射表中找到实际的文件, 然后播放该音频; 如果没有 key 对应的音频文件, 那么将没有任何效果.
	 * @param dict 添加的映射表字典
	 */
	void								appendMappingFile(cocos2d::CCDictionary * dict);
	
	/**
	 * 通过 key 从映射表中搜索到实际的文件, 然后播放音频
	 * @param key 用于在映射表中查找的 key
	 * @param loop 是否循环播放, 默认不循环播放
	 * @return 返回 SimpleAudioEngine 类的 playEffect 方法返回的值
	 */
	uint32								playEffectWithKey(const std::string & key, bool loop = false);
	
	/**
	 * 通过 key 从映射表中搜索到实际的文件, 然后播放音频
	 * @param key 用于在映射表中查找的 key
	 * @param loop 是否循环播放, 默认不循环播放
	 */
	void								playBGMWithKey(const std::string & key, bool loop = false);
	
	/**
	 * 所有音乐淡出, 包括 Effect & BGM, 淡出后音量降为 0, 必须调用 fadeIn 以恢复音量.
	 * @param duration 淡出的持续时间
	 */
	void								fadeOutVolume(float32 duration = 1.0f);
	
	/**
	 * 所有音乐淡入, 包括 Effect & BGM
	 * @param duration 淡入的持续时间
	 */
	void								fadeInVolume(float32 duration = 1.0f);
	
	/// update
	virtual void						update(float dt);

	/// 从键查找到对应的文件名
	const char *						fileWithKey(const std::string & key);
	
public: /** SimpleAudioEngine 的功能相同 **/
	
	void								preloadBackgroundMusic(const char * pszFilePath);
	
	void								playBackgroundMusic(const char * pszFilePath, bool bLoop);
	
	void								playBackgroundMusic(const char * pszFilePath);
	
	void								stopBackgroundMusic(bool bReleaseData);
	
	void								stopBackgroundMusic();
	
	void								pauseBackgroundMusic();
	
	void								resumeBackgroundMusic();
	
	void								rewindBackgroundMusic();
	
	void								willPlayBackgroundMusic();
	
	bool								isBackgroundMusicPlaying();
	
	float								getBackgroundMusicVolume();
	
	void								setBackgroundMusicVolume(float volume);
	
	float								getEffectsVolume();
	
	void								setEffectsVolume(float volume);
	
	uint32								playEffect(const char * pszFilePath, bool bLoop);
	
	uint32								playEffect(const char * pszFilePath);
	
	void								pauseEffect(uint32 soundID);
	
	void 								pauseAllEffects();
	
	void								resumeEffect(uint32 soundID);
	
	void								resumeAllEffects();
	
	void								stopEffect(uint32 soundID);
	
	void								stopAllEffects();
	
	void								preloadEffect(const char * pszFilePath);
	
	void								unloadEffect(const char * pszFilePath);
	
private: /** Functions **/
	SoundController();
	
private:
	typedef enum FadeType
	{
		kFadeType_None,
		kFadeType_In,
		kFadeType_Out,
	}FadeType;
	
private:
	CocosDenshion::SimpleAudioEngine *				m_engine;
	cocos2d::CCDictionary *							m_dict;
	
	FadeType										m_fadeType;
	float32											m_elapse;
	float32											m_duration;
	float32											m_effectsVolume;
	float32											m_BGMVolume;
	
	std::string										m_subpath;
};

#endif /* defined(__AndroidaBooM__SoundController__) */


