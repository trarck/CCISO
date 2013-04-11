#include "CCISOTileMap.h"
#include "CCISOCoordinate.h"
#include "CCISOTileLayer.h"
#include "CCISOTileset.h"

NS_CC_BEGIN

CCISOTileLayer::CCISOTileLayer()
:m_iStartX(0)
,m_iStartY(0)
,m_tLayerSize(CCSizeZero)
,m_tMapTileSize(CCSizeZero)
,m_tOffset(CCPointZero)
,m_pProperties(NULL)
,m_sLayerName("")
,m_pTiles(NULL)
,m_bUseAutomaticVertexZ(false)
,m_nVertexZvalue(0)
{
	
}

CCISOTileLayer::~CCISOTileLayer()
{
    CC_SAFE_RELEASE(m_pProperties);
    if(m_pTiles )
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}

bool CCISOTileLayer::init()
{
    m_pProperties=new CCDictionary();
    
	return true;
}

bool CCISOTileLayer::init(CCSize& mapTileSize)
{
    if(init()){
        m_tMapTileSize=mapTileSize;
        return true;
    }
    return false;
}

bool CCISOTileLayer::init(CCSize& mapTileSize,CCPoint& offset)
{
    if(init(mapTileSize)){
        m_tOffset=offset;
        return true;
    }
    return false;
}


void CCISOTileLayer::initOffset(const CCPoint& tOffset)
{
//    this->setPosition(tOffset);
	this->setOffset(tOffset);
	CCPoint startMapCoord=isoViewToGamePoint(tOffset);
	m_iStartX=(int)startMapCoord.x;
	m_iStartY=(int)startMapCoord.y;
}

void CCISOTileLayer::initOffset(float x,float y)
{
	this->initOffset(ccp(x,y));
}

CCISOTileLayer* CCISOTileLayer::create()
{
    CCISOTileLayer* pRet=new CCISOTileLayer();
    if(pRet->init()){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = NULL;
        return NULL; 
    }
}

void CCISOTileLayer::releaseLayer()
{
    if (m_pTiles)
    {
        delete [] m_pTiles;
        m_pTiles = NULL;
    }
}

void CCISOTileLayer::setupTiles()
{
    CCAssert(false, "you must impl CCISOTileLayer::setupTiles");
}

void CCISOTileLayer::addTileAt(float x,float y)
{
    addTileAt(ccp(x,y));
}

void CCISOTileLayer::addTileAt(const CCPoint& pos)
{
    CCAssert(false, "you must impl CCISOTileLayer::addTileAt");
}

/**
 * 获取tile
 */
CCISOTile* CCISOTileLayer::tileAt(float x,float y)
{
    return tileAt(ccp(x,y));
}


CCISOTile* CCISOTileLayer::tileAt(const CCPoint& pos)
{
    CCISOTile* tile=NULL;
    unsigned int gid=tileGIDAt(pos);
    
    if(gid>0){
        CCISOTileset* tileset=m_pMap->getTilesetGroup()->getTilesetByGid(gid);
        tile=tileset->tileForGid(gid);
    }
    
    return tile;
}

void CCISOTileLayer::removeTileAt(float x,float y)
{
    removeTileAt(ccp(x,y));
}

void CCISOTileLayer::removeTileAt(const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "CCISOTileLayer::removeTileAt: invalid position");
    
    int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
    m_pTiles[idx]=0;
}

unsigned int CCISOTileLayer::tileGIDAt(float x,float y)
{
    return tileGIDAt(ccp(x,y));
}

unsigned int CCISOTileLayer::tileGIDAt(const CCPoint& pos)
{
    if(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0){
        int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
        unsigned int gid = m_pTiles[idx];
        
        return gid;
    }
    return 0;
}


//TODO 
void CCISOTileLayer::setTileGID(unsigned int gid, const CCPoint& pos)
{
    CCAssert(pos.x < m_tLayerSize.width && pos.y < m_tLayerSize.height && pos.x >=0 && pos.y >=0, "CCISOTileLayer::setTileGID: invalid position");
    int idx = (int)(pos.x + pos.y * m_tLayerSize.width);
    m_pTiles[idx]=gid;
}

void CCISOTileLayer::setTileGID(unsigned int gid, float x,float y)
{
    setTileGID(gid,ccp(x,y));
}


//===============tile sprite===============

/**
 * 获取tile
 */
CCSprite* CCISOTileLayer::tileSpriteAt(float x,float y)
{
    return tileSpriteAt(ccp(x,y));
}

CCSprite* CCISOTileLayer::tileSpriteAt(const CCPoint& pos)
{
    CCSprite* sprite=NULL;
    
    CCISOTile* tile=tileAt(pos);
    if(tile){
        sprite=CCSprite::createWithTexture(tile->getTexture(), tile->getTextureRect());
    }
    
    return sprite;
}

/**
 * 删除tile
 */
void CCISOTileLayer::removeTileSpriteAt(float x,float y)
{
    removeTileSpriteAt(ccp(x,y));
}

void CCISOTileLayer::removeTileSpriteAt(const CCPoint& pos)
{
    CCAssert(false, "you must impl CCISOTileLayer::removeSpriteTileAt");
}


void CCISOTileLayer::scroll(const CCPoint& tOffset)
{
    CCLOG("CCISOTileLayer::scroll");
}

void CCISOTileLayer::scroll(float x,float y)
{
    scroll(ccp(x,y));
}

void CCISOTileLayer::parseInternalProperties()
{
    CCLOG("CCISOTileLayer::parseInternalProperties");
    // if cc_vertex=automatic, then tiles will be rendered using vertexz
    
    CCString *vertexz = propertyNamed("cc_vertexz");
    if (vertexz)
    {
        // If "automatic" is on, then parse the "cc_alpha_func" too
        if (vertexz->m_sString == "automatic")
        {
            m_bUseAutomaticVertexZ = true;
            CCString *alphaFuncVal = propertyNamed("cc_alpha_func");
            float alphaFuncValue = 0.0f;
            if (alphaFuncVal != NULL)
            {
                alphaFuncValue = alphaFuncVal->floatValue();
            }
            setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest));
            
            GLint alphaValueLocation = glGetUniformLocation(getShaderProgram()->getProgram(), kCCUniformAlphaTestValue);
            
            // NOTE: alpha test shader is hard-coded to use the equivalent of a glAlphaFunc(GL_GREATER) comparison
            getShaderProgram()->setUniformLocationWith1f(alphaValueLocation, alphaFuncValue);
        }
        else
        {
            m_nVertexZvalue = vertexz->intValue();
        }
    }
}

int  CCISOTileLayer::zOrderForPos(const CCPoint& pos)
{
    int ret = 0;
    unsigned int maxVal = 0;
//    maxVal = (unsigned int)(m_tLayerSize.width + m_tLayerSize.height);
    ret = (int)(maxVal - (pos.x + pos.y));

    return ret;
}

int CCISOTileLayer::vertexZForPos(const CCPoint& pos)
{
    int ret = 0;
    unsigned int maxVal = 0;
    if (m_bUseAutomaticVertexZ)
    {
        maxVal = (unsigned int)(m_tLayerSize.width + m_tLayerSize.height);
        ret = (int)(-(maxVal - (pos.x + pos.y)));
    }
    else
    {
        ret = m_nVertexZvalue;
    }
    
    return ret;
}

CCString* CCISOTileLayer::propertyNamed(const char *propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}


void CCISOTileLayer::setLayerSize(const CCSize& tLayerSize)
{
    m_tLayerSize = tLayerSize;
}

CCSize CCISOTileLayer::getLayerSize()
{
    return m_tLayerSize;
}


void CCISOTileLayer::setOffset(const CCPoint& tOffset)
{
    m_tOffset = tOffset;
}

void CCISOTileLayer::setOffset(float x,float y)
{
    m_tOffset.x=x;
	m_tOffset.y=y;
}

CCPoint CCISOTileLayer::getOffset()
{
    return m_tOffset;
}

void CCISOTileLayer::setMapTileSize(float width,float height)
{
    m_tMapTileSize.width=width;
    m_tMapTileSize.height=height;
}

void CCISOTileLayer::setMapTileSize(const CCSize& tMapTileSize)
{
    m_tMapTileSize = tMapTileSize;
}

const CCSize& CCISOTileLayer::getMapTileSize()
{
    return m_tMapTileSize;
}


void CCISOTileLayer::setLayerOrientation(unsigned int uLayerOrientation)
{
    m_uLayerOrientation = uLayerOrientation;
}

unsigned int CCISOTileLayer::getLayerOrientation()
{
    return m_uLayerOrientation;
}

void CCISOTileLayer::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOTileLayer::getProperties()
{
    return m_pProperties;
}

void CCISOTileLayer::setTiles(unsigned int* pTiles)
{
    m_pTiles = pTiles;
}

unsigned int* CCISOTileLayer::getTiles()
{
    return m_pTiles;
}


NS_CC_END
