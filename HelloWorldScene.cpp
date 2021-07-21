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
#include"MenuScene.h"

USING_NS_CC_EXT;
USING_NS_CC;
using ui::Scale9Sprite;

int posj = 1, posi = 1;

int direction = 0;

int canop = 1;

int level;

int over = 0;

ControlButton* b_pause;
ControlButton* b_quit;
ControlButton* b_resume;
ControlButton* b_restart;

//0 up
//1 down
//2 left
//3 right

Mygraph g;

Label* menu;
Label* menu0;
Label* menu1;
Label* menu2;
Label* menu3;
Sprite* blood[10];
vector<point>path;

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

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


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

    auto label = Label::createWithTTF("Maze", "fonts/Marker Felt.ttf", 36);
    label->getLetter(0)->setColor(Color3B(255, 0, 0));
    label->getLetter(1)->setColor(Color3B(255, 20, 147));
    label->getLetter(2)->setColor(Color3B(0, 0, 255));
    label->getLetter(3)->setColor(Color3B(255, 127, 36));
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
    
    auto lc = CCLayerColor::create(Color4B(255, 250, 250,255));
    this->addChild(lc);
    iniFunc();
    return true;
}

void HelloWorld::iniFunc() {
    g = Mygraph(level);
    //180 300 460 580
    posi = g.inii;
    posj = g.inij;
    path.clear();
    path.push_back(point(posi, posj));

    menu = Label::createWithTTF("Storage: ", "fonts/Marker Felt.ttf", 28);
    menu->setTextColor(Color4B(0, 0, 0, 255));
    menu->setPosition(Vec2(80, 860));
    this->addChild(menu);

    menu0 = Label::createWithTTF(": "+to_string(g.boxnum), "fonts/Marker Felt.ttf", 28);
    menu0->setPosition(Vec2(220, 860));
    menu0->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(menu0);

    menu1 = Label::createWithTTF(": " + to_string(g.arrownum), "fonts/Marker Felt.ttf", 28);
    menu1->setPosition(Vec2(370, 860));
    menu1->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(menu1);

    menu2 = Label::createWithTTF(": " + to_string(g.firearrownum), "fonts/Marker Felt.ttf", 28);
    menu2->setPosition(Vec2(520, 860));
    menu2->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(menu2);

    menu3 = Label::createWithTTF(": " + to_string(g.bombnum), "fonts/Marker Felt.ttf", 28);
    menu3->setPosition(Vec2(620, 860));
    menu3->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(menu3);

    direction = 0;
    canop = 1;
    over = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    person = Sprite::create("pfront.png");
    person->setPosition(Vec2(origin.x + posj * 40 + 40, origin.y + posi * 40 + 40));
    person->setGlobalZOrder(7);
    this->addChild(person);


    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 43; j++) {
            if (g.squares[i][j].type == 1) {
                s[i][j] = Sprite::create("wall.jpg");
                s[i][j]->setGlobalZOrder(10);
                s[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(s[i][j]);
            }
            else if (g.squares[i][j].type == 2) {
                s[i][j] = Sprite::create("wall3.jpg");
                s[i][j]->setGlobalZOrder(10);
                s[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(s[i][j]);
            }
            else if (g.squares[i][j].type == 3) {
                s[i][j] = Sprite::create("water.jpg");
                s[i][j]->setGlobalZOrder(0);
                s[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(s[i][j]);
            }
            else if (g.squares[i][j].type == 4) {
                s[i][j] = Sprite::create("campfire1.png");
                s[i][j]->setGlobalZOrder(0);
                s[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(s[i][j]);
            }
            else if (g.squares[i][j].type == 5) {
                s[i][j] = Sprite::create("campfire2.png");
                s[i][j]->setGlobalZOrder(0);
                s[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(s[i][j]);
            }
            else if (g.squares[i][j].type == 6) {
                s[i][j] = Sprite::create("tree.png");
                s[i][j]->setGlobalZOrder(0);
                s[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(s[i][j]);
            }
            if (g.squares[i][j].door1.hasdoor == 1) {
                if (g.squares[i][j].door1.color == 0)door1[i][j] = Sprite::create("doorred1.png");
                else if (g.squares[i][j].door1.color == 1)door1[i][j] = Sprite::create("dooryellow1.png");
                else if (g.squares[i][j].door1.color == 2)door1[i][j] = Sprite::create("doorpink1.png");
                else if (g.squares[i][j].door1.color == 3)door1[i][j] = Sprite::create("doorblue1.png");
                else if (g.squares[i][j].door1.color == 4)door1[i][j] = Sprite::create("doorgreen1.png");
                door1[i][j]->setGlobalZOrder(10);
                door1[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(door1[i][j]);
            }
            if (g.squares[i][j].type == 3 && g.squares[i][j].board.hasboard == 1) {
                board[i][j] = Sprite::create("board.png");
                board[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                board[i][j]->setOpacity(130);
                board[i][j]->setGlobalZOrder(0);
                this->addChild(board[i][j]);
            }
            if (g.squares[i][j].door2.hasdoor == 1) {
                if (g.squares[i][j].door2.color == 0)door2[i][j] = Sprite::create("doorred3.png");
                else if (g.squares[i][j].door2.color == 1)door2[i][j] = Sprite::create("dooryellow3.png");
                else if (g.squares[i][j].door2.color == 2)door2[i][j] = Sprite::create("doorpink3.png");
                else if (g.squares[i][j].door2.color == 3)door2[i][j] = Sprite::create("doorblue3.png");
                else if (g.squares[i][j].door2.color == 4)door2[i][j] = Sprite::create("doorgreen3.png");
                door2[i][j]->setGlobalZOrder(10);
                door2[i][j]->setPosition(Vec2(origin.x + j * 40 + 28, origin.y + i * 40 + 40));
                this->addChild(door2[i][j]);
            }
            if (g.squares[i][j].candle.hascandle == 1) {
                if (g.squares[i][j].candle.state == 0) {
                    candle[i][j] = Sprite::create("candle2.png");
                }
                else candle[i][j]= Sprite::create("candle1.png");
                candle[i][j]->setGlobalZOrder(0);
                candle[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                this->addChild(candle[i][j]);
            }
            if (g.squares[i][j].button.hasbutton == 1) {
                if (g.squares[i][j].button.color == 1)button[i][j] = Sprite::create("buttonyellow.png");
                else if (g.squares[i][j].button.color == 2)button[i][j] = Sprite::create("buttonpink.png");
                else if (g.squares[i][j].button.color == 3)button[i][j] = Sprite::create("buttonblue.png");
                else if (g.squares[i][j].button.color == 4)button[i][j] = Sprite::create("buttongreen.png");
                else if (g.squares[i][j].button.color == 5)button[i][j] = Sprite::create("buttonorange.png");
                button[i][j]->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                button[i][j]->setGlobalZOrder(0);
                this->addChild(button[i][j]);
            }
            if (g.squares[i][j].word != "") {
                auto note = Sprite::create("note.png");
                note->setPosition(Vec2(origin.x + j * 40 + 40, origin.y + i * 40 + 40));
                note->setGlobalZOrder(0);
                this->addChild(note);
            }
        }
    }
   

    for (int i = 0; i < g.iniarrow.size(); i++) {
        Myarrow arrow;
        arrow.fire = 0;
        *arrow.state = 5;
        arrow.arrow= Sprite::create("arrow3.png");
        arrow.arrow->setPosition(Vec2(origin.x + g.iniarrow[i].j * 40 + 40, origin.y + g.iniarrow[i].i * 40 + 40));
        arrow.arrow->setGlobalZOrder(0);
        this->addChild(arrow.arrow);
        auto rep = awagAnimation();
        arrow.arrow->runAction(rep);
        arrows.push_back(arrow);
    }
    for (int i = 0; i < g.inifirearrow.size(); i++) {
        Myarrow arrow;
        arrow.fire = 1;
        *arrow.state = 5;
        arrow.arrow = Sprite::create("firearrow3.png");
        arrow.arrow->setPosition(Vec2(origin.x + g.inifirearrow[i].j * 40 + 40, origin.y + g.inifirearrow[i].i * 40 + 40));
        arrow.arrow->setGlobalZOrder(0);
        this->addChild(arrow.arrow);
        auto rep = awagAnimation();
        arrow.arrow->runAction(rep);
        arrows.push_back(arrow);
    }
    for (int i = 0; i < g.inibomb.size(); i++) {
        Mybomb bomb;
        *bomb.state = 5;
        bomb.bomb = Sprite::create("bomb3.png");
        bomb.bomb->setPosition(Vec2(origin.x + g.inibomb[i].j * 40 + 40, origin.y + g.inibomb[i].i * 40 + 40));
        bomb.bomb->setGlobalZOrder(0);
        this->addChild(bomb.bomb);
        auto rep = awagAnimation();
        bomb.bomb->runAction(rep);
        bombs.push_back(bomb);
    }
    for (int i = 0; i < g.inibox.size(); i++) {
        Mybox box;
        *box.state = 5;
        box.box = Sprite::create("box3.png");
        box.box->setPosition(Vec2(origin.x + g.inibox[i].j * 40 + 40, origin.y + g.inibox[i].i * 40 + 40));
        box.box->setGlobalZOrder(0);
        this->addChild(box.box);
        auto rep = awagAnimation();
        box.box->runAction(rep);
        boxes.push_back(box);
    }
    for (int i = 0; i < g.inibox2.size(); i++) {
        Mybox box;
        *box.state = 0;
        box.box = Sprite::create("box.png");
        box.box->setPosition(Vec2(origin.x + g.inibox2[i].j * 40 + 40, origin.y + g.inibox2[i].i * 40 + 40));
        box.box->setGlobalZOrder(5);
        this->addChild(box.box);
        boxes.push_back(box);
    }
    for (int i = 0; i < g.iniblood.size(); i++) {
        Sprite* blood;
        blood = Sprite::create("blood3.png");
        blood->setPosition(Vec2(origin.x + g.iniblood[i].j * 40 + 40, origin.y + g.iniblood[i].i * 40 + 40));
        blood->setGlobalZOrder(0);
        this->addChild(blood);
        auto rep = awagAnimation();
        blood->runAction(rep);
        bloods.push_back(blood);
    }

    auto cup= Sprite::create("cup.png");
    cup->setPosition(Vec2(origin.x + g.win.j * 40 + 40, origin.y + g.win.i * 40 + 40));
    cup->setGlobalZOrder(0);
    this->addChild(cup);

    auto menubox = Sprite::create("box.png");
    menubox->setPosition(Vec2(180,860));
    menubox->setGlobalZOrder(0);
    this->addChild(menubox);

    auto menuarrow = Sprite::create("arrow.png");
    menuarrow->setPosition(Vec2(300,860));
    menuarrow->setGlobalZOrder(0);
    this->addChild(menuarrow);

    auto menufirearrow = Sprite::create("firearrow.png");
    menufirearrow->setPosition(Vec2(460,860));
    menufirearrow->setGlobalZOrder(0);
    this->addChild(menufirearrow);

    auto menubomb = Sprite::create("bomb.png");
    menubomb->setPosition(Vec2(580,860));
    menubomb->setGlobalZOrder(0);
    this->addChild(menubomb);

    for (int i = 0; i < g.blood; i++) {
        blood[i] = Sprite::create("blood.png");
        blood[i]->setPosition(1200 + 40 * i, 860);
        this->addChild(blood[i]);
    }

    auto bac = Scale9Sprite::create("b_pause.png");
    auto word = Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", 36);
    word->setColor(Color3B(255, 20, 147));
    b_pause = ControlButton::create(word, bac);
    b_pause->setPosition(1700, 860);
    b_pause->setGlobalZOrder(10);
    this->addChild(b_pause);
    b_pause->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::clickEvent), Control::EventType::TOUCH_DOWN);

    //this->schedule(schedule_selector(HelloWorld::eventCheck), 1.0/60.0);
    this->scheduleUpdate();
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////some assistant functions:

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

int dis(int x, int y) {
    int x0 = getx(getj(x));
    int y0 = gety(geti(y));
    return (int)sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
}

void HelloWorld::addpath(int i, int j) {
    if (path.size() < 10) {
        path.push_back(point(i, j));
    }
    else {
        for (int i = 0; i < path.size() - 1; i++) {
            path[i] = path[i + 1];
        }
        path[path.size() - 1] = point(i, j);
    }
}

point HelloWorld::findLand() {
    int i;
    for (int i = path.size()-1; i >= 0; i--) {
        if (canPersonGo(path[i].i, path[i].j))break;
        path.pop_back();
    }
    point land = path[path.size() - 1];
    path.pop_back();
    return land;
}

int HelloWorld::canArrowGo(int i, int j) {
    if (constrain(i, j) == 0)return 0;
    if (hasBox(i, j))return 0;
    if (g.squares[i][j].type == 1|| g.squares[i][j].type == 2)return 0;
    return 1;
}

int HelloWorld::canPersonGo(int i, int j) { //not include the door judgement
    if (constrain(i, j) == 0)return 0;
    if (g.squares[i][j].type >= 1&&g.squares[i][j].type<=2)return 0;
    if (g.squares[i][j].type == 6)return 0;
    if (isWater(i,j))return 0;
    if (g.squares[i][j].candle.hascandle == 1)return 0;
    return 1;
}

int HelloWorld::canBoxGo(int i, int j, int dir) {
    if (constrain(i, j) == 0)return 0;
    if (i == posi && j == posj)return 0;
    if (g.squares[i][j].type == 1|| g.squares[i][j].type == 2)return 0;
    if (g.squares[i][j].type == 6)return 0;
    if (isWater(i,j))return 2;
    if (hasBox(i,j) == 1)return 0;
    if (g.squares[i][j].candle.hascandle == 1)return 0;
    if (dir == 0) {
        if (checkdoor1(i, j) == 0)return 0;
    }
    else if (dir == 1) {
        if (checkdoor1(i + 1, j) == 0)return 0;
    }
    else if (dir == 2) {
        if (checkdoor2(i, j + 1) == 0)return 0;
    }
    else if (dir == 3) {
        if (checkdoor2(i, j) == 0)return 0;
    }
    for (auto bomb : bombs) {
        if (getpos(bomb.bomb).i == i && getpos(bomb.bomb).j == j)return 0;
    }
    return 1;
}

int HelloWorld::checkdoor1(int i, int j) {
    if (g.squares[i][j].door1.hasdoor == 0 || g.squares[i][j].door1.status == 1)return 1;
    return 0;
}

int HelloWorld::checkdoor2(int i, int j) {
    if (g.squares[i][j].door2.hasdoor == 0 || g.squares[i][j].door2.status == 1)return 1;
    return 0;
}

bool constrain(int i, int j) {
    if (i < 0)return 0;
    if (i >= 20)return 0;
    if (j < 0)return 0;
    if (j >= 43)return 0;
    return 1;
}

void HelloWorld::doorChange(int i, int j, int color,int mode) {
    if (constrain(i, j) == 0)return;
    if (g.squares[i][j].door1.hasdoor == 1 &&mode==0&& g.squares[i][j].door1.status==0&& g.squares[i][j].door1.color == color) {
        g.squares[i][j].door1.nowbutton++;
        if (g.squares[i][j].door1.nowbutton == g.squares[i][j].door1.needbutton) {
            this->removeChild(door1[i][j]);
            if (color == 0) {
                door1[i][j] = Sprite::create("doorred2.png");
            }
            else if (color == 1) {
                door1[i][j] = Sprite::create("dooryellow2.png");
            }
            else if (color == 2) {
                door1[i][j] = Sprite::create("doorpink2.png");
            }
            else if (color == 3) {
                door1[i][j] = Sprite::create("doorblue2.png");
            }
            else if (color == 4) {
                door1[i][j] = Sprite::create("doorgreen2.png");
            }
            door1[i][j]->setGlobalZOrder(10);
            door1[i][j]->setPosition(Vec2(j * 40 + 30, i * 40 + 40));
            this->addChild(door1[i][j]);
            g.squares[i][j].door1.status = 1;
        }
    }
    else if (g.squares[i][j].door2.hasdoor == 1 &&mode==0&& g.squares[i][j].door2.status == 0 && g.squares[i][j].door2.color == color) {
        g.squares[i][j].door2.nowbutton++;
        if (g.squares[i][j].door2.nowbutton == g.squares[i][j].door2.needbutton) {
            this->removeChild(door2[i][j]);
            if (color == 0) {
                door2[i][j] = Sprite::create("doorred2.png");
            }
            else if (color == 1) {
                door2[i][j] = Sprite::create("dooryellow2.png");
            }
            else if (color == 2) {
                door2[i][j] = Sprite::create("doorpink2.png");
            }
            else if (color == 3) {
                door2[i][j] = Sprite::create("doorblue2.png");
            }
            else if (color == 4) {
                door2[i][j] = Sprite::create("doorgreen2.png");
            }
            door2[i][j]->setGlobalZOrder(10);
            door2[i][j]->setPosition(Vec2(j * 40 + 30, i * 40 + 40));
            this->addChild(door2[i][j]);
            g.squares[i][j].door2.status = 1;
        }
    }
    else if (g.squares[i][j].door1.hasdoor == 1 &&mode==1&& g.squares[i][j].door1.color == color) {
        g.squares[i][j].door1.nowbutton--;
        if (g.squares[i][j].door1.status == 1) {
            this->removeChild(door1[i][j]);
            if (color == 0) {
                door1[i][j] = Sprite::create("doorred1.png");
            }
            else if (color == 1) {
                door1[i][j] = Sprite::create("dooryellow1.png");
            }
            else if (color == 2) {
                door1[i][j] = Sprite::create("doorpink1.png");
            }
            else if (color == 3) {
                door1[i][j] = Sprite::create("doorblue1.png");
            }
            else if (color == 4) {
                door1[i][j] = Sprite::create("doorgreen1.png");
            }
            door1[i][j]->setGlobalZOrder(10);
            door1[i][j]->setPosition(Vec2(j * 40 + 40, i * 40 + 40));
            this->addChild(door1[i][j]);
            g.squares[i][j].door1.status = 0;
        }
    }
    else if (g.squares[i][j].door2.hasdoor == 1 && mode==1 && g.squares[i][j].door2.color == color) {
        g.squares[i][j].door2.nowbutton--;
        if (g.squares[i][j].door2.status == 1) {
            this->removeChild(door2[i][j]);
            if (color == 0) {
                door2[i][j] = Sprite::create("doorred3.png");
            }
            else if (color == 1) {
                door2[i][j] = Sprite::create("dooryellow3.png");
            }
            else if (color == 2) {
                door2[i][j] = Sprite::create("doorpink3.png");
            }
            else if (color == 3) {
                door2[i][j] = Sprite::create("doorblue3.png");
            }
            else if (color == 4) {
                door2[i][j] = Sprite::create("doorgreen3.png");
            }
            door2[i][j]->setGlobalZOrder(10);
            door2[i][j]->setPosition(Vec2(j * 40 + 28, i * 40 + 40));
            this->addChild(door2[i][j]);
            g.squares[i][j].door2.status = 0;
        }
    }
}

void HelloWorld::boardChange(int i, int j,int mode) {
    if (constrain(i, j) == 0)return;
    if (g.squares[i][j].board.hasboard == 1 && mode == 0 && g.squares[i][j].board.state == 0) {
        g.squares[i][j].board.nowbutton++;
        if (g.squares[i][j].board.nowbutton == g.squares[i][j].board.needbutton) {
            board[i][j]->setOpacity(255);
            g.squares[i][j].board.state = 1;
            for (auto box : boxes) {
                if (getpos(box.box) == point(i, j)) {
                    *box.state = 0;
                    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("box.png");
                    box.box->setTexture(texture);
                    box.box->setGlobalZOrder(5);
                }
            }
            for (auto bomb : bombs) {
                if (getpos(bomb.bomb) == point(i, j)) {
                    *bomb.state = 2;
                    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bomb2.png");
                    bomb.bomb->setTexture(texture);
                    bomb.bomb->setGlobalZOrder(20);
                }
            }
        }
    }
    
    else if (g.squares[i][j].board.hasboard == 1 && mode == 1) {
        g.squares[i][j].board.nowbutton--;
        if (g.squares[i][j].board.state == 1) {
            board[i][j]->setOpacity(130);
            g.squares[i][j].board.state = 0;
            if (posi == i && posj == j) {
                point land = findLand();
                //auto seq = dropwaterSeq2(g.squares[i][j].board.toi, g.squares[i][j].board.toj);
                auto seq = dropwaterSeq2(land.i, land.j);
                person->runAction(seq);
            }
            for (auto box : boxes) {
                if (getpos(box.box) == point(i, j)&&*box.state!=1) {
                    *box.state = 3;
                    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("box4.png");
                    box.box->setTexture(texture);
                }
            }
            for (auto bomb : bombs) {
                if (getpos(bomb.bomb) == point(i, j)) {
                    *bomb.state = 3;
                    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bomb4.png");
                    bomb.bomb->setTexture(texture);
                    bomb.bomb->stopActionByTag(1);
                }
            }
        }
    }
}



void HelloWorld::checkonto(int i, int j) {
    if (g.squares[i][j].button.hasbutton == 1) {
        if (g.squares[i][j].button.color <= 4) {
            doorChange(g.squares[i][j].button.doorpos.i, g.squares[i][j].button.doorpos.j, g.squares[i][j].button.color, 0);
        }
        else if (g.squares[i][j].button.color == 5) {
            boardChange(g.squares[i][j].button.doorpos.i, g.squares[i][j].button.doorpos.j, 0);
        }
    }
    
}


void HelloWorld::checkleave(int i, int j) {
    if (g.squares[i][j].button.hasbutton == 1) {
        if (g.squares[i][j].button.color <= 4) {
            doorChange(g.squares[i][j].button.doorpos.i, g.squares[i][j].button.doorpos.j, g.squares[i][j].button.color, 1);
        }
        else if (g.squares[i][j].button.color == 5) {
            boardChange(g.squares[i][j].button.doorpos.i, g.squares[i][j].button.doorpos.j, 1);
        }
    }
}

void HelloWorld::boxonto(Mybox box, int i, int j) {
    if (isWater(i,j)) {
        *box.state = 3;
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("box4.png");
        box.box->setTexture(texture);
    }
    if (g.squares[i][j].type == 4) {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("campfire2.png");
        s[i][j]->setGlobalZOrder(0);
        s[i][j]->setTexture(texture);
        g.squares[i][j].type = 5;
    }
}

void HelloWorld::bombonto(Mybomb bomb, int i, int j) {
    if (isWater(i, j)) {
        *bomb.state = 3;
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bomb4.png");
        bomb.bomb->setTexture(texture);
        bomb.bomb->setGlobalZOrder(0);
        bomb.bomb->stopActionByTag(1);
    }
    if (g.squares[i][j].type == 4) {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("campfire2.png");
        s[i][j]->setGlobalZOrder(0);
        s[i][j]->setTexture(texture);
        g.squares[i][j].type = 5;
    }
}

void HelloWorld::renewStorage(int type) {
    if (type == 0) {
        menu0->setString(": " + to_string(g.boxnum));
    }
    else if (type == 1) {
        menu1->setString(": " + to_string(g.arrownum));
    }
    else if (type == 2) {
        menu2->setString(": " + to_string(g.firearrownum));
    }
    else if (type == 3) {
        menu3->setString(": " + to_string(g.bombnum));
    }
}

void HelloWorld::renewBlood(int num) {
    for (int i = 0; i < g.blood; i++) {
        this->removeChild(blood[i]);
    }
    if (g.blood + num <= 0) {
        note2 = Sprite::create("wordarea2.png");
        note2->setPosition(Vec2(900, 450));
        note2->setGlobalZOrder(30);
        note2->setOpacity(140);
        this->addChild(note2);
        noteword = Label::createWithTTF("You lose.", "fonts/Marker Felt.ttf", 48);
        noteword->setPosition(Vec2(900, 500));
        noteword->setTextColor(Color4B(0, 0, 0, 255));
        noteword->setGlobalZOrder(30);
        this->addChild(noteword);
        canop = 0;
        over = 1;
        winlose();
    }
    else {
        g.blood += num;
        if (g.blood > 10)g.blood = 10;
        for (int i = 0; i < g.blood; i++) {
            blood[i] = Sprite::create("blood.png");
            blood[i]->setPosition(1200 + 40 * i, 860);
            this->addChild(blood[i]);
        }
    }
}

void HelloWorld::winlose() {
    Scale9Sprite* bac;
    Label* word;

    bac = Scale9Sprite::create("b_select.png");
    bac->setGlobalZOrder(30);
    word = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 36);
    word->setColor(Color3B(0, 0, 0));
    word->setGlobalZOrder(30);
    b_quit = ControlButton::create(word, bac);
    b_quit->setPosition(900, 250);
    b_quit->setGlobalZOrder(30);
    this->addChild(b_quit);
    b_quit->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::clickEvent), Control::EventType::TOUCH_DOWN);

    bac = Scale9Sprite::create("b_select.png");
    bac->setGlobalZOrder(30);
    word = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 36);
    word->setColor(Color3B(0, 0, 0));
    word->setGlobalZOrder(30);
    b_restart = ControlButton::create(word, bac);
    b_restart->setPosition(900, 350);
    this->addChild(b_restart);
    b_restart->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::clickEvent), Control::EventType::TOUCH_DOWN);
}


void HelloWorld::persononto(int i, int j) {
    if (g.win == point(i, j)) {
        note2 = Sprite::create("wordarea2.png");
        note2->setPosition(Vec2(900, 450));
        note2->setGlobalZOrder(30);
        note2->setOpacity(140);
        this->addChild(note2);
        
        note = Sprite::create("win.png");
        note->setPosition(Vec2(900,450));
        note->setGlobalZOrder(30);
        this->addChild(note);
        noteword = Label::createWithTTF("You win!", "fonts/Marker Felt.ttf", 48);
        noteword->setPosition(Vec2(900, 500));
        noteword->setTextColor(Color4B(255, 0, 0, 255));
        noteword->setGlobalZOrder(30);
        this->addChild(noteword);
        canop = 0;
        over = 1;

        winlose();
    }
    else if (g.squares[i][j].word != "") {
        note = Sprite::create("wordarea.png");
        note->setPosition(Vec2(1100, 450));
        note->setGlobalZOrder(30);
        note->setOpacity(150);
        this->addChild(note);
        noteword = Label::createWithTTF(g.squares[i][j].word, "fonts/Marker Felt.ttf", g.squares[i][j].wordsize);
        noteword->setPosition(Vec2(1100, 450));
        noteword->setTextColor(Color4B(0, 0, 0, 255));
        noteword->setGlobalZOrder(30);
        this->addChild(noteword);
    }
    for (auto it = boxes.begin(); it != boxes.end(); it++) {
        if (*it->state==5&&getpos(it->box) == point(i, j)) {
            g.boxnum++;
            renewStorage(0);
            this->removeChild(it->box);
            boxes.erase(it);
            break;
        }
    }
    for (auto it = arrows.begin(); it != arrows.end(); it++) {
        if (*it->state == 5 && getpos(it->arrow) == point(i, j)) {
            if (it->fire == 0) {
                g.arrownum++;
                renewStorage(1);
                this->removeChild(it->arrow);
                arrows.erase(it);
                break;
            }
            else {
                g.firearrownum++;
                renewStorage(2);
                this->removeChild(it->arrow);
                arrows.erase(it);
                break;
            }
        }
    }
    for (auto it = bombs.begin(); it != bombs.end(); it++) {
        if (*it->state == 5 && getpos(it->bomb) == point(i, j)) {
            g.bombnum++;
            renewStorage(3);
            this->removeChild(it->bomb);
            bombs.erase(it);
            break;
        }
    }
    for (auto it = bloods.begin(); it != bloods.end(); it++) {
        if (getpos(*it) == point(i, j)) {
            renewBlood(1);
            this->removeChild(*it);
            bloods.erase(it);
            break;
        }
    }
    if (g.squares[i][j].type == 4) {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("campfire2.png");
        s[i][j]->setGlobalZOrder(0);
        s[i][j]->setTexture(texture);
        g.squares[i][j].type = 5;
        renewBlood(-3);
    }
}

void HelloWorld::personleave(int i, int j) {
    if (g.squares[i][j].word != "") {
        this->removeChild(note);
        this->removeChild(noteword);
    }
}


void HelloWorld::candleLight(int i, int j) {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("candle1.png");
    candle[i][j]->setTexture(texture);
    g.squares[i][j].candle.state = 1;
    if (g.squares[g.squares[i][j].candle.doorpos.i][g.squares[i][j].candle.doorpos.j].door1.dooropen() || g.squares[g.squares[i][j].candle.doorpos.i][g.squares[i][j].candle.doorpos.j].door2.dooropen()) {
        doorChange(g.squares[i][j].candle.doorpos.i, g.squares[i][j].candle.doorpos.j, 0, 1);
    }
    else {
        doorChange(g.squares[i][j].candle.doorpos.i, g.squares[i][j].candle.doorpos.j, 0, 0);
    }
}

void HelloWorld::candleDark(int i, int j) {
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("candle2.png");
    candle[i][j]->setTexture(texture);
    g.squares[i][j].candle.state = 0;
    if (g.squares[g.squares[i][j].candle.doorpos.i][g.squares[i][j].candle.doorpos.j].door1.dooropen() || g.squares[g.squares[i][j].candle.doorpos.i][g.squares[i][j].candle.doorpos.j].door2.dooropen()) {
        doorChange(g.squares[i][j].candle.doorpos.i, g.squares[i][j].candle.doorpos.j, 0, 1);
    }
    else {
        doorChange(g.squares[i][j].candle.doorpos.i, g.squares[i][j].candle.doorpos.j, 0, 0);
    }
}

void HelloWorld::setPic(Sprite* spr,string s) {
    auto ani = Animation::create();
    ani->addSpriteFrameWithFile(s);
    ani->setDelayPerUnit(0.01);
    ani->setRestoreOriginalFrame(false);
    auto act = Animate::create(ani);
    spr->runAction(act);
}

Animation* HelloWorld::getAnimation(string name, float delay, int num) {//now no use
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

Animation* HelloWorld::explodeAnimation1() {
    auto ani = Animation::create();
    ani->addSpriteFrameWithFile("bomb.png");
    ani->setDelayPerUnit(0.2f);
    ani->setRestoreOriginalFrame(false);
    return ani;
}

Animation* HelloWorld::explodeAnimation2() {
    auto ani = Animation::create();
    ani->addSpriteFrameWithFile("explode.png");
    ani->setDelayPerUnit(0.2f);
    ani->setRestoreOriginalFrame(false);
    return ani;
}

Animation* HelloWorld::smokeAnimation() {
    auto ani = Animation::create();
    ani->addSpriteFrameWithFile("smoke.png");
    ani->setDelayPerUnit(1);
    ani->setRestoreOriginalFrame(false);
    return ani;
}

RepeatForever* HelloWorld::awagAnimation() {
    auto act1 = MoveBy::create(0.5, Point(0,6));
    auto act2 = MoveBy::create(1, Point(0, -12));
    auto act3 = MoveBy::create(0.5, Point(0, 6));
    auto seq = Sequence::create(act1, act2, act3, NULL);
    auto rep = RepeatForever::create(seq);
    return rep;
}

Animation* dropwaterAnimation() {
    auto ani = Animation::create();
    if(direction==0)ani->addSpriteFrameWithFile("pback.png");
    else if (direction == 1)ani->addSpriteFrameWithFile("pfront.png");
    else if (direction == 2)ani->addSpriteFrameWithFile("pleft.png");
    else if (direction == 3)ani->addSpriteFrameWithFile("pright.png");
    ani->addSpriteFrameWithFile("water2.png");
    ani->setDelayPerUnit(0.05f);
    ani->setRestoreOriginalFrame(false);
    return ani;
}

Animation* dropwaterAnimation2() {
    auto ani = Animation::create();
    ani->addSpriteFrameWithFile("water2.png");
    if (direction == 0)ani->addSpriteFrameWithFile("pback.png");
    else if (direction == 1)ani->addSpriteFrameWithFile("pfront.png");
    else if (direction == 2)ani->addSpriteFrameWithFile("pleft.png");
    else if (direction == 3)ani->addSpriteFrameWithFile("pright.png");
    ani->setDelayPerUnit(0.2f);
    ani->setRestoreOriginalFrame(false);
    return ani;
}

Sequence* HelloWorld::dropwaterSeq(int dir) {
    auto ani = dropwaterAnimation();
    auto act = Animate::create(ani);
    auto callfunc = CallFunc::create([=] {
        renewBlood(-1);
        });
    auto ani2= dropwaterAnimation2();
    auto act2 = Animate::create(ani2);
    MoveBy* move1, *move2;
    if (dir == 0) {
        move1 = MoveBy::create(0.1, Point(0, 40));
        move2 = MoveBy::create(0.1, Point(0, -40));
    }
    else if (dir == 1) {
        move1 = MoveBy::create(0.1, Point(0, -40));
        move2 = MoveBy::create(0.1, Point(0, 40));
    }
    else if (dir == 2) {
        move1 = MoveBy::create(0.1, Point(-40,0));
        move2 = MoveBy::create(0.1, Point(40,0));
    }
    else if (dir == 3) {
        move1 = MoveBy::create(0.1, Point(40,0));
        move2 = MoveBy::create(0.1, Point(-40,0));
    }
    auto blink = Blink::create(1, 3);
    auto startcall = CallFunc::create([=] {
        canop = 0;
        });
    auto finishcall = CallFunc::create([=] {
        if(over==0)canop = 1;
        checkonto(posi, posj);
        persononto(posi, posj);
        });
    auto seq = Sequence::create(startcall, move1, act, callfunc, cocos2d::DelayTime::create(0.3), act2,move2,blink,finishcall, NULL);
    return seq;
}

Sequence* HelloWorld::dropwaterSeq2(int i, int j) {
    auto ani = dropwaterAnimation();
    auto act = Animate::create(ani);
    auto callfunc = CallFunc::create([=] {
        renewBlood(-1);
        });
    auto ani2 = dropwaterAnimation2();
    auto act2 = Animate::create(ani2);
    auto blink = Blink::create(1, 3);
    auto startcall = CallFunc::create([=] {
        canop = 0;
        });
    auto finishcall = CallFunc::create([=] {
        if (over == 0)canop = 1;
        posi = i;
        posj = j;
        addpath(posi, posj);
        });
    auto move = MoveTo::create(dis(getx(posj), getx(j), gety(posi), gety(i)) / 600.0, Point(getx(j), gety(i)));
    auto seq = Sequence::create(startcall, act, callfunc, cocos2d::DelayTime::create(0.3), act2, move, blink, finishcall, NULL);
    return seq;
}



point HelloWorld::getpos(cocos2d::Sprite* spri) {
    return point(geti(spri->getPositionY()), getj(spri->getPositionX()));
}

int HelloWorld::hasBox(int i, int j) {
    for (auto box : boxes) {
        if (getpos(box.box) == point(i, j) && *box.state != 3&&*box.state!=5)return 1;
    }
    return 0;
}

int HelloWorld::hasBox2(int i, int j) {
    for (auto box : boxes) {
        if (getpos(box.box) == point(i, j) && *box.state == 3)return 1;
    }
    return 0;
}


bool HelloWorld::isWater(int i, int j) {
    if(constrain(i, j) && g.squares[i][j].type == 3 && hasBox2(i, j) == 0&&g.squares[i][j].board.cango()==0)return 1;
    return 0;
}

void HelloWorld::explodeop(int i, int j, int dir) {
    
}

void HelloWorld::explodeop1(int i,int j, int dir) {
    if (posi == i && posj == j) {
        renewBlood(-5);
    }
    if (constrain(i, j) && g.squares[i][j].type == 1) {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("wall2.png");
        s[i][j]->setGlobalZOrder(0);
        s[i][j]->setTexture(texture);
        g.squares[i][j].type = 0;
    }
    if (constrain(i, j) && g.squares[i][j].candle.notlight() == 1) {
        candleLight(i, j);
    }
    else if (constrain(i, j) && g.squares[i][j].candle.light() == 1) {
        candleDark(i, j);
    }
    if (constrain(i, j) && g.squares[i][j].type == 5) {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("campfire1.png");
        s[i][j]->setGlobalZOrder(0);
        s[i][j]->setTexture(texture);
        g.squares[i][j].type = 4;
    }

    for (auto bomb : bombs) {
        if (*bomb.state == 3)continue;
        if (getpos(bomb.bomb) == point(i, j) && (*bomb.state == 2||*bomb.state==5)) {
            if (*bomb.state == 5) {
                bombonto(bomb,i, j);
                checkonto(i, j);
            }
            *bomb.state = 0;
            bomb.bomb->stopAllActions();
            setPic(bomb.bomb, "bomb.png");
            //CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("bomb.png");
            //bomb.bomb->setTexture(texture);
            auto ani1 = explodeAnimation1();
            auto ani2 = explodeAnimation2();
            auto explodecall1 = CallFunc::create([=] {
                *bomb.state = 1;
                });
            auto explodecall2 = CallFunc::create([=] {
                bombexplode1(getpos(bomb.bomb).i, getpos(bomb.bomb).j);
                checkleave(getpos(bomb.bomb).i, getpos(bomb.bomb).j);
                });
            auto explodecall3 = CallFunc::create([=] {
                this->removeChild(bomb.bomb, true);
                for (auto i = bombs.begin(); i != bombs.end(); i++) {
                    if (i->bomb == bomb.bomb) {
                        bombs.erase(i);
                        break;
                    }
                }
                bombexplode(i, j);
                });

            auto act1 = Animate::create(ani1);
            auto act2 = Animate::create(ani2);
            auto seq = Sequence::create(cocos2d::DelayTime::create(2), explodecall1,
                act1, explodecall2, act2, cocos2d::DelayTime::create(0.3), explodecall3, NULL);
            bomb.bomb->runAction(seq);
            seq->setTag(1);
        }
    }
    if (dir >= 0) {
        for (auto box : boxes) {
            if (*box.state == 3)continue;
            if (*box.state == 5)continue;
            if (getpos(box.box) == point(i, j)) {
                if (dir == 0) {
                    *box.state = 1;
                    *box.dir = 0;
                    auto act = MoveBy::create((18 - i) / 15.0, Point(0, (18 - i) * 40));
                    box.box->runAction(act);
                    act->setTag(1);
                    checkleave(i, j);
                }
                else if (dir == 1) {
                    *box.state = 1;
                    *box.dir = 1;
                    auto act = MoveBy::create((i-1) / 15.0, Point(0, (1-i) * 40));
                    box.box->runAction(act);
                    act->setTag(1);
                    checkleave(i, j);
                }
                else if (dir == 2) {
                    *box.state = 1;
                    *box.dir = 2;
                    auto act = MoveBy::create((j-1) / 15.0, Point((1-j) * 40,0));
                    box.box->runAction(act);
                    act->setTag(1);
                    checkleave(i, j);
                }
                else if (dir == 3) {
                    *box.state = 1;
                    *box.dir = 3;
                    auto act = MoveBy::create((41 - j) / 15.0, Point((41 - j) * 40,0));
                    box.box->runAction(act);
                    act->setTag(1);
                    checkleave(i, j);
                }
            }
        }
    }
    for (auto it = boxes.begin(); it != boxes.end(); it++) {
        if (*it->state == 5 && getpos(it->box) == point(i, j)) {
            g.boxnum++;
            renewStorage(0);
            this->removeChild(it->box);
            boxes.erase(it);
            break;
        }
    }
    for (auto it = arrows.begin(); it != arrows.end(); it++) {
        if (*it->state == 5 && getpos(it->arrow) == point(i, j)) {
            if (it->fire == 0) {
                this->removeChild(it->arrow);
                arrows.erase(it);
                break;
            }
            else {
                this->removeChild(it->arrow);
                arrows.erase(it);
                break;
            }
        }
    }
    for (auto it = bombs.begin(); it != bombs.end(); it++) {
        if (*it->state == 5 && getpos(it->bomb) == point(i, j)) {
            this->removeChild(it->bomb);
            bombs.erase(it);
            break;
        }
    }
    for (auto it = bloods.begin(); it != bloods.end(); it++) {
        if (getpos(*it) == point(i, j)) {
            this->removeChild(*it);
            bloods.erase(it);
            break;
        }
    }
}

void HelloWorld::explodeop2(int i, int j) {
    if (constrain(i, j) && g.squares[i][j].type == 5) {
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("campfire1.png");
        s[i][j]->setGlobalZOrder(0);
        s[i][j]->setTexture(texture);
        g.squares[i][j].type = 4;
    }
}

void HelloWorld::bombexplode(int i, int j) {
    explodeop(i - 1, j - 1,-1);
    explodeop(i - 1, j, 1);
    explodeop(i - 1, j + 1,-1);
    explodeop(i, j - 1, 2);
    explodeop(i, j + 1, 3);
    explodeop(i + 1, j - 1, -1);
    explodeop(i + 1, j, 0);
    explodeop(i + 1, j + 1, -1);
}

void HelloWorld::bombexplode1(int i, int j) {
    explodeop1(i - 1, j - 1, -1);
    explodeop1(i - 1, j, 1);
    explodeop1(i - 1, j + 1, -1);
    explodeop1(i, j - 1, 2);
    explodeop1(i, j + 1, 3);
    explodeop1(i + 1, j - 1, -1);
    explodeop1(i + 1, j, 0);
    explodeop1(i + 1, j + 1, -1);
    explodeop2(i, j);
}

int dis(int a,int b,int c,int d) {
    return(sqrt((a - b) * (a - b) + (c - d) * (c - d)));
}

void HelloWorld::goTo(Mybox b,int x, int y, int i, int j) {
    auto callf = CallFunc::create([=] {
        *b.state = 0;
        checkonto(i, j);
        boxonto(b, i, j);
        });
    *b.state = 2;
    b.box->stopAllActionsByTag(1);
    auto move = MoveTo::create(dis(x, getx(j), y, gety(i)) / 600.0, Point(getx(j), gety(i)));
    auto seq = Sequence::create(move, callf, NULL);
    b.box->runAction(seq);
}

void HelloWorld::stopActInTime(Mybox b, float t) {
    auto callf = CallFunc::create([=] {
        b.box->stopAllActionsByTag(1);
        *b.state = 0;
        });
    auto seq = Sequence::create(cocos2d::DelayTime::create(t), callf,NULL);
    b.box->runAction(seq);
}

void HelloWorld::stopActInTime2(Myarrow a, float t) {
    auto callf = CallFunc::create([=] {
        a.arrow->stopAllActionsByTag(1);
        *a.state = 1;
        });
    auto callf2 = CallFunc::create([=] {
        for (auto i = arrows.begin(); i != arrows.end(); i++) {
            if (i->arrow == a.arrow) {
                arrows.erase(i);
                break;
            }
        }
        this->removeChild(a.arrow,1);
        });
    *a.state = 2;
    auto seq = Sequence::create(cocos2d::DelayTime::create(t), callf, cocos2d::DelayTime::create(0.5), callf2,NULL);
    a.arrow->runAction(seq);
}

void HelloWorld::stopActInTime3(Myarrow a, float t, int dir) {
    auto ani = smokeAnimation();
    auto act = Animate::create(ani);
    int i = getpos(a.arrow).i;
    int j = getpos(a.arrow).j;
    auto callf = CallFunc::create([=] {
        for (auto i = arrows.begin(); i != arrows.end(); i++) {
            if (i->arrow == a.arrow) {
                arrows.erase(i);
                break;
            }
        }
        this->removeChild(a.arrow, 1);
        auto ani = smokeAnimation();
        auto act = Animate::create(ani);
        if (dir == 0) {
            auto ccf = CallFunc::create([=] {
                this->removeChild(s[i+1][j]);
                });
            auto seq = Sequence::create(act,ccf, NULL);
            g.squares[i + 1][j].type = 0;
            s[i + 1][j]->runAction(seq);
        }
        else if (dir == 1) {
            auto ccf = CallFunc::create([=] {
                this->removeChild(s[i - 1][j]);
                });
            auto seq = Sequence::create(act, ccf, NULL);
            g.squares[i - 1][j].type = 0;
            s[i - 1][j]->runAction(seq);
        }
        else if (dir == 2) {
            auto ccf = CallFunc::create([=] {
                this->removeChild(s[i][j-1]);
                });
            auto seq = Sequence::create(act, ccf, NULL);
            g.squares[i][j-1].type = 0;
            s[i][j-1]->runAction(seq);
        }
        else if (dir == 3) {
            auto ccf = CallFunc::create([=] {
                this->removeChild(s[i][j+1]);
                });
            auto seq = Sequence::create(act, ccf, NULL);
            g.squares[i][j+1].type = 0;
            s[i][j+1]->runAction(seq);
        }
        
        });
    *a.state = 2;
    auto seq = Sequence::create(cocos2d::DelayTime::create(t), callf,NULL);
    a.arrow->runAction(seq);
}

void HelloWorld::updateinfo() {

}



void HelloWorld::update(float dt) {
    for (auto& arrow : arrows) {
        if (dis(arrow.arrow->getPositionX(), arrow.arrow->getPositionY()) > 10)continue;
        if (arrow.fire == 1 && g.squares[getpos(arrow.arrow).i][getpos(arrow.arrow).j].candle.notlight() == 1) {
            candleLight(getpos(arrow.arrow).i, getpos(arrow.arrow).j);
        }
        if (arrow.fire == 0 && g.squares[getpos(arrow.arrow).i][getpos(arrow.arrow).j].candle.light() == 1) {
            candleDark(getpos(arrow.arrow).i, getpos(arrow.arrow).j);
        }
        if (arrow.fire == 1 && g.squares[getpos(arrow.arrow).i][getpos(arrow.arrow).j].type == 5) {
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("campfire1.png");
            s[getpos(arrow.arrow).i][getpos(arrow.arrow).j]->setGlobalZOrder(0);
            s[getpos(arrow.arrow).i][getpos(arrow.arrow).j]->setTexture(texture);
            g.squares[getpos(arrow.arrow).i][getpos(arrow.arrow).j].type = 4;
        }
        if (arrow.fire == 0 && g.squares[getpos(arrow.arrow).i][getpos(arrow.arrow).j].type == 4) {
            arrow.fire = 1;
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("firearrow.png");
            arrow.arrow->setTexture(texture);
        }
        for (auto b = bombs.begin(); b != bombs.end();) {
            if (*b->state == 3) {
                b++;
                continue;
            }
            if (arrow.fire == 0 && getpos(arrow.arrow) == getpos(b->bomb) && *b->state == 0) {
                b->bomb->stopAllActions();
                Mybomb newbomb;
                newbomb.bomb = Sprite::create("bomb2.png");
                newbomb.bomb->setPosition(Vec2(b->bomb->getPositionX(), b->bomb->getPositionY()));
                newbomb.bomb->setGlobalZOrder(20);
                newbomb.state = new int;
                *newbomb.state = 2;
                this->addChild(newbomb.bomb);
                this->removeChild(b->bomb);
                b = bombs.erase(b);
                bombs.push_back(newbomb);
            }
            else if (arrow.fire == 1 && getpos(arrow.arrow) == getpos(b->bomb) && (*b->state == 2||*b->state==5)) {
                if (*b->state == 5) {
                    bombonto(*b, getpos(b->bomb).i, getpos(b->bomb).j);
                    checkonto(getpos(b->bomb).i, getpos(b->bomb).j);
                }
                Mybomb newbomb;
                newbomb.bomb = Sprite::create("bomb.png");
                newbomb.bomb->setPosition(Vec2(b->bomb->getPositionX(), b->bomb->getPositionY()));
                newbomb.bomb->setGlobalZOrder(20);
                newbomb.state = new int;
                *newbomb.state = 0;
                this->addChild(newbomb.bomb);
                this->removeChild(b->bomb);
                b = bombs.erase(b);
                bombs.push_back(newbomb);
                auto ani1 = explodeAnimation1();
                auto ani2 = explodeAnimation2();
                int i = geti(newbomb.bomb->getPositionY());
                int j = getj(newbomb.bomb->getPositionX());
                auto explodecall1 = CallFunc::create([=] {
                    *newbomb.state = 1;
                    });
                auto explodecall2 = CallFunc::create([=] {
                    bombexplode1(getpos(newbomb.bomb).i, getpos(newbomb.bomb).j);
                    checkleave(getpos(newbomb.bomb).i, getpos(newbomb.bomb).j);
                    });
                auto explodecall3 = CallFunc::create([=] {
                    this->removeChild(newbomb.bomb);
                    for (auto i = bombs.begin(); i != bombs.end(); i++) {
                        if (i->bomb == newbomb.bomb) {
                            bombs.erase(i);
                            break;
                        }
                    }

                    bombexplode(i, j);
                    });

                auto act1 = Animate::create(ani1);
                auto act2 = Animate::create(ani2);
                auto seq = Sequence::create(cocos2d::DelayTime::create(2), explodecall1,
                    act1, explodecall2, act2, cocos2d::DelayTime::create(0.3), explodecall3, NULL);
                newbomb.bomb->runAction(seq);
                seq->setTag(1);
            }
            else {
                b++;
            }
        }
        if (*arrow.state == 0) {
            if (*arrow.dir == 0) {
                int offset = gety(geti(arrow.arrow->getPositionY())) - arrow.arrow->getPositionY();
                if (offset >= 0) {
                    if (canArrowGo(getpos(arrow.arrow).i + 1, getpos(arrow.arrow).j) == 0) {
                        stopActInTime2(arrow, (offset) / 600.0);
                    }
                    else if (arrow.fire == 1 && g.squares[getpos(arrow.arrow).i + 1][getpos(arrow.arrow).j].type == 6) {
                        stopActInTime3(arrow, (offset) / 600.0,0);
                    }
                }
            }
            else if (*arrow.dir == 1) {
                int offset = -gety(geti(arrow.arrow->getPositionY())) + arrow.arrow->getPositionY();
                if (offset >= 0) {
                    if (canArrowGo(getpos(arrow.arrow).i - 1, getpos(arrow.arrow).j) == 0) {
                        stopActInTime2(arrow, (offset) / 600.0);
                    }
                    else if (arrow.fire == 1 && g.squares[getpos(arrow.arrow).i - 1][getpos(arrow.arrow).j].type == 6) {
                        stopActInTime3(arrow, (offset) / 600.0,1);
                    }
                }
            }
            else if (*arrow.dir == 2) {
                int offset = -getx(getj(arrow.arrow->getPositionX())) + arrow.arrow->getPositionX();
                if (offset >= 0) {
                    if (canArrowGo(getpos(arrow.arrow).i, getpos(arrow.arrow).j - 1) == 0) {
                        stopActInTime2(arrow, (offset) / 600.0);
                    }
                    else if (arrow.fire == 1 && g.squares[getpos(arrow.arrow).i][getpos(arrow.arrow).j-1].type == 6) {
                        stopActInTime3(arrow, (offset) / 600.0,2);
                    }
                }
            }
            else if (*arrow.dir == 3) {
                int offset = getx(getj(arrow.arrow->getPositionX())) - arrow.arrow->getPositionX();
                if (offset >= 0) {
                    if (canArrowGo(getpos(arrow.arrow).i, getpos(arrow.arrow).j + 1) == 0) {
                        stopActInTime2(arrow, (offset) / 600.0);
                    }
                    else if (arrow.fire == 1 && g.squares[getpos(arrow.arrow).i][getpos(arrow.arrow).j+1].type == 6) {
                        stopActInTime3(arrow, (offset) / 600.0,3);
                    }
                }
            }
        }
    }
    for (auto box : boxes) {
        if (*box.state == 1) {
            if (g.squares[getpos(box.box).i][getpos(box.box).j].type == 4) {
                CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("campfire2.png");
                s[getpos(box.box).i][getpos(box.box).j]->setGlobalZOrder(0);
                s[getpos(box.box).i][getpos(box.box).j]->setTexture(texture);
                g.squares[getpos(box.box).i][getpos(box.box).j].type = 5;
            }
            if (*box.dir == 0) {
                int offset = gety(geti(box.box->getPositionY())) - box.box->getPositionY();
                if (offset>=0) {
                    int f = canBoxGo(getpos(box.box).i + 1, getpos(box.box).j, *box.dir);
                    if (f == 0) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(),getpos(box.box).i, getpos(box.box).j);
                    }
                    else if (f == 2) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(), getpos(box.box).i+1, getpos(box.box).j);
                    }
                }
            }
            else if (*box.dir == 1) {
                int offset = -gety(geti(box.box->getPositionY())) + box.box->getPositionY();
                if (offset >= 0) {
                    int f = canBoxGo(getpos(box.box).i - 1, getpos(box.box).j,*box.dir);
                    if (f == 0) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(), getpos(box.box).i, getpos(box.box).j);
                    }
                    else if (f == 2) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(), getpos(box.box).i-1, getpos(box.box).j);
                    }
                }
            }
            else if (*box.dir == 2) {
                int offset = -getx(getj(box.box->getPositionX())) + box.box->getPositionX();
                if (offset >= 0) {
                    int f = canBoxGo(getpos(box.box).i, getpos(box.box).j - 1, * box.dir);
                    if (f == 0) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(), getpos(box.box).i, getpos(box.box).j);
                    }
                    else if (f == 2) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(), getpos(box.box).i, getpos(box.box).j-1);
                    }
                }
            }
            else if (*box.dir == 3) {
                int offset = getx(getj(box.box->getPositionX())) - box.box->getPositionX();
                if (offset >= 0) {
                    int f = canBoxGo(getpos(box.box).i, getpos(box.box).j + 1, *box.dir);
                    if (f == 0) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(), getpos(box.box).i, getpos(box.box).j);
                    }
                    else if (f == 2) {
                        goTo(box, box.box->getPositionX(), box.box->getPositionY(), getpos(box.box).i, getpos(box.box).j + 1);
                    }
                }
            }
        }
    }
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////keyboard action:


void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //判断 keyCode 枚举来区分所按下的按键
    auto moveUp = MoveBy::create(0.1, Point(0, 40));
    auto moveUpbox = MoveBy::create(0.1, Point(0, 40));

    auto moveDown = MoveBy::create(0.1, Point(0, -40));
    auto moveDownbox = MoveBy::create(0.1, Point(0, -40));

    auto moveLeft = MoveBy::create(0.1, Point(-40, 0));
    auto moveLeftbox = MoveBy::create(0.1, Point(-40, 0));

    auto moveRight = MoveBy::create(0.1, Point(40, 0));
    auto moveRightbox = MoveBy::create(0.1, Point(40, 0));

    /////////////////////start switch//////////////////////
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_UP_ARROW: {
        if (canop == 0)break;
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pback.png");
        person->setTexture(texture);
        direction = 0;
        if (isWater(posi+1,posj)) {
            auto seq = dropwaterSeq(0);
            person->runAction(seq);
        }
        else if (canPersonGo(posi + 1, posj) == 1 && checkdoor1(posi + 1, posj) == 1){
            if (hasBox(posi + 1,posj) == 1){
                if (canBoxGo(posi + 2, posj,0) && checkdoor1(posi + 2, posj) == 1) {
                    for (auto box : boxes) {
                        if (getpos(box.box) == point(posi + 1, posj) && *box.state != 3) {
                            auto act = MoveBy::create(0.1, Point(0, 40));
                            person->runAction(moveUp);
                            box.box->runAction(act);
                            checkleave(posi, posj);
                            personleave(posi, posj);
                            checkonto(posi + 2, posj);
                            persononto(posi + 1, posi);
                            boxonto(box, posi+2, posj);
                            posi += 1;
                            addpath(posi, posj);
                            break;
                        }
                    }
                }
                break;
            }
            int f = 0;
            for (auto bomb : bombs) {
                if (getpos(bomb.bomb) == point(posi + 1, posj) &&*bomb.state != 3 && *bomb.state != 5) {
                    f = 1;
                    if (canBoxGo(posi + 2, posj,0) && checkdoor1(posi + 2, posj) == 1) {
                        auto act = MoveBy::create(0.1, Point(0, 40));
                        person->runAction(moveUp);
                        bomb.bomb->runAction(act);
                        checkleave(posi, posj);
                        personleave(posi, posj);
                        checkonto(posi + 2, posj);
                        persononto(posi + 1, posj);
                        bombonto(bomb, posi + 2, posj);
                        posi += 1;
                        addpath(posi, posj);
                    }
                    else {
                        break;
                    }
                }
            }
            if (f == 1)break;
            checkleave(posi, posj);
            personleave(posi, posj);
            if (isWater(posi + 1, posj)) {
                auto seq = dropwaterSeq(0);
                person->runAction(seq);
                break;
            }
            checkonto(posi + 1, posj);
            persononto(posi + 1, posj);
            person->runAction(moveUp);
            posi += 1;
            addpath(posi, posj);
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_DOWN_ARROW: {
        if (canop == 0)break;
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pfront.png");
        person->setTexture(texture);
        direction = 1;
        if (isWater(posi - 1, posj)) {
            auto seq = dropwaterSeq(1);
            person->runAction(seq);
        }
        else if (canPersonGo(posi - 1, posj) == 1 && checkdoor1(posi, posj) == 1){
            if (hasBox(posi - 1, posj) == 1) {
                if (canBoxGo(posi - 2, posj,1) && checkdoor1(posi - 1, posj) == 1) {
                    for (auto box : boxes) {
                        if (getpos(box.box) == point(posi - 1, posj)&&*box.state!=3) {
                            auto act = MoveBy::create(0.1, Point(0, -40));
                            person->runAction(moveDown);
                            box.box->runAction(act);
                            checkleave(posi, posj);
                            personleave(posi, posj);
                            checkonto(posi - 2, posj);
                            boxonto(box, posi-2, posj);
                            persononto(posi - 1, posj);
                            posi -= 1;
                            addpath(posi, posj);
                            break;
                        }
                    }
                }
                break;
            }
            int f = 0;
            for (auto bomb : bombs) {
                if (getpos(bomb.bomb) == point(posi - 1, posj) && *bomb.state != 3 && *bomb.state != 5) {
                    f = 1;
                    if (canBoxGo(posi - 2, posj,1) && checkdoor1(posi - 1, posj) == 1) {
                        auto act = MoveBy::create(0.1, Point(0, -40));
                        person->runAction(moveDown);
                        bomb.bomb->runAction(act);
                        checkleave(posi, posj);
                        personleave(posi, posj);
                        checkonto(posi - 2, posj);
                        persononto(posi - 1, posj);
                        bombonto(bomb, posi - 2, posj);
                        posi -= 1;
                        addpath(posi, posj);
                    }
                    else {
                        break;
                    }
                }
            }
            if (f == 1)break;
            checkleave(posi, posj);
            personleave(posi, posj);
            if (isWater(posi-1, posj)) {
                auto seq = dropwaterSeq(1);
                person->runAction(seq);
                break;
            }
            checkonto(posi - 1, posj);
            persononto(posi - 1, posj);
            person->runAction(moveDown);
            posi -= 1;
            addpath(posi, posj);
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW: {
        if (canop == 0)break;
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pleft.png");
        person->setTexture(texture);
        direction = 2;
        if (isWater(posi, posj-1)) {
            auto seq = dropwaterSeq(2);
            person->runAction(seq);
        }
        else if (canPersonGo(posi, posj-1) == 1 && checkdoor2(posi, posj) == 1){
            if (hasBox(posi, posj-1) == 1) {
                if (canBoxGo(posi, posj-2,2) && checkdoor2(posi, posj-1) == 1) {
                    for (auto box : boxes) {
                        if (getpos(box.box) == point(posi, posj-1) && *box.state != 3) {
                            auto act = MoveBy::create(0.1, Point(-40,0));
                            person->runAction(moveLeft);
                            box.box->runAction(act);
                            checkleave(posi, posj);
                            personleave(posi, posj);
                            checkonto(posi, posj-2);
                            persononto(posi, posj - 1);
                            boxonto(box, posi, posj-2);
                            posj -= 1;
                            addpath(posi, posj);
                            break;
                        }
                    }
                }
                break;
            }
            int f = 0;
            for (auto bomb : bombs) {
                if (getpos(bomb.bomb) == point(posi, posj - 1) && *bomb.state != 3 && *bomb.state != 5) {
                    f = 1;
                    if (canBoxGo(posi, posj - 2,2) && checkdoor1(posi, posj - 1) == 1) {
                        auto act = MoveBy::create(0.1, Point(-40, 0));
                        person->runAction(moveLeft);
                        bomb.bomb->runAction(act);
                        checkleave(posi, posj);
                        personleave(posi, posj);
                        checkonto(posi, posj - 2);
                        persononto(posi, posj - 1);
                        bombonto(bomb,posi, posj - 2);
                        posj -= 1;
                        addpath(posi, posj);
                    }
                    else {
                        break;
                    }
                }
            }
            if (f == 1)break;
            checkleave(posi, posj);
            personleave(posi, posj);
            if (isWater(posi, posj-1)) {
                auto seq = dropwaterSeq(2);
                person->runAction(seq);
                break;
            }
            checkonto(posi, posj - 1);
            persononto(posi, posj - 1);
            person->runAction(moveLeft);
            posj -= 1;
            addpath(posi, posj);
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: {
        if (canop == 0)break;
        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("pright.png");
        person->setTexture(texture);
        direction = 3;
        if (isWater(posi, posj+1)) {
            auto seq = dropwaterSeq(3);
            person->runAction(seq);
        }
        else if (canPersonGo(posi, posj + 1) == 1 && checkdoor2(posi, posj + 1) == 1)
        {
            if (hasBox(posi, posj+1) == 1) {
                if (canBoxGo(posi, posj + 2,3) && checkdoor2(posi, posj + 2) == 1) {
                    for (auto box : boxes) {
                        if (getpos(box.box) == point(posi, posj + 1) && *box.state != 3) {
                            auto act = MoveBy::create(0.1, Point(40, 0));
                            person->runAction(moveRight);
                            box.box->runAction(act);
                            checkleave(posi, posj);
                            personleave(posi, posj);
                            checkonto(posi, posj + 2);
                            persononto(posi, posj + 1);
                            boxonto(box, posi, posj + 2);
                            posj += 1;
                            addpath(posi, posj);
                            break;
                        }
                    }
                }
                break;
            }
            int f = 0;
            for (auto bomb : bombs) {
                if (getpos(bomb.bomb) == point(posi, posj + 1) && *bomb.state != 3 && *bomb.state != 5) {
                    f = 1;
                    if (canBoxGo(posi, posj + 2,3) && checkdoor1(posi, posj + 1) == 1) {
                        auto act = MoveBy::create(0.1, Point(40, 0));
                        person->runAction(moveRight);
                        bomb.bomb->runAction(act);
                        checkleave(posi, posj);
                        personleave(posi, posj);
                        checkonto(posi, posj + 2);
                        persononto(posi, posj + 1);
                        bombonto(bomb, posi, posj + 2);
                        posj += 1;
                        addpath(posi, posj);
                    }
                    else {
                        break;
                    }
                }
            }
            if (f == 1)break;
            checkleave(posi, posj);
            personleave(posi, posj);
            if (isWater(posi, posj + 1)) {
                auto seq = dropwaterSeq(3);
                person->runAction(seq);
                break;
            }
            checkonto(posi, posj + 1);
            persononto(posi, posj + 1);
            person->runAction(moveRight);
            posj += 1;
            addpath(posi, posj);
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_SPACE: {
        if (canop == 0)break;
        if (g.bombnum <= 0)break;
        if (direction == 0 && canBoxGo(posi+1,posj,0) || direction == 1 && canBoxGo(posi - 1, posj,1) || direction == 2 && canBoxGo(posi, posj-1,2) || direction == 3 && canBoxGo(posi, posj+1,3))
        {
            Mybomb bomb;
            bomb.bomb = Sprite::create("bomb.png");
            bombs.push_back(bomb);
            bomb.bomb->setGlobalZOrder(20);
            if (direction == 0) {
                bomb.bomb->setPosition(Vec2(origin.x + getx(posj), origin.y + gety(posi) + 40));
                checkonto(posi + 1, posj);
                bombonto(bomb, posi + 1, posj);
            }
            else if (direction == 1) {
                bomb.bomb->setPosition(Vec2(origin.x + getx(posj), origin.y + gety(posi) - 40));
                checkonto(posi - 1, posj);
                bombonto(bomb, posi - 1, posj);
            }
            else if (direction == 2) {
                bomb.bomb->setPosition(Vec2(origin.x + getx(posj) - 40, origin.y + gety(posi)));
                checkonto(posi, posj-1);
                bombonto(bomb, posi, posj-1);
            }
            else if (direction == 3) {
                bomb.bomb->setPosition(Vec2(origin.x + getx(posj) + 40, origin.y + gety(posi)));
                checkonto(posi, posj + 1);
                bombonto(bomb, posi, posj+1);
            }
            this->addChild(bomb.bomb);
            auto ani1 = explodeAnimation1();
            auto ani2 = explodeAnimation2();
            int i = geti(bomb.bomb->getPositionY());
            int j = getj(bomb.bomb->getPositionX());
            
            auto explodecall1 = CallFunc::create([=] {
                *bomb.state = 1;
                });
            auto explodecall2 = CallFunc::create([=] {
                bombexplode1(getpos(bomb.bomb).i, getpos(bomb.bomb).j);
                checkleave(getpos(bomb.bomb).i, getpos(bomb.bomb).j);
                });
            auto explodecall3 = CallFunc::create([=] {
                this->removeChild(bomb.bomb, true);
                for (auto i = bombs.begin(); i != bombs.end(); i++) {
                    if (i->bomb==bomb.bomb) {
                        bombs.erase(i);
                        break;
                    }
                }
                bombexplode(i,j);
                //////////////////
                });

            auto act1 = Animate::create(ani1);
            auto act2 = Animate::create(ani2);
            auto seq = Sequence::create(cocos2d::DelayTime::create(2),explodecall1,
                act1, explodecall2,act2,cocos2d::DelayTime::create(0.3), explodecall3, NULL);
            if (*bomb.state != 3) {
                bomb.bomb->runAction(seq);
                seq->setTag(1);
            }
            g.bombnum--;
            renewStorage(3);
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_ENTER:
    case EventKeyboard::KeyCode::KEY_BACKSPACE: {
        if (canop == 0)break;
        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
            if (g.firearrownum <= 0)break;
            else {
                g.firearrownum--;
                renewStorage(2);
            }
        }
        else {
            if (g.arrownum <= 0)break;
            else {
                g.arrownum--;
                renewStorage(1);
            }
        }
        Myarrow arrow;
        *arrow.dir = direction;
        if (keyCode == EventKeyboard::KeyCode::KEY_ENTER)arrow.fire = 1;
        else arrow.fire = 0;
        if (arrow.fire == 1)arrow.arrow = Sprite::create("firearrow.png");
        else arrow.arrow = Sprite::create("arrow.png");
        arrows.push_back(arrow);
        arrow.arrow->setGlobalZOrder(19);
        arrow.arrow->setPosition(Vec2(origin.x + getx(posj), origin.y + gety(posi)));
        if (direction == 1)arrow.arrow->setRotation(90);
        else if (direction == 2)arrow.arrow->setRotation(180);
        else if (direction == 0)arrow.arrow->setRotation(270);
        this->addChild(arrow.arrow);
        if (direction == 0) {
            auto flycall = CallFunc::create([=] {
                this->removeChild(arrow.arrow, true);
                for (auto i = arrows.begin(); i != arrows.end(); i++) {
                    if (i->arrow == arrow.arrow) {
                        arrows.erase(i);
                        break;
                    }
                }
                });
            auto fly = MoveBy::create(((19 - posi) * 40 - 40) / 600.0, Point(0, (19 - posi) * 40 - 40));
            auto seq = Sequence::create(fly, cocos2d::DelayTime::create(0.5), flycall, NULL);
            arrow.arrow->runAction(seq);
            seq->setTag(1);
        }
        else if (direction == 1) {
            auto flycall = CallFunc::create([=] {
                this->removeChild(arrow.arrow, true);
                for (auto i = arrows.begin(); i != arrows.end(); i++) {
                    if (i->arrow == arrow.arrow) {
                        arrows.erase(i);
                        break;
                    }
                }
                });
            auto fly = MoveBy::create(-((0 - posi) * 40 + 40) / 600.0, Point(0, (0 - posi) * 40 + 40));
            auto seq = Sequence::create(fly, cocos2d::DelayTime::create(0.5), flycall, NULL);
            arrow.arrow->runAction(seq);
            seq->setTag(1);
        }
        else if (direction == 2) {
            auto flycall = CallFunc::create([=] {
                this->removeChild(arrow.arrow, true);
                for (auto i = arrows.begin(); i != arrows.end(); i++) {
                    if (i->arrow == arrow.arrow) {
                        arrows.erase(i);
                        break;
                    }
                }
                });
            auto fly = MoveBy::create(-((0 - posj) * 40 + 40) / 600.0, Point((0 - posj) * 40 + 40, 0));
            auto seq = Sequence::create(fly, cocos2d::DelayTime::create(0.5), flycall, NULL);
            arrow.arrow->runAction(seq);
            seq->setTag(1);
        }
        else if (direction == 3) {
            auto flycall = CallFunc::create([=] {
                this->removeChild(arrow.arrow, true);
                for (auto i = arrows.begin(); i != arrows.end(); i++) {
                    if (i->arrow == arrow.arrow) {
                        arrows.erase(i);
                        break;
                    }
                }
                });
            auto fly = MoveBy::create(((42 - posj) * 40 - 40) / 600.0, Point((42 - posj) * 40 - 40, 0));
            auto seq = Sequence::create(fly, cocos2d::DelayTime::create(0.5), flycall, NULL);
            arrow.arrow->runAction(seq);
            seq->setTag(1);
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_ALT: {
        if (canop == 0)break;
        if (g.boxnum <= 0)break;
        if (direction == 0 && g.squares[posi + 1][posj].type != 1 || direction == 1 && g.squares[posi - 1][posj].type != 1 || direction == 2 && g.squares[posi][posj - 1].type != 1 || direction == 3 && g.squares[posi][posj + 1].type != 1)
        {
            if (direction == 0&& canBoxGo(posi + 1, posj, 0)) {
                Mybox box;
                box.box = Sprite::create("box.png");
                box.box->setGlobalZOrder(5);
                box.box->setPosition(Vec2(origin.x + getx(posj), origin.y + gety(posi) + 40));
                this->addChild(box.box);
                boxes.push_back(box);
                checkonto(posi+1,posj);
                boxonto(box,posi + 1, posj);
                g.boxnum--;
                renewStorage(0);
            }
            else if (direction == 1&&canBoxGo(posi - 1, posj, 0)) {
                Mybox box;
                box.box = Sprite::create("box.png");
                box.box->setGlobalZOrder(5);
                box.box->setPosition(Vec2(origin.x + getx(posj), origin.y + gety(posi) - 40));
                this->addChild(box.box);
                boxes.push_back(box);
                checkonto(posi - 1, posj);
                boxonto(box, posi - 1, posj);
                g.boxnum--;
                renewStorage(0);
            }
            else if (direction == 2 && canBoxGo(posi, posj-1, 0)) {
                Mybox box;
                box.box = Sprite::create("box.png");
                box.box->setGlobalZOrder(5);
                box.box->setPosition(Vec2(origin.x + getx(posj)-40, origin.y + gety(posi)));
                this->addChild(box.box);
                boxes.push_back(box);
                checkonto(posi, posj-1);
                boxonto(box, posi, posj - 1);
                g.boxnum--;
                renewStorage(0);
            }

            else if (direction == 3 && canBoxGo(posi, posj+1, 0)) {
                Mybox box;
                box.box = Sprite::create("box.png");
                box.box->setGlobalZOrder(5);
                box.box->setPosition(Vec2(origin.x + getx(posj) + 40, origin.y + gety(posi)));
                this->addChild(box.box);
                boxes.push_back(box);
                checkonto(posi, posj + 1);
                boxonto(box, posi, posj + 1);
                g.boxnum--;
                renewStorage(0);
            }
        }
        break;
    }
    }
}

void HelloWorld::clickEvent(cocos2d::CCObject* a, cocos2d::extension::Control::EventType event) {
    if (a == b_pause) {
        if (canop == 0)return;
        canop = 0;
        Scale9Sprite* bac;
        Label* word;

        note2 = Sprite::create("wordarea2.png");
        note2->setPosition(Vec2(900, 450));
        note2->setGlobalZOrder(30);
        note2->setOpacity(140);
        this->addChild(note2);

        bac = Scale9Sprite::create("b_select.png");
        bac->setGlobalZOrder(30);
        word = Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 36);
        word->setColor(Color3B(0,0,0));
        word->setGlobalZOrder(30);
        b_quit = ControlButton::create(word, bac);
        b_quit->setPosition(900,250);
        b_quit->setGlobalZOrder(30);
        this->addChild(b_quit);
        b_quit->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::clickEvent), Control::EventType::TOUCH_DOWN);

        bac = Scale9Sprite::create("b_select.png");
        bac->setGlobalZOrder(30);
        word = Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 36);
        word->setColor(Color3B(0, 0, 0));
        word->setGlobalZOrder(30);
        b_restart = ControlButton::create(word, bac);
        b_restart->setPosition(900,450);
        this->addChild(b_restart);
        b_restart->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::clickEvent), Control::EventType::TOUCH_DOWN);

        bac = Scale9Sprite::create("b_select.png");
        bac->setGlobalZOrder(30);
        word = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 36);
        word->setColor(Color3B(0, 0, 0));
        word->setGlobalZOrder(30);
        b_resume = ControlButton::create(word, bac);
        b_resume->setPosition(900,650);
        b_resume->setGlobalZOrder(30);
        this->addChild(b_resume);
        b_resume->addTargetWithActionForControlEvents(this, cccontrol_selector(HelloWorld::clickEvent), Control::EventType::TOUCH_DOWN);
    }
    else if (a==b_quit) {
        auto scene = Mymenu::createScene();
        auto transition = TransitionZoomFlipX::create(1, scene);
        Director::getInstance()->replaceScene(transition);
    }
    else if (a == b_restart) {
        canop = 1;
        auto scene = HelloWorld::createScene();
        auto transition = TransitionZoomFlipX::create(1, scene);
        Director::getInstance()->replaceScene(transition);
    }
    else if (a == b_resume) {
        canop = 1;
        this->removeChild(b_quit);
        this->removeChild(b_restart);
        this->removeChild(b_resume);
        this->removeChild(note2);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



