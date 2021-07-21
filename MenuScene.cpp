/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC_EXT;
USING_NS_CC;
using ui::Scale9Sprite;


Label* words[10];
Scale9Sprite* bac;
ControlButton* b[10];
extern int level;

Scene* Mymenu::createScene()
{
    return Mymenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Mymenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

// on "init" you need to initialize your instance
bool Mymenu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Mymenu::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Select Levels", "fonts/Marker Felt.ttf", 36);
    label->getLetter(0)->setColor(Color3B(255, 0, 0));
    label->getLetter(1)->setColor(Color3B(255, 20, 147));
    label->getLetter(2)->setColor(Color3B(0, 0, 255));
    label->getLetter(3)->setColor(Color3B(255, 127, 36));
    label->getLetter(4)->setColor(Color3B(255, 0, 0));
    label->getLetter(5)->setColor(Color3B(255, 20, 147));
    label->getLetter(7)->setColor(Color3B(0, 0, 255));
    label->getLetter(8)->setColor(Color3B(255, 127, 36));
    label->getLetter(9)->setColor(Color3B(255, 0, 0));
    label->getLetter(10)->setColor(Color3B(255, 20, 147));
    label->getLetter(11)->setColor(Color3B(0, 0, 255));
    label->getLetter(12)->setColor(Color3B(255, 127, 36));
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    //auto listener = EventListenerKeyboard::create();
    //listener->onKeyPressed = CC_CALLBACK_2(Mymenu::onKeyPressed, this);
    //this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto lc = CCLayerColor::create(Color4B(255, 250, 250, 255));
    this->addChild(lc);
    iniFunc();
    return true;
}

void Mymenu::clickEvent(CCObject* a, Control::EventType event) {
    if (a == b[0]) {
        level = 0;
        auto scene = HelloWorld::createScene();
        auto transition = TransitionZoomFlipY::create(1, scene);
        Director::getInstance()->replaceScene(transition);
    }
    else if (a == b[1]) {
        level = 1;
        auto scene = HelloWorld::createScene();
        auto transition = TransitionZoomFlipY::create(1, scene);
        Director::getInstance()->replaceScene(transition);
    }
    else if (a == b[2]) {
        level = 2;
        auto scene = HelloWorld::createScene();
        auto transition = TransitionZoomFlipY::create(1, scene);
        Director::getInstance()->replaceScene(transition);
    }
    else if (a == b[3]) {
        level = 0;
        auto scene = HelloWorld::createScene();
        auto transition = TransitionZoomFlipY::create(1, scene);
        Director::getInstance()->replaceScene(transition);
    }
}

void Mymenu::iniFunc() {
    auto draw = DrawNode::create();
    draw->setGlobalZOrder(0);
    draw->drawSegment(Vec2(450, 460), Vec2(550, 540), 5, Color4F(1, 0.4980, 0.1412, 1));
    draw->drawSegment(Vec2(650, 540), Vec2(750, 460), 5, Color4F(1, 0.4980, 0.1412, 1));
    draw->drawSegment(Vec2(850, 469), Vec2(950, 540), 5, Color4F(1, 0.4980, 0.1412, 1));
    this->addChild(draw);


    bac = Scale9Sprite::create("buttonblue.png");
    words[0]= Label::createWithTTF("Test", "fonts/Marker Felt.ttf", 36);
    words[0]->setColor(Color3B(255, 20, 147));
    b[0] = ControlButton::create(words[0], bac);
    b[0]->setPosition(400, 450);
    b[0]->setGlobalZOrder(10);
    this->addChild(b[0]);
    b[0]->addTargetWithActionForControlEvents(this, cccontrol_selector(Mymenu::clickEvent), Control::EventType::TOUCH_DOWN);

    bac = Scale9Sprite::create("buttonblue.png");
    words[1] = Label::createWithTTF("Level 1", "fonts/Marker Felt.ttf", 36);
    words[1]->setColor(Color3B(255, 20, 147));
    b[1] = ControlButton::create(words[1], bac);
    b[1]->setPosition(600, 550);
    b[1]->setGlobalZOrder(10);
    this->addChild(b[1]);
    b[1]->addTargetWithActionForControlEvents(this, cccontrol_selector(Mymenu::clickEvent), Control::EventType::TOUCH_DOWN);

    bac = Scale9Sprite::create("buttonblue.png");
    words[2] = Label::createWithTTF("Level 2", "fonts/Marker Felt.ttf", 36);
    words[2]->setColor(Color3B(255, 20, 147));
    b[2] = ControlButton::create(words[2], bac);
    b[2]->setPosition(800, 450);
    b[2]->setGlobalZOrder(10);
    this->addChild(b[2]);
    b[2]->addTargetWithActionForControlEvents(this, cccontrol_selector(Mymenu::clickEvent), Control::EventType::TOUCH_DOWN);

    bac = Scale9Sprite::create("buttonblue.png");
    words[3] = Label::createWithTTF("Level 3", "fonts/Marker Felt.ttf", 36);
    words[3]->setColor(Color3B(255, 20, 147));
    b[3] = ControlButton::create(words[3], bac);
    b[3]->setPosition(1000, 550);
    b[3]->setGlobalZOrder(10);
    this->addChild(b[3]);
    b[3]->addTargetWithActionForControlEvents(this, cccontrol_selector(Mymenu::clickEvent), Control::EventType::TOUCH_DOWN);

    return;
}









/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



