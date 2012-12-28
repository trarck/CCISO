//
//  Coordinate.m
//  Dungeons
//
//  Created by trarck trarck on 11-10-14.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "CCCoordinate.h"

NS_CC_BEGIN

static CCCoordinate* l_coordinate=NULL;

CCCoordinate::CCCoordinate()
:m_xUnit(0)
,m_yUnit(0)
,m_zUnit(0)
,m_tileWidth(0)
,m_tileHeight(0)
{
    
}

CCCoordinate::~CCCoordinate()
{
    
}


CCCoordinate* CCCoordinate::sharedCoordinate()
{
	if(!l_coordinate){
		l_coordinate=new CCCoordinate();
        l_coordinate->init();
	}
	return l_coordinate;	
}

bool CCCoordinate::init()
{
    return true;
}

bool CCCoordinate::init(int width,int height)
{

    setTileSize(width ,height);
	
	return true;
}

bool CCCoordinate::init(int xUnit,int yUnit,int zUnit)
{
	setCoordinateUnit(xUnit ,yUnit ,zUnit);
	
	return true;
}


void CCCoordinate::setTileSize(int width ,int height)
{
	m_tileWidth=width;
	m_tileHeight=height;
	
	m_xUnit=width/2;
	m_yUnit=height/2;
	m_zUnit=height;
}

void CCCoordinate::setCoordinateUnit(int xUnit ,int yUnit ,int zUnit)
{
	m_xUnit=xUnit;
	m_yUnit=yUnit;
	m_zUnit=zUnit;
	
	m_tileWidth=xUnit*2;
	m_tileHeight=yUnit*2;
}

void CCCoordinate::setCoordinateUnit(int xUnit ,int yUnit)
{
	setCoordinateUnit(xUnit ,yUnit ,yUnit*2);
}


CCPoint CCCoordinate::screenToMap(float x ,float y)
{
	x=x/m_tileWidth;
	y=y/m_tileHeight;
    return CCPointMake(x+y,y-x);
//	CCPoint p;
//	p.x=x+y;
//	p.y=y-x;
//	return p;
}

CCPoint CCCoordinate::screenToMap(CCPoint point)
{
	return screenToMap(point.x,point.y);
}

CCPoint CCCoordinate::screenToMapGrid(float x ,float y)
{
	CCPoint p=screenToMap(x,y);
	p.x=floor(p.x);
	p.y=floor(p.y);
	return p;
}

CCPoint CCCoordinate::screenToMapGrid(CCPoint point)
{
	return screenToMapGrid(point.x ,point.y);
}

CCCell CCCoordinate::screenToMapCell(float x ,float y)
{
	CCPoint p=screenToMap(x ,y);
	CCCell cell;
	cell.x=(int) p.x;
	cell.y=(int) p.y;
	return cell;
}

CCPoint CCCoordinate::mapToScreen(float x ,float y ,float z)
{
	double sx=x-y,sy=x+y;
	CCPoint p;
	p.x=sx*m_xUnit;
	p.y=sy*m_yUnit-z*m_zUnit;
	return p;
}

CCPoint CCCoordinate::mapToScreen(float x ,float y)
{
	return mapToScreen(x ,y ,0);
}

CCPoint CCCoordinate::mapToScreen(CCPoint point)
{
	return mapToScreen(point.x ,point.y ,0);
}

CCSize CCCoordinate::mapToscreenSize(int l ,int b ,int h)
{
	int s;
	float width,height;
	CCSize size;
	
	s=l+b;
	width=s*m_xUnit;
	height=s*m_yUnit+h*m_zUnit;
	size.width=width;
	size.height=height;
	return size;
}

CCPoint CCCoordinate::mapToscreenAnchor(int l ,int b ,int h)
{
	CCPoint p;
	p.x=b*m_xUnit;
	p.y=h*m_zUnit;
	return p;
}

NS_CC_END
