
#include "CCISOTileMap.h"

NS_CC_BEGIN

CCISOTileMap::CCISOTileMap()
:m_tMapSize(CCSizeZero)
,m_pTileLayers(NULL)
,m_pObjectLayers(NULL)
,m_pProperties(NULL)
,m_pTileProperties(NULL)
{
	
}

CCISOTileMap::~CCISOTileMap()
{
    CC_SAFE_RELEASE(m_pProperties);
    CC_SAFE_RELEASE(m_pObjectLayers);
    CC_SAFE_RELEASE(m_pTileProperties);
}

CCISOTileMap * CCISOTileMap::createWithXMLFile(const char *xmlFile)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithXMLFile(xmlFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOTileMap * CCISOTileMap::createWithXMLFile(const char *xmlFile)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithJSONFile(xmlFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOTileMap* CCISOTileMap::createWithXML(const char* tmxString, const char* resourcePath)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOTileMap* CCISOTileMap::createWithJSON(const char* jsonString, const char* resourcePath)
{
    CCISOTileMap *pRet = new CCISOTileMap();
    if (pRet->initWithJSON(jsonString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CCISOTileMap::init()
{
	return true;
}

bool CCISOTileMap::initWithXMLFile(const char *xmlFile)
{
    CCAssert(mapFile != NULL && strlen(mapFile)>0, "CCISOTileMap: map file should not bi NULL");
    
    setContentSize(CCSizeZero);
    
    CCISOXMLParser *xmlParser = CCISOXMLParser::formatWithXMLFile(xmlFile);
    
    CCISOMapInfo *mapInfo=xmlParser->getMapInfo();
    
    if (! mapInfo)
    {
        return false;
    }
    CCAssert( mapInfo->getTilesets()->count() != 0, "CCISOTileMap: Map not found. Please check the filename.");
    buildWithMapInfo(mapInfo);
    
    return true;
}

bool CCISOTileMap::initWithJSONFile(const char *jsonFile)
{
    CCAssert( false, "CCISOTileMap::initWithJSONFile not support.");
    
    return true;
}

bool CCISOTileMap::initWithXML(const char* xmlString, const char* resourcePath)
{
    setContentSize(CCSizeZero);
        
    CCISOXMLParser *xmlParser = CCISOXMLParser::formatWithXMLFile(xmlString, resourcePath);
    CCISOMapInfo *mapInfo=xmlParser->getMapInfo();
    
    CCAssert( mapInfo->getTilesets()->count() != 0, "CCISOTileMap: Map not found. Please check the filename.");
    buildWithMapInfo(mapInfo);
    
    return true;
}

bool CCISOTileMap::initWithJSON(const char* jsonString, const char* resourcePath)
{
    CCAssert( false, "CCISOTileMap::initWithJSON not support.");
    
    return true;
}

// protected
CCISOLayer * CCISOTileMap::parseLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    CCISOTilesetInfo *tileset = this->tilesetForLayer(layerInfo, mapInfo);
    CCISOLayer *layer = CCISOLayer::create(tileset, layerInfo, mapInfo);
    
    // tell the layerinfo to release the ownership of the tiles map.
    layerInfo->m_bOwnTiles = false;
    layer->setupTiles();
    
    return layer;
}

CCISOTilesetInfo * CCISOTiledMap::tilesetForLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    CCSize size = layerInfo->m_tLayerSize;
    CCArray* tilesets = mapInfo->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        CCISOTilesetInfo* tileset = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH_REVERSE(tilesets, pObj)
        {
            tileset = (CCISOTilesetInfo*)pObj;
            if (tileset)
            {
                for( unsigned int y=0; y < size.height; y++ )
                {
                    for( unsigned int x=0; x < size.width; x++ )
                    {
                        unsigned int pos = (unsigned int)(x + size.width * y);
                        unsigned int gid = layerInfo->m_pTiles[ pos ];
                        
                        // gid are stored in little endian.
                        // if host is big endian, then swap
                        //if( o == CFByteOrderBigEndian )
                        //    gid = CFSwapInt32( gid );
                        /* We support little endian.*/
                        
                        // XXX: gid == 0 --> empty tile
                        if( gid != 0 )
                        {
                            // Optimization: quick return
                            // if the layer is invalid (more than 1 tileset per layer) an CCAssert will be thrown later
                            if( (gid & kCCFlippedMask) >= tileset->m_uFirstGid )
                                return tileset;
                        }
                    }
                }
            }
        }
    }
    
    // If all the tiles are 0, return empty tileset
    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->m_sName.c_str());
    return NULL;
}

void CCISOTiledMap::buildWithMapInfo(CCISOMapInfo* mapInfo)
{
    m_tMapSize = mapInfo->getMapSize();
    m_tTileSize = mapInfo->getTileSize();
    m_nMapOrientation = mapInfo->getOrientation();
    
    this->setObjectLayers( mapInfo->getObjectGroups());
    this->setProperties(mapInfo->getProperties());
    this->setTileProperties(mapInfo->getTileProperties());
    
   
    int idx=0;
    
    CCArray* layers = mapInfo->getLayers();
    if (layers && layers->count()>0)
    {
        CCISOLayerInfo* layerInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(layers, pObj)
        {
            layerInfo = (CCISOLayerInfo*)pObj;
            if (layerInfo && layerInfo->m_bVisible)
            {
                CCISOLayer *child = parseLayer(layerInfo, mapInfo);
                addChild((CCNode*)child, idx, idx);
                
                // update content size with the max size
                const CCSize& childSize = child->getContentSize();
                CCSize currentSize = this->getContentSize();
                currentSize.width = MAX( currentSize.width, childSize.width );
                currentSize.height = MAX( currentSize.height, childSize.height );
                this->setContentSize(currentSize);
                
                idx++;
            }
        }
    }
}

// public
CCISOLayer * CCISOTiledMap::layerNamed(const char *layerName)
{
    CCAssert(layerName != NULL && strlen(layerName) > 0, "Invalid layer name!");
    
    if (m_pTileLayers && m_pTileLayers->count()>0){
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pTileLayers, pObj)
        {
            CCISOLayer* layer = dynamic_cast<CCISOLayer*>(pObj);
            if(layer)
            {
                if(0 == strcmp(layer->getLayerName(), layerName))
                {
                    return layer;
                }
            }
        }
    }
    // layer not found
    return NULL;
}

CCISOObjectGroup * CCISOTiledMap::objectLayerNamed(const char *layerName)
{
    CCAssert(layerName != NULL && strlen(layerName) > 0, "Invalid layer name!");
    
    std::string sLayerName = layerName;
    if (m_pObjectLayers && m_pObjectLayers->count()>0)
    {
        CCISOObjectGroup* objectGroup = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(m_pObjectLayers, pObj)
        {
            objectGroup = (CCISOObjectGroup*)(pObj);
            if (objectGroup && objectGroup->getGroupName() == sGroupName)
            {
                return objectGroup;
            }
        }
    }
    
    // objectGroup not found
    return NULL;
}

CCString* CCISOTiledMap::propertyNamed(const char *propertyName)
{
    return (CCString*)m_pProperties->objectForKey(propertyName);
}

CCDictionary* CCISOTiledMap::propertiesForGID(int GID)
{
    return (CCDictionary*)m_pTileProperties->objectForKey(GID);
}


void CCISOTileMap::setMapSize(CCSize tMapSize)
{
    m_tMapSize = tMapSize;
}

CCSize CCISOTileMap::getMapSize()
{
    return m_tMapSize;
}

void CCISOTileMap::setTileSize(const CCSize& tTileSize)
{
    m_tTileSize = tTileSize;
}

const CCSize& CCISOTileMap::getTileSize()
{
    return m_tTileSize;
}

void CCISOTileMap::setName(const char* pName)
{
    m_pName = pName;
}

const char* CCISOTileMap::getName()
{
    return m_pName;
}

void CCISOTileMap::setMapOrientation(int nMapOrientation)
{
    m_nMapOrientation = nMapOrientation;
}

int CCISOTileMap::getMapOrientation()
{
    return m_nMapOrientation;
}

void CCISOTileMap::setObjectLayers(CCArray* pObjectLayers)
{
    CC_SAFE_RETAIN(pObjectLayers);
    CC_SAFE_RELEASE(m_pObjectLayers);
    m_pObjectLayers = pObjectLayers;
}

CCArray* CCISOTileMap::getObjectLayers()
{
    return m_pObjectLayers;
}

void CCISOTileMap::setProperties(CCDictionary* pProperties)
{
    CC_SAFE_RETAIN(pProperties);
    CC_SAFE_RELEASE(m_pProperties);
    m_pProperties = pProperties;
}

CCDictionary* CCISOTileMap::getProperties()
{
    return m_pProperties;
}

void CCISOTileMap::setTileProperties(CCDictionary* pTileProperties)
{
    CC_SAFE_RETAIN(pTileProperties);
    CC_SAFE_RELEASE(m_pTileProperties);
    m_pTileProperties = pTileProperties;
}

CCDictionary* CCISOTileMap::getTileProperties()
{
    return m_pTileProperties;
}


NS_CC_END
