#include "CCISOTileLayer.h"

NS_CC_BEGIN

CCISOTileLayer::CCISOTileLayer()
{
	
}

CCISOTileLayer::~CCISOTileLayer()
{
	CC_SAFE_RELEASE();
}

bool CCISOTileLayer::init()
{

	return true;
}

void CCISOTileLayer::visitShowTile()
{
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
	//移动的格子数.为了确保显示的完全，每个角相应移动一个格子。左右就加2，同样上下也要加2
	int columnCount=floor(screenSize.width/TileWidth)+2;
	int rowCount=(fllor(screenSize.hight/TileHeight)+2)*2;
	//屏幕的四个点。目前按原点在左上角，需要转成gl坐标系。
	CCPoint screeOriginal=isoViewToGame2F(0,0);
	//由于是按对角移动，只需要x移轴
	screenOriginal.x-=1;
	int oggColumnCount=columnCount+1;
	int startX=(int)screenOriginal.x,startY=(int)screenOriginal.y;
	int mx=0,my=0;
	for(int j=0;j<rowCount;j++){
		//if(j>0){
		//	if(j&1){
		//		columnCount++;
		//		startY++;
		//	}else{
		//		columnCount--;
		//		startX++;
		//	}
		//}
		for(int i=0;i<columnCount;i++){
			mx=startX+i;
			my=startY-i;
			//有了map坐标就可以显示内容。
		}
		//if((j+1)&1){
		//	columnCount++;
		//	startY++;
		//}else{
		//	columnCount--;
		//	startX++;
		//}
		//这里可以使j+1，再调换true和false的body,就是正常逻辑
		if(j&1){
			//下个循环为偶
			columnCount--;
			startX++;
		}else{
			//下个循环为奇
			columnCount++;
			startY++;
		}
	}
}

//ios game book 上的方法
void CCISOTileLayer::visitShowTile2()
{
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
	//屏幕的四个点。目前按原点在左上角，需要转成gl坐标系。
	CCPoint screenLeftTop=isoViewToGame2F(0,0);
	CCPoint screenRightTop=isoViewToGame2F(screenSize.width,0);
	CCPoint screenLeftBottom=isoViewToGame2F(0,screenSize.height);
	CCPoint screenRightBottom=isoViewToGame2F(screenSize.width,screenSize.height);

	screenLeftTop.x-=1
	screenRightBottom.x+=1;
	screenRightTop.y-=1;
	screenLeftBottom.y+=1;

	
	CCPoint rowStart=screenLeftTop;
	CCPoint rowEnd=screenRightTop;

	//由于是按对角移动，只需要x移轴
	
	int mx=0,my=0;
	float x=rowStart.x,y=rowStart.y;
	int rowCount=0;
	//在左下角之上
	while(rowStart.x<screenLeftBottom.x||rowStart.y<screenLeftBottom.y){
		while(x!=rowEnd.x && y!=rowEnd.y){
			mx=x;
			my=y;
		}
		if(++rowCount&1){
			rowStart.y+=1;
			rowEnd.x+=1;
		}else{
			rowStart.x+=1;
			rowEnd.y+=1;
		}
	}
}

void CCISOTileLayer::setLayerSize(CCSize tLayerSize)
{
    m_tLayerSize = tLayerSize;
}

CCSize CCISOTileLayer::getLayerSize()
{
    return m_tLayerSize;
}

void CCISOTileLayer::setContentSize(CCSize tContentSize)
{
    m_tContentSize = tContentSize;
}

CCSize CCISOTileLayer::getContentSize()
{
    return m_tContentSize;
}

void CCISOTileLayer::setName(const char* pName)
{
    CC_SAFE_RETAIN(pName);
    CC_SAFE_RELEASE(m_pName);
    m_pName = pName;
}

const char* CCISOTileLayer::getName()
{
    return m_pName;
}


NS_CC_END
