#include "CCISOCoordinate.h"
#include "CCISOTileSimpleGroundLayer.h"

NS_CC_BEGIN


CCISOTileSimpleGroundLayer * CCISOTileSimpleGroundLayer::layerWithTilesetInfo(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    return CCISOTileSimpleGroundLayer::create(tilesetInfo, layerInfo, mapInfo);
}

CCISOTileSimpleGroundLayer * CCISOTileSimpleGroundLayer::create(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    CCISOTileSimpleGroundLayer *pRet = new CCISOTileSimpleGroundLayer();
    if (pRet->initWithTilesetInfo(tilesetInfo, layerInfo, mapInfo))
    {
        pRet->autorelease();
        return pRet;
    }
    return NULL;
}

CCISOTileSimpleGroundLayer::CCISOTileSimpleGroundLayer()
:m_iStartX(0)
,m_iStartY(0)
,m_tLayerSize(CCSizeZero)
,m_tMapTileSize(CCSizeZero)
,m_pTiles(NULL)
,m_pTileSet(NULL)
,m_pProperties(NULL)
,m_sLayerName("")
,m_pReusedTile(NULL)
,m_pSpriteBatchNode(NULL)
,m_pAtlasIndexArray(NULL)
{
	
}

CCISOTileSimpleGroundLayer::~CCISOTileSimpleGroundLayer()
{
    CC_SAFE_RELEASE(m_pTileSet);
    CC_SAFE_RELEASE(m_pReusedTile);
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pSpriteBatchNode);
//    if (m_pAtlasIndexArray)
//    {
//        ccCArrayFree(m_pAtlasIndexArray);
//        m_pAtlasIndexArray = NULL;
//    }
    
    CC_SAFE_DELETE_ARRAY(m_pTiles);
}

bool CCISOTileSimpleGroundLayer::init()
{
    m_tTileSize=CCSizeZero;
	m_tOffset=CCPointZero;
    
	return true;
}

bool CCISOTileSimpleGroundLayer::init(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    m_pSpriteBatchNode=new CCSpriteBatchNode();
    // XXX: is 35% a good estimate ?
    CCSize size = layerInfo->m_tLayerSize;
    float totalNumberOfTiles = size.width * size.height;
    float capacity = totalNumberOfTiles * 0.35f + 1; // 35 percent is occupied ?
    
    CCTexture2D *texture = NULL;
    if( tilesetInfo )
    {
        texture = CCTextureCache::sharedTextureCache()->addImage(tilesetInfo->m_sSourceImage.c_str());
    }
    
    if (m_pSpriteBatchNode->initWithTexture(texture, (unsigned int)capacity))
    {
        // layerInfo
        m_sLayerName = layerInfo->m_sName;
        m_tLayerSize = size;
        m_pTiles = layerInfo->m_pTiles;
        m_uMinGID = layerInfo->m_uMinGID;
        m_uMaxGID = layerInfo->m_uMaxGID;
        m_cOpacity = layerInfo->m_cOpacity;
        this->initOffset(layerInfo->m_tOffset);
        
        setProperties(CCDictionary::createWithDictionary(layerInfo->getProperties()));
        m_fContentScaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
        
        // tilesetInfo
        m_pTileSet = tilesetInfo;
        CC_SAFE_RETAIN(m_pTileSet);
        
        // mapInfo
        m_tMapTileSize = mapInfo->getTileSize();
        m_uLayerOrientation = mapInfo->getOrientation();
        
        
        m_pAtlasIndexArray = ccCArrayNew((unsigned int)totalNumberOfTiles);
        
        this->setContentSize(CCSizeMake(m_tLayerSize.width * m_tMapTileSize.width, m_tLayerSize.height * m_tMapTileSize.height));
        
        m_bUseAutomaticVertexZ = false;
        m_nVertexZvalue = 0;
        
        return true;
    }
    return false;
}

bool CCISOTileSimpleGroundLayer::initWithTilesetInfo(CCISOTilesetInfo *tilesetInfo, CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    return this->init(tilesetInfo,layerInfo,mapInfo);
}


void CCISOTileSimpleGroundLayer::initOffset(const CCPoint& tOffset)
{
//    this->setPosition(tOffset);
	this->setOffset(tOffset);
	CCPoint startMapCoord=isoViewToGamePoint(tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
}

void CCISOTileSimpleGroundLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}


void CCISOTileSimpleGroundLayer::releaseMap()
{
    if (m_pTiles)
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
    
    if (m_pAtlasIndexArray)
    {
        ccCArrayFree(m_pAtlasIndexArray);
        m_pAtlasIndexArray = NULL;
    }
}

void CCISOTileSimpleGroundLayer::setupTiles()
{
    // Optimization: quick hack that sets the image size on the tileset
    m_pTileSet->m_tImageSize = m_pSpriteBatchNode->getTextureAtlas()->getTexture()->getContentSizeInPixels();
    
    // By default all the tiles are aliased
    // pros:
    //  - easier to render
    // cons:
    //  - difficult to scale / rotate / etc.
    m_pSpriteBatchNode->getTextureAtlas()->getTexture()->setAliasTexParameters();
    
    //CFByteOrder o = CFByteOrderGetCurrent();
    
    // Parse cocos2d properties
    this->parseInternalProperties();
    
    for (unsigned int y=0; y < m_tLayerSize.height; y++)
    {
        for (unsigned int x=0; x < m_tLayerSize.width; x++)
        {
            unsigned int pos = (unsigned int)(x + m_tLayerSize.width * y);
            unsigned int gid = m_pTiles[ pos ];
            
            // gid are stored in little endian.
            // if host is big endian, then swap
            //if( o == CFByteOrderBigEndian )
            //    gid = CFSwapInt32( gid );
            /* We support little endian.*/
            
            // XXX: gid == 0 --> empty tile
            if (gid != 0)
            {
                this->appendTileForGID(gid, ccp(x, y));
                
                // Optimization: update min and max GID rendered by the layer
                m_uMinGID = MIN(gid, m_uMinGID);
                m_uMaxGID = MAX(gid, m_uMaxGID);
            }
        }
    }
    
    CCAssert( m_uMaxGID >= m_pTileSet->m_uFirstGid &&
             m_uMinGID >= m_pTileSet->m_uFirstGid, "TMX: Only 1 tileset per layer is supported");
}



void CCISOTileSimpleGroundLayer::setLayerSize(const CCSize& tLayerSize)
{
    m_tLayerSize = tLayerSize;
}

CCSize CCISOTileSimpleGroundLayer::getLayerSize()
{
    return m_tLayerSize;
}

//void CCISOTileSimpleGroundLayer::setContentSize(CCSize tContentSize)
//{
//    m_tContentSize = tContentSize;
//}
//
//CCSize CCISOTileSimpleGroundLayer::getContentSize()
//{
//    return m_tContentSize;
//}

void CCISOTileSimpleGroundLayer::setTileSize(const CCSize& tileSize)
{
    m_tTileSize=tileSize;
}

void CCISOTileSimpleGroundLayer::setTileSize(float width,float height)
{
    m_tTileSize.width=width;
    m_tTileSize.height=height;
}


void CCISOTileSimpleGroundLayer::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

void CCISOTileSimpleGroundLayer::setOffset(float x,float y)
{
    m_tOffset.x=x;
	m_tOffset.y=y;
}

CCPoint CCISOTileSimpleGroundLayer::getOffset()
{
    return m_tOffset;
}

void CCISOTileSimpleGroundLayer::setMapTileSize(const CCSize& tMapTileSize)
{
    m_tMapTileSize = tMapTileSize;
}

const CCSize& CCISOTileSimpleGroundLayer::getMapTileSize()
{
    return m_tMapTileSize;
}

void CCISOTileSimpleGroundLayer::setTiles(unsigned int* pTiles)
{
    CC_SAFE_RETAIN(pTiles);
    CC_SAFE_RELEASE(m_pTiles);
    m_pTiles = pTiles;
}

unsigned int* CCISOTileSimpleGroundLayer::getTiles()
{
    return m_pTiles;
}

void CCISOTileSimpleGroundLayer::setTileSet(CCISOTilesetInfo* pTileSet)
{
    CC_SAFE_RETAIN(pTileSet);
    CC_SAFE_RELEASE(m_pTileSet);
    m_pTileSet = pTileSet;
}

CCISOTilesetInfo* CCISOTileSimpleGroundLayer::getTileSet()
{
    return m_pTileSet;
}

void CCISOTileSimpleGroundLayer::setLayerOrientation(unsigned int uLayerOrientation)
{
    m_uLayerOrientation = uLayerOrientation;
}

unsigned int CCISOTileSimpleGroundLayer::getLayerOrientation()
{
    return m_uLayerOrientation;
}

void CCISOTileSimpleGroundLayer::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOTileSimpleGroundLayer::getProperties()
{
    return m_pProperties;
}

void CCISOTileSimpleGroundLayer::setTileSets(CCArray* pTileSets)
{
    CC_SAFE_RETAIN(pTileSets);
    CC_SAFE_RELEASE(m_pTileSets);
    m_pTileSets = pTileSets;
}

CCArray* CCISOTileSimpleGroundLayer::getTileSets()
{
    return m_pTileSets;
}

NS_CC_END
