#include "PlayScene.h"
#include"cocos2d.h"
#include "SimpleAudioEngine.h"
#include "tinyxml2/tinyxml2.h"

USING_NS_CC;



void PlayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (win == 0)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			move(UP);
		}
		break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			move(LEFT);
		}
		break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			move(DOWN);
		}
		break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			move(RIGHT);
		}
		break;
		}
		if (win == 1)
		{
			auto win = Sprite::create("victory.png");
			win->setScale(2.5);
			win->setPosition(Vec2(ox+400, oy+300));
			this->addChild(win, 4);
		}
	}
}

Scene* PlayScene::createScene()
{
	return PlayScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in PlayScene.cpp\n");
}

bool PlayScene::init()
{
	if (!Scene::init())
	{
		return false;
	}


	int cbox, cstar;
	cbox = cstar = 0;
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			switch (map[i][j])
			{
			case '1':
			{
				auto w = Sprite::create("wall_50_50.png");
				w->setPosition(ox + 50 * i, oy + 50 * j);
				this->addChild(w, 0);
				map[i][j] = WALL;
				break;
			}
			case'2':
			{

				auto box0 = Sprite::create("box_50_50.png");
				box0->setPosition(ox + 50 * i, oy + 50 * j);
				this->addChild(box0, 2);
				map[i][j] = BOX;
				pbox[cbox] = position(i, j, box0);
				cbox++;
				break;
			}
			case'3':
			{
				auto w = Sprite::create("redstar.png");
				w->setPosition(ox + 50 * i, oy + 50 * j);
				this->addChild(w, 0);
				map[i][j] = STAR;
				pgoal[cstar] = position(i, j);
				cstar++;
				break;
			}
			case'4':
			{
				auto me = Sprite::create("people.png");
				this->addChild(me, 4);
				me->setPosition(ox + 50 * i, oy + 50 * j);
				map[i][j] = ME;
				pme = position(i, j, me);
				break;
			}
			case' ':
				map[i][j] = SPACE;
				break;
			}
		}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PlayScene::again, this));

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

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto background = Sprite::create("background.png");
	if (background == nullptr)
		problemLoading("background.png");
	else
	{
		background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(background, -1);
	}





	//auto sprite = Sprite::create("HelloWorld.png");
	//if (sprite == nullptr)
	//{
	//	problemLoading("'HelloWorld.png'");
	//}
	//else
	//{
	//	// position the sprite on the center of the screen
	//	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//	// add the sprite as a child to this layer
	//	this->addChild(sprite, 0);
	//}
	//return true;



	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayScene::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);




}


void PlayScene::again(Ref* pSender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.4f, PlayScene::createScene()));
}

void PlayScene::esc(Ref* pSender)
{
	Director::getInstance()->end();
}
