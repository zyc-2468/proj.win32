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

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int posj = 1, posi = 1;

int direction = 0;
//0 up
//1 down
//2 left
//3 right

Mygraph g;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Maze", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto lc = CCLayerColor::create(Color4B(255, 250, 250,200));
    this->addChild(lc);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 24; j++) {
            if (g.squares[i][j].type == 1) {
                s[i][j] = Sprite::create("wall.jpg");
                s[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(s[i][j], 0);
            }
        }
    }

    person = Sprite::create("pfront.png");
    person->setPosition(Vec2(origin.x+80, origin.y+80));
    this->addChild(person);   
    


    return true;
}

int getx(int j) {
    return j * 40 + 40;
}

int gety(int i) {
    return i * 40 + 40;
}

int geti(int y) {
    return (y - 20) / 40;
}

int getj(int x) {
    return(x - 20) / 40;
}

bool constrain(int i, int j) {
    if (i < 0)return 0;
    if (i >= 16)return 0;
    if (j < 0)return 0;
    if (j >= 24)return 0;
    return 1;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //判断 keyCode 枚举来区分所按下的按键
    auto moveUp = MoveBy::create(0.1, Point(0, 40));

    auto moveDown = MoveBy::create(0.1, Point(0, -40));

    auto moveLeft = MoveBy::create(0.1, Point(-40, 0));

    auto moveRight = MoveBy::create(0.1, Point(40, 0));
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        if (g.squares[posi + 1][posj].type != 1)
        {
            int x = person->getPositionX();
            int y = person->getPositionY();
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pback.png");
            person->setTexture(texture);
            person->setPosition(Vec2(x, y));
            person->runAction(moveUp);
            posi += 1;
            direction = 0;
        }
        break;
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        if (g.squares[posi - 1][posj].type != 1)
        {
            int x = person->getPositionX();
            int y = person->getPositionY();
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pfront.png");
            person->setTexture(texture);
            person->setPosition(Vec2(x, y));
            person->runAction(moveDown);
            posi -= 1;
            direction = 1;
        }
        break;
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        if (g.squares[posi][posj - 1].type != 1)
        {
            int x = person->getPositionX();
            int y = person->getPositionY();
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pleft.png");
            person->setTexture(texture);
            person->setPosition(Vec2(x, y));
            person->runAction(moveLeft);
            posj -= 1;
            direction = 2;
        }
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        if (g.squares[posi][posj + 1].type != 1)
        {
            int x = person->getPositionX();
            int y = person->getPositionY();
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pright.png");
            person->setTexture(texture);
            person->setPosition(Vec2(x, y));
            person->runAction(moveRight);
            posj += 1;
            direction = 3;
        }
        break;
    case EventKeyboard::KeyCode::KEY_SPACE:
        if (direction==0&&g.squares[posi+1][posj].type != 1|| direction == 1 && g.squares[posi - 1][posj].type != 1|| direction == 3 && g.squares[posi][posj-1].type != 1|| direction == 0 && g.squares[posi][posj+1].type != 1)
        {
           auto bomb = Sprite::create("bomb.png");
           if(direction==0)bomb->setPosition(Vec2(origin.x+getx(posj),origin.y+gety(posi)+40));
           else if (direction == 1)bomb->setPosition(Vec2(origin.x + getx(posj), origin.y + gety(posi) - 40));
           else if (direction == 2)bomb->setPosition(Vec2(origin.x + getx(posj)-40, origin.y + gety(posi)));
           else if(direction == 3)bomb->setPosition(Vec2(origin.x + getx(posj)+40, origin.y + gety(posi)));
           this->addChild(bomb);
           auto ani = explodeAnimation();
           auto explodecall = CallFunc::create([=] {
               this->removeChild(bomb, true);
               int i = geti(bomb->getPositionY());
               int j = getj(bomb->getPositionX());
               if (constrain(i+1, j)&&g.squares[i+1][j].type==1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i + 1][j]->setTexture(texture);
                   g.squares[i + 1][j].type = 0;
               }
               if (constrain(i + 1, j-1) && g.squares[i + 1][j-1].type == 1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i + 1][j-1]->setTexture(texture);
                   g.squares[i + 1][j-1].type = 0;
               }
               if (constrain(i + 1, j+1) && g.squares[i + 1][j+1].type == 1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i + 1][j+1]->setTexture(texture);
                   g.squares[i + 1][j+1].type = 0;
               }
               if (constrain(i, j-1) && g.squares[i][j-1].type == 1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i][j-1]->setTexture(texture);
                   g.squares[i][j-1].type = 0;
               }
               if (constrain(i, j+1) && g.squares[i][j+1].type == 1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i][j+1]->setTexture(texture);
                   g.squares[i][j+1].type = 0;
               }
               if (constrain(i-1, j - 1) && g.squares[i-1][j - 1].type == 1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i-1][j - 1]->setTexture(texture);
                   g.squares[i-1][j - 1].type = 0;
               }
               if (constrain(i-1, j) && g.squares[i-1][j].type == 1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i-1][j]->setTexture(texture);
                   g.squares[i-1][j].type = 0;
               }
               if (constrain(i-1, j + 1) && g.squares[i-1][j + 1].type == 1) {
                   CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.jpg");
                   s[i-1][j + 1]->setTexture(texture);
                   g.squares[i-1][j + 1].type = 0;
               }
               });
           auto act = Animate::create(ani);
           auto seq = Sequence::create(cocos2d::DelayTime::create(2),
               act, cocos2d::DelayTime::create(0.3), explodecall, NULL);
           bomb->runAction(seq);
        }
        break;
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

Animation* HelloWorld::getAnimation(string name, float delay, int num) {
    auto ani = Animation::create();
    for (int i = 0; i < num; i++) {
        string framename = name;
        framename += to_string(i) + ".png";
        ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(framename.c_str()));
    }
    ani->setDelayPerUnit(delay);
    ani->setRestoreOriginalFrame(true);
    return ani;
}

Animation* HelloWorld::explodeAnimation() {
    auto ani = Animation::create();
    ani->addSpriteFrameWithFile("bomb.png");
    ani->addSpriteFrameWithFile("explode.png");
    ani->setDelayPerUnit(0.2f);
    ani->setRestoreOriginalFrame(false);
    return ani;
}
