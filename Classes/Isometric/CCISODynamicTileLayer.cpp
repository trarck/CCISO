#include "CCISODynamicTileLayer.h"
#include "CCISOCoordinate.h"

NS_CC_BEGIN



CCISODynamicTileLayer::CCISODynamicTileLayer()
:m_pDynamicComponent(NULL)
,m_iLastStartX(0)
,m_iLastStartY(0)
{

}

CCISODynamicTileLayer::~CCISODynamicTileLayer()
{
	CC_SAFE_RELEASE(m_pDynamicComponent);
}

bool CCISODynamicTileLayer::init()
{
    if(CCISOTileLayer::init()){
        m_tScreenSize=CCDirector::sharedDirector()->getWinSize();//CCSizeMake(480,320);
        
        m_pDynamicComponent=new CCISODynamicComponent();
        m_pDynamicComponent->setCreateDelegator(this);
        m_pDynamicComponent->setTileLayer(this);
        
        return true;
    }
    return false;
}

bool CCISODynamicTileLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(CCISOTileLayer::init(mapTileSize, offset)){
        init();
        setComponentColumnAndRow();
        m_pDynamicComponent->setupComponents(offset);
        
        return true;
    }
    return false;
}

void CCISODynamicTileLayer::setupTiles()
{
    setComponentColumnAndRow();
    m_pDynamicComponent->setupComponents(m_tOffset);
}

void CCISODynamicTileLayer::setComponentColumnAndRow()
{

    if(m_pDynamicComponent && m_tMapTileSize.height!=0 && m_tMapTileSize.width!=0){
        int componentTileColumn=floor(m_tScreenSize.width/m_tMapTileSize.width)+2;
        int componentTileRow=floor(m_tScreenSize.height/m_tMapTileSize.height)+2;
        
        m_pDynamicComponent->setComponentTileColumn(componentTileColumn);
        m_pDynamicComponent->setComponentTileRow(componentTileRow);
    }

}

void CCISODynamicTileLayer::draw()
{
	
	ccDrawColor4B(255,0,0,255);
    ccDrawRect(m_tOffset,ccp(m_tOffset.x+m_tScreenSize.width,m_tOffset.y+m_tScreenSize.height));
}



void CCISODynamicTileLayer::scroll(const CCPoint& tOffset)
{
    this->setOffset(tOffset);
	m_pDynamicComponent->scroll(tOffset);
}

void CCISODynamicTileLayer::setScreenSize(const CCSize& screenSize)
{
    m_tScreenSize=screenSize;
}


void CCISODynamicTileLayer::setDynamicComponent(CCISODynamicComponent* pDynamicComponent)
{
    CC_SAFE_RETAIN(pDynamicComponent);
    CC_SAFE_RELEASE(m_pDynamicComponent);
    m_pDynamicComponent = pDynamicComponent;
}

CCISODynamicComponent* CCISODynamicTileLayer::getDynamicComponent()
{
    return m_pDynamicComponent;
}

CCSprite* CCISODynamicTileLayer::createTile()
{
    CCSprite* cellTile=CCSprite::create("grid_ground.png");
    cellTile->setAnchorPoint(ccp(0.5,0));
    //    cellTile->setOpacity(60);
    this->addChild(cellTile);
    return cellTile;
}
NS_CC_END
