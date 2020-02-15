#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3
#define WALL 1
#define BOX 2
#define STAR 3
#define ME 4
#define SPACE 5
const int DIR[4][2] = { {0,1} ,{-1,0}, {0,-1}, {1,0} };





class position
{
private:
	int x, y;
	Sprite *p;
	int cwin;
public:
	position()
	{}
	position(int x, int y,Sprite *p)
	{
		this->x = x, this->y = y;
		this->p = p;
		cwin = 0;
	}
	position(int x, int y)
	{
		this->x = x, this->y = y;
		cwin = 0;
	}
	int operator==(position b)
	{
		if (this->x == b.x&&this->y == b.y)
			return 1;
		else
			return 0;
	}
	void move(int dir)
	{
		x += DIR[dir][0];
		y += DIR[dir][1];
		p->runAction(MoveBy::create(0.05f,Point(DIR[dir][0]*50,DIR[dir][1]*50)));
	}
	void wl(int i)
	{
		cwin = i;
	}
	void cgepng(CCTexture2D* texture)
	{
		p->setTexture(texture);
	}
	int rx() { return x; }
	int ry() { return y; }
	int rwin() { return cwin; }
};


class PlayScene : public cocos2d::Scene
{
private:
	const int ox=100, oy=100;
	char map[6][7] =
	{
	"111111",
	"1 32 1",
	"1  2 1",
	"1312 1",
	"1  431",
	"111111"
	};
	position pme;
	position pbox[3];
	position pgoal[3];
	int win =0;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void again(cocos2d::Ref* pSender);
	void esc(cocos2d::Ref* pSender);
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	position* fbox(int x, int y)
	{
		for (int i=0;i<3;i++)
		{
			if (pbox[i] == position(x, y))
				return &pbox[i];
		}
	}
	void move(int dir)
	{
		int x = pme.rx(),y=pme.ry();
		int x1 = x + DIR[dir][0], y1 = y + DIR[dir][1];
		if (map[x1][y1]==SPACE||map[x1][y1]==STAR)
		{
			map[x1][y1] = ME;
			map[x][y] = SPACE;
			for (int i = 0; i < 3; i++)
			{
				if (position(x, y) == pgoal[i])
				{
					map[x][y] = STAR;
				}
			}
			pme.move(dir);
		}
		if (map[x1][y1] == BOX)
		{
			int x2 = x + 2*DIR[dir][0], y2 = y + 2*DIR[dir][1];
			position *tbox = fbox(x1, y1);
			if (map[x2][y2] == SPACE)
			{
				if (tbox->rwin() == 1)
				{
					CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("box_50_50.png");
					tbox->cgepng(texture);
					tbox->wl(0);
				}
				map[x2][y2] = BOX, map[x1][y1] = ME, map[x][y] = SPACE;
				for (int i = 0; i < 3; i++)
				{
					if (position(x, y) == pgoal[i])
					{
						map[x][y] = STAR;
					}
				}
				tbox->move(dir);
				pme.move(dir);
			}
			if (map[x2][y2] == STAR)
			{
				CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("redbox_50_50.png");
				tbox->cgepng(texture);
				tbox->wl(1);
				map[x2][y2] = BOX, map[x1][y1] = ME, map[x][y] = SPACE;
				for (int i = 0; i < 3; i++)
				{
					if (position(x, y) == pgoal[i])
					{
						map[x][y] = STAR;
					}
				}
				tbox->move(dir);
				pme.move(dir);
				if (pbox[0].rwin() + pbox[1].rwin() + pbox[2].rwin() == 3)
					win = 1;
			}
			
		}
	
	
	
	}
	CREATE_FUNC(PlayScene);
};





#endif