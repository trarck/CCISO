#include "CCISOBatchDynamicTileLayer.h"
#include "CCISOCoordinate.h"
#include "CCISOBatchDynamicComponent.h"

NS_CC_BEGIN



CCISOBatchDynamicTileLayer::CCISOBatchDynamicTileLayer()
:m_pTileset(NULL)
{

}

CCISOBatchDynamicTileLayer::~CCISOBatchDynamicTileLayer()
{
	CC_SAFE_RELEASE(m_pTileset);
}

bool CCISOBatchDynamicTileLayer::init()
{
    if(CCISOTileLayer::init()){
        m_tScreenSize=CCDirector::sharedDirector()->getWinSize();//CCSizeMake(480,320);
        
        m_pDynamicComponent=new CCISOBatchDynamicComponent();
        m_pDynamicComponent->setTileLayer(this);
        
        return true;
    }
    return false;
}

bool CCISOBatchDynamicTileLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(CCISOTileLayer::init(mapTileSize, offset)){
        init();       
        return true;
    }
    return false;
}

NS_CC_END
