/*
 *  CISOCoordinate.h
 *  
 *  使用基于2的幂次方的数值，乘除直接使用位移操作
 *  每个游戏的tile大小都是固定的，直接定义好，可以提高效率
 *  Created by trarck trarck on 11-11-8.
 *  Copyright 2011 yitengku.com. All rights reserved.
 *
 */

#ifndef ISO_CCISOCoordinate_H_
#define ISO_CCISOCoordinate_H_

#include "cocos2d.h"

//tile width 
#ifndef TileWidth
#define TileWidth 64 
#endif
//tile height
#ifndef TileHeight
#define TileHeight 32 
#endif

#ifndef XUnit
#define XUnit TileWidth/2 
#endif

#ifndef YUnit
#define YUnit TileHeight/2 
#endif

#ifndef ZUnit
#define ZUnit TileHeight 
#endif
//tileWidth=64,tileHeight=32

typedef struct T_CCPointF{
	float x;
    float y;
} ISOPointF;

typedef struct T_CCPointI{
	int x;
    int y;
} ISOPointI;

USING_NS_CC;

static inline CCPoint isoViewToGame2F(float x,float y)
{
	CCPoint p;
	x=x/TileWidth;//x=x/64
	y=y/TileHeight;//y=y/32
	p.x=x+y;
	p.y=y-x;
	return p;
}

static inline CCPoint isoViewToGamePoint(const CCPoint& point)
{
	return isoViewToGame2F(point.x,point.y);
}

static inline CCPoint isoViewToGameGrid2F (float x,float  y)
{
	CCPoint p=isoViewToGame2F(x,y);
	p.x=floor(p.x);
	p.y=floor(p.y);
	return p;
}

static inline CCPoint isoViewToGameGridPoint (const CCPoint& point)
{
	return isoViewToGameGrid2F(point.x,point.y);
}

static inline CCPoint isoViewToGameCell2F (float x,float  y)
{
	CCPoint p=isoViewToGame2F(x,y);
	p.x=(int)p.x;
	p.y=(int)p.y;
	return p;
}


static inline CCPoint isoGameToView3F(float x ,float y ,float z)
{
	double sx=x-y,sy=x+y;
	CCPoint p;
	p.x=sx*XUnit;//sx*32
	p.y=sy*YUnit-z*ZUnit;//sy*16-z*32
	return p;
}

static inline CCPoint isoGameToView2F(float x, float y)
{
	double sx=x-y,sy=x+y;
	CCPoint p;
	p.x=sx*XUnit;//sx*32
	p.y=sy*YUnit;//sy*16
	return p;
}

static inline CCPoint isoGameToViewPoint(const CCPoint&  point)
{
	return isoGameToView2F(point.x,point.y);
}

//返回CCPoint的指针

static inline CCPoint* isoViewToGame2FP(float x,float y)
{
	CCPoint* p=new CCPoint();
	x=x/TileWidth;//x=x/64
	y=y/TileHeight;//y=y/32
	p->x=x+y;
	p->y=y-x;
	p->autorelease();
	return p;
}

static inline CCPoint* isoViewToGamePointP(const CCPoint& point)
{
	return isoViewToGame2FP(point.x,point.y);
}

static inline CCPoint* isoViewToGameGrid2FP(float x,float  y)
{
	CCPoint* p=isoViewToGame2FP(x,y);
	p->x=floor(p->x);
	p->y=floor(p->y);
	return p;
}

static inline CCPoint* isoViewToGameGridPointP (const CCPoint& point)
{
	return isoViewToGameGrid2FP(point.x,point.y);
}

static inline CCPoint* isoViewToGameCell2FP(float x,float  y)
{
	CCPoint* p=isoViewToGame2FP(x,y);
	p->x=(int)p->x;
	p->y=(int)p->y;
	return p;
}


static inline CCPoint* isoGameToView3FP(float x ,float y ,float z)
{
	double sx=x-y,sy=x+y;
	CCPoint* p=new CCPoint();
	p->x=sx*XUnit;//sx*32
	p->y=sy*YUnit-z*ZUnit;//sy*16-z*32
	p->autorelease();
	return p;
}

static inline CCPoint* isoGameToView2FP(float x, float y)
{
	double sx=x-y,sy=x+y;
	CCPoint* p=new CCPoint();
	p->x=sx*XUnit;//sx*32
	p->y=sy*YUnit;//sy*16
	p->autorelease();
	return p;
}

static inline CCPoint* isoGameToViewPointP(const CCPoint&  point)
{
	return isoGameToView2FP(point.x,point.y);
}

#endif //ISO_CCISOCoordinate_H_