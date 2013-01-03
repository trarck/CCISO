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
	//�ƶ��ĸ�����.Ϊ��ȷ����ʾ����ȫ��ÿ������Ӧ�ƶ�һ�����ӡ����Ҿͼ�2��ͬ������ҲҪ��2
	int columnCount=floor(screenSize.width/TileWidth)+2;
	int rowCount=(fllor(screenSize.hight/TileHeight)+2)*2;
	//��Ļ���ĸ��㡣Ŀǰ��ԭ�������Ͻǣ���Ҫת��gl����ϵ��
	CCPoint screeOriginal=isoViewToGame2F(0,0);
	//�����ǰ��Խ��ƶ���ֻ��Ҫx����
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
			//����map����Ϳ�����ʾ���ݡ�
		}
		//if((j+1)&1){
		//	columnCount++;
		//	startY++;
		//}else{
		//	columnCount--;
		//	startX++;
		//}
		//�������ʹj+1���ٵ���true��false��body,���������߼�
		if(j&1){
			//�¸�ѭ��Ϊż
			columnCount--;
			startX++;
		}else{
			//�¸�ѭ��Ϊ��
			columnCount++;
			startY++;
		}
	}
}

//ios game book �ϵķ���
void CCISOTileLayer::visitShowTile2()
{
	CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
	//��Ļ���ĸ��㡣Ŀǰ��ԭ�������Ͻǣ���Ҫת��gl����ϵ��
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

	//�����ǰ��Խ��ƶ���ֻ��Ҫx����
	
	int mx=0,my=0;
	float x=rowStart.x,y=rowStart.y;
	int rowCount=0;
	//�����½�֮��
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
