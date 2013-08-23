//
//  testAEPlugin.cpp
//  cocos2d-x-Utils
//
//  Created by mac on 13-7-15.
//
//

#include "testAEPlugin.h"
#include "AnimationTypes.h"
#include "CCSpecialSprite.h"
#include "CCActionExtension.h"
#include "YHAnimationHelper.h"
#include "YHAnimationCache.h"
#include "ActionContext.h"

CCScene* TestAEPlugin::scene()
{
	CCScene* scene = CCScene::create();
	CCLayer* layer = TestAEPlugin::create();
	scene->addChild(layer);
	return scene;
}

bool TestAEPlugin::init()
{
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCLayer::init());
		
		ActionContext::getContext()->initialize();
		
		CCLayerColor * colorBG = CCLayerColor::create(ccc4(0xff, 0xff, 0xff, 0xff));
		this->addChild(colorBG);
		
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Role.plist");
		
		std::string file = CCFileUtils::sharedFileUtils()->fullPathForFilename("Animator_Moudle.plist");
		CCDictionary* dict = CCDictionary::createWithContentsOfFile(file.c_str());
		AnimatorModuleData* moduleData = AnimatorModuleData::data(dict);
		AnimatorModuleDataCache::sharedCache()->addData(moduleData, file);
		
		file = CCFileUtils::sharedFileUtils()->fullPathForFilename("Animator_SettingData.plist");
		dict = CCDictionary::createWithContentsOfFile(file.c_str());
		AnimatorSettingData* settingData = AnimatorSettingData::data(dict);
		AnimatorSettingDataCache::sharedCache()->addData(settingData, file);
		
		file = CCFileUtils::sharedFileUtils()->fullPathForFilename(settingData->m_animatorFile.c_str());
		dict = CCDictionary::createWithContentsOfFile(file.c_str());
		CCAnimation * animation = YHAnimationHelper::createAnimation_Ver2(dict);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation, settingData->m_animatorFile.c_str());
		
		file = CCFileUtils::sharedFileUtils()->fullPathForFilename(settingData->m_animatorDataFile.c_str());
		dict = CCDictionary::createWithContentsOfFile(file.c_str());
		AnimatorData* animatorData = AnimatorData::data(dict);
		AnimatorDataCache::sharedCache()->addData(animatorData, settingData->m_animatorDataFile);
		
		for (int i=0; i<100; ++i)
		{
			moduleData = AnimatorModuleDataCache::sharedCache()->getData("Animator_Moudle.plist");
			CCSprite* sp = moduleData->createSpecialSprite();
			sp->setPosition(ccp(CCRANDOM_MINUS1_1() * 200.0f, CCRANDOM_MINUS1_1()* 200.0f));
			addChild(sp);
			
			CCSprite* sp1 = CCSprite::create();
			settingData = AnimatorSettingDataCache::sharedCache()->getData("Animator_SettingData.plist");
			animation = CCAnimationCache::sharedAnimationCache()->animationByName(settingData->m_animatorFile.c_str());
			animatorData = AnimatorDataCache::sharedCache()->getData(settingData->m_animatorDataFile);
			YHAnimationHelper::runActionWithSprite(sp1, animation, true, animatorData);
			sp->addChild(sp1, 1, 1);
		}
		
		AnimatorModuleDataCache::sharedCache()->clean();
		AnimatorSettingDataCache::sharedCache()->clean();
		AnimatorDataCache::sharedCache()->clean();
		
		/// testModule
//		file = CCFileUtils::sharedFileUtils()->fullPathForFilename("Animator_Moudle.plist");
//		dict = CCDictionary::createWithContentsOfFile(file.c_str());
//		CCSpecialSprite* ssp = CCSpecialSprite::create(dict);
//		CCSpriteBatchNode* batchNode = CCSpriteBatchNode::create("Icon.png");
//		CCSprite* sp = CCSprite::create("Icon.png");
//		addChild(batchNode);
//		ssp->addChild(sp, 1, 1);
//		ssp->setPosition(ccp(200,200));
//		batchNode->addChild(ssp);
		
//		CCAnchorPointBy * apb = CCAnchorPointBy::create(5.0f, ccp(1.5f, 1.5f));
//		CCMoveTo * action = CCMoveTo::create(5.0f, ccp(100, 100));
//		CCSprite * icon = CCSprite::create("Icon.png");
//		icon->setPosition(ccp(240, 160));
//		icon->runAction((CCAnchorPointBy *)apb->reverse()->copyWithZone(NULL));
//		icon->runAction(apb);
//		icon->runAction((CCAction *)action->copyWithZone(NULL));
//		this->addChild(icon);
			
		bRet = true;
	} while (0);
	
	return bRet;
}