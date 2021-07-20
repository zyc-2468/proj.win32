#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include"../proj.win32/library.h"
#include"../proj.win32/square.h"
#include"extensions/GUI/CCControlExtension/CCControl.h"
#include"extensions/GUI/CCControlExtension/CCControlButton.h"
#include"ui/UIScale9Sprite.h"
#include "HelloWorldScene.h"
//#include"ui/CocosGUI.h"
//#include"ui/UIWidget.h"

class Mymenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(Mymenu);
    void iniFunc();
    void clickEvent(cocos2d::CCObject* pSender, cocos2d::extension::Control::EventType event);
};

#endif 
