
#include "CCISOTileMapBuilder.h"
#include "CCISOTileset.h"

NS_CC_BEGIN

CCISOTileMapBuilder::CCISOTileMapBuilder()
{
	
}

CCISOTileMapBuilder::~CCISOTileMapBuilder()
{

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

void CCISOTileMapBuilder::buildWithMapInfo(CCISOMapInfo* mapInfo)
{
    m_tMapSize = mapInfo->getMapSize();
    m_tTileSize = mapInfo->getTileSize();
    m_nMapOrientation = mapInfo->getOrientation();
    
    this->setTileLayers(mapInfo->getLayers());
    this->setObjectGroups( mapInfo->getObjectGroups());
    this->setProperties(mapInfo->getProperties());
    this->setTileProperties(mapInfo->getTileProperties());

    this->buildMapLayers(mapInfo);
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
            if (layerInfo && layerInfo->m_bVisible)
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

NS_CC_END
