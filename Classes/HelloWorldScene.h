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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"../proj.win32/library.h"
#include"../proj.win32/square.h"
#include"extensions/GUI/CCControlExtension/CCControl.h"
#include"extensions/GUI/CCControlExtension/CCControlButton.h"
#include"ui/UIScale9Sprite.h"

class Myarrow {
public:
    cocos2d::Sprite* arrow;
    bool fire;
    int* dir;
    int* state;
    Myarrow() {
        state = new int;
        *state = 0;
        dir = new int;
        *dir = 0;
    }
};

class Mybomb {
public:
    cocos2d::Sprite* bomb;
    int* state;
    Mybomb() {
        state = new int;
        *state = 0;
    }
};

class Monster {
public:
    cocos2d::Sprite* monster;
    set<point> activearea;
};

class Mybox {
public:
    cocos2d::Sprite* box;
    int* state;
    int* dir;
    Mybox() {
        state = new int;
        *state = 0;
        dir = new int;
        *dir = 0;
    }
};

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    cocos2d::Sprite* person = new cocos2d::Sprite();
    cocos2d::Sprite* s[20][43];
    cocos2d::Sprite* door1[20][43];
    cocos2d::Sprite* door2[20][43];
    cocos2d::Sprite* candle[20][43];
    cocos2d::Sprite* board[20][43];
    cocos2d::Sprite* button[20][43];
    list<Mybomb> bombs;
    list<Mybox> boxes;
    list<Myarrow> arrows;
    cocos2d::Sprite* note;
    cocos2d::Sprite* note2;
    cocos2d::Label* noteword;
    //list<Monster> monsters;
    list<cocos2d::Sprite*> bloods;
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    cocos2d::Animation* getAnimation(string name, float delay, int num);
    cocos2d::Animation* explodeAnimation1();
    cocos2d::Animation* explodeAnimation2();
    cocos2d::Animation* smokeAnimation();
    cocos2d::RepeatForever* awagAnimation();
    cocos2d::Sequence* dropwaterSeq(int dir);
    cocos2d::Sequence* dropwaterSeq2(int i, int j);
    //void arriveop(int i, int j);
    void doorChange(int i, int j, int color, int mode);
    void boardChange(int i, int j, int mode);
    int checkdoor1(int i, int j);
    int checkdoor2(int i, int j);
    void candleLight(int i, int j);
    void candleDark(int i, int j);
    void checkonto(int i, int j);
    void checkleave(int i, int j);
    void persononto(int i, int j);
    void personleave(int i, int j);
    void boxonto(Mybox box, int i, int j);
    void bombonto(Mybomb bomb, int i, int j);
    int canBoxGo(int i, int j, int dir);
    int canPersonGo(int i, int j);
    int canArrowGo(int i, int j);
    point getpos(cocos2d::Sprite* spri);
    void bombexplode(int i, int j);
    void bombexplode1(int i, int j);
    //void eventCheck(float dt);
    void explodeop(int i, int j, int dir);
    void explodeop1(int i, int j, int dir);
    void explodeop2(int i, int j);
    void goTo(Mybox b, int x, int y, int i, int j);
    void stopActInTime(Mybox b, float t);
    void stopActInTime2(Myarrow a, float t);
    void stopActInTime3(Myarrow a, float t, int dir);
    virtual void update(float dt);
    int hasBox(int i, int j);
    int hasBox2(int i, int j);
    bool isWater(int i, int j);
    void iniFunc();
    void updateinfo();
    void renewStorage(int type);
    void renewBlood(int num);
    void setPic(cocos2d::Sprite* spr, string s);
    void clickEvent(cocos2d::CCObject* pSender, cocos2d::extension::Control::EventType event);
    void winlose();
    
};

bool constrain(int i, int j);
int getx(int j);
int gety(int i);
int geti(int y);
int getj(int x);
int dis(int a, int b, int c, int d);

#endif // __HELLOWORLD_SCENE_H__
