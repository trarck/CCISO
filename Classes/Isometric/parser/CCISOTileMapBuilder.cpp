#include "CCISOTileMapBuilder.h"

#include "CCISOObjectGroupInfo.h"

#include "CCISOTileset.h"
#include "CCISOTileLayer.h"
#include "CCISOTileMap.h"
#include "CCISOObject.h"

NS_CC_BEGIN

CCISOTileMapBuilder::CCISOTileMapBuilder()
:m_pMap(NULL)
{
	
}

CCISOTileMapBuilder::~CCISOTileMapBuilder()
{

}

bool CCISOTileMapBuilder::init()
{
    return true;
}

bool CCISOTileMapBuilder::init(CCISOTileMap* pMap)
{
    m_pMap=pMap;
    return true;
}

void CCISOTileMapBuilder::buildWithMapInfo(CCISOMapInfo* mapInfo)
{
    CCAssert(m_pMap!=NULL, "buildWithMapInfo m_pMap can't be null");
    m_pMap->setMapSize(mapInfo->getMapSize());
    m_pMap->setTileSize(mapInfo->getTileSize());
    m_pMap->setProperties(mapInfo->getProperties());
    
    this->buildMapTilesets(mapInfo);
    this->buildMapLayers(mapInfo);
    this->buildMapObjectGroups(mapInfo);
}


void CCISOTileMapBuilder::buildMapTilesets(CCISOMapInfo* mapInfo)
{
    
    CCArray* tilesets = mapInfo->getTilesets();
    if (tilesets && tilesets->count()>0)
    {
        
        CCISOTilesetGroup* tilesetGroup=new CCISOTilesetGroup();
        
        CCISOTilesetInfo* tilesetInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(tilesets, pObj)
        {
            tilesetInfo = (CCISOTilesetInfo*)pObj;
            if (tilesetInfo)
            {
                buildMapTileset(tilesetInfo, mapInfo, tilesetGroup);
            }
        }
        
        m_pMap->setTilesetGroup(tilesetGroup);
        tilesetGroup->release();
    }
}

void CCISOTileMapBuilder::buildMapTileset(CCISOTilesetInfo* tilesetInfo,CCISOMapInfo* mapInfo,CCISOTilesetGroup* tilesetGroup)
{
    CCSize tileSize=mapInfo->getTileSize();
    int tileWidth=(int)tileSize.width;
    int tileHeight=(int)tileSize.height;
    
    CCISOTileset* tileset=new CCISOTileset();
    
    tileset->setTileWidth(tileWidth);
    tileset->setTileHeight(tileHeight);
    
    tileset->setName(tilesetInfo->getName());
    tileset->setFirstGid(tilesetInfo->getFirstGid());
    tileset->setTileSpacing(tilesetInfo->getSpacing());
    tileset->setMargin(tilesetInfo->getMargin());
    tileset->setTileOffset(tilesetInfo->getTileOffset());
    tileset->setProperties(tilesetInfo->getProperties());

    const char* imageSource=tilesetInfo->getImageSource();
    
    if(imageSource){
        tileset->setImageSource(tilesetInfo->getImageSource());
        tileset->setImageSize(tilesetInfo->getImageSize());
        tileset->loadFromImageSource();
        CCArray* tileInfos=tilesetInfo->getTiles();
        if(tileInfos){
            setMapTilesProperties(tileInfos,tileset);
        }
    }else{
        CCArray* tileInfos=tilesetInfo->getTiles();
        if(tileInfos){
            buildMapTiles(tileInfos, tileset);
        }
    }
    
    tilesetGroup->addTileset(tileset);
    tileset->release();
}

void CCISOTileMapBuilder::buildMapTiles(CCArray* tileInfos,CCISOTileset* tileset)
{
    CCAssert(tileInfos, "buildMapTiles tiles must non't be null");
    CCObject* pObj;

    CCARRAY_FOREACH(tileInfos, pObj){
        CCISOTileInfo* tileInfo=(CCISOTileInfo*)pObj;
        
        if(tileInfo->getImageSource()){
            unsigned int tileId=tileInfo->getId();
            
            CCSprite* sprite=new CCSprite();
            sprite->initWithFile(tileInfo->getImageSource());
            
            CCISOTile* tile=new CCISOTile();
            tile->init(tileId, tileset, sprite);
            tile->setProperties(tileInfo->getProperties());
            tileset->addTile(tile);
            
            sprite->release();
            tile->release();
        }
    }
}

void CCISOTileMapBuilder::setMapTilesProperties(CCArray* tileInfos,CCISOTileset* tileset)
{
    CCAssert(tileInfos, "setMapTilesProperties tiles must non't be null");
    CCObject* pObj;
    
    CCARRAY_FOREACH(tileInfos, pObj){
        CCISOTileInfo* tileInfo=(CCISOTileInfo*)pObj;
        CCISOTile* tile=tileset->tileForId(tileInfo->getId());
        tile->setProperties(tileInfo->getProperties());
    }
}

void CCISOTileMapBuilder::buildMapObjectGroups(CCISOMapInfo* mapInfo)
{
    
    CCArray* objectGroups = mapInfo->getObjectGroups();
    if (objectGroups && objectGroups->count()>0)
    {
        CCISOObjectGroupInfo* objectGroupInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(objectGroups, pObj)
        {
            objectGroupInfo = (CCISOObjectGroupInfo*)pObj;
            if (objectGroupInfo && objectGroupInfo->getVisible())
            {
                CCISOObjectGroup* objGroup=new CCISOObjectGroup();
                objGroup->setName(objectGroupInfo->getName());
                objGroup->setOffset(objectGroupInfo->getPositionOffset());
                objGroup->setProperties(objectGroupInfo->getProperties());
                buildMapObjects(objectGroupInfo->getObjects(), objGroup);
            }
        }
    }
}

void CCISOTileMapBuilder::buildMapObjects(CCArray* objects,CCISOObjectGroup* objectGroup)
{
    CCAssert(objects!=NULL, "buildMapObjects objects must non't be null");
    CCAssert(objectGroup!=NULL, "buildMapObjects objectGroup must non't be null");
    
    CCISOObjectInfo* objectInfo = NULL;
    CCObject* pObj = NULL;
    CCARRAY_FOREACH(objects, pObj)
    {
        objectInfo = (CCISOObjectInfo*)pObj;
        if (objectInfo && objectInfo->getVisible())
        {
            buildMapObject(objectInfo,objectGroup);
        }
    }
}

void CCISOTileMapBuilder::buildMapObject(CCISOObjectInfo* objectInfo,CCISOObjectGroup* objectGroup)
{
    CCISOObject* obj=new CCISOObject();
    obj->setName(objectInfo->getName());
    obj->setGid(objectInfo->getGid());
    obj->setPosition(objectInfo->getPosition());
    obj->setSize(objectInfo->getSize());
    obj->setType(objectInfo->getType());
    obj->setVisible(objectInfo->getVisible());
    obj->setProperties(objectInfo->getProperties());
    objectGroup->getObjects()->addObject(obj);
    obj->release();
}

void CCISOTileMapBuilder::buildMapLayers(CCISOMapInfo* mapInfo)
{
    int idx=0;
    
    CCArray* layers = mapInfo->getLayers();
    if (layers && layers->count()>0)
    {
        CCISOLayerInfo* layerInfo = NULL;
        CCObject* pObj = NULL;
        CCARRAY_FOREACH(layers, pObj)
        {
            layerInfo = (CCISOLayerInfo*)pObj;
            if (layerInfo && layerInfo->getVisible())
            {
                CCISOTileLayer *child = parseLayer(layerInfo, mapInfo);
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


CCISOTileLayer * CCISOTileMapBuilder::parseLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    //CCISOTilesetInfo *tileset = this->tilesetForLayer(layerInfo, mapInfo);
    //CCISOTileLayer *layer = CCISOTileLayer::create(tileset, layerInfo, mapInfo);
    //
    //// tell the layerinfo to release the ownership of the tiles map.
    //layerInfo->m_bOwnTiles = false;
    //layer->setupTiles();
    //
    //return layer;
	return NULL;
}

CCISOTilesetInfo * CCISOTileMapBuilder::tilesetForLayer(CCISOLayerInfo *layerInfo, CCISOMapInfo *mapInfo)
{
    CCSize size = layerInfo->getLayerSize();
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
                unsigned int* pTiles=layerInfo->getTiles();
                
                for( unsigned int y=0; y < size.height; y++ )
                {
                    for( unsigned int x=0; x < size.width; x++ )
                    {
                        unsigned int pos = (unsigned int)(x + size.width * y);
                        unsigned int gid = pTiles[ pos ];
                        
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
                            if( (gid & kCCFlippedMask) >= tileset->getFirstGid() )
                                return tileset;
                        }
                    }
                }
            }
        }
    }
    
    // If all the tiles are 0, return empty tileset
    CCLOG("cocos2d: Warning: ISO Layer '%s' has no tiles", layerInfo->getName());
    return NULL;
}




NS_CC_END
