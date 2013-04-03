#include "CCISOCoordinate.h"
#include "CCISOXMLReader.h"
#include "support/zip_support/ZipUtils.h"
#include "support/CCPointExtension.h"
#include "support/base64.h"
#include "CCISOTileMap.h"
#include "CCISOTileSet.h"
#include "CCISOTileLayer.h"
#include "CCISOObjectGroup.h"
#include "CCISOObject.h"

using namespace std;

NS_CC_BEGIN

/*
 void tmx_startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
 void tmx_endElement(void *ctx, const xmlChar *name);
 void tmx_characters(void *ctx, const xmlChar *ch, int len);
 */

static const char* valueForKey(const char *key, std::map<std::string, std::string>* dict)
{
    if (dict)
    {
        std::map<std::string, std::string>::iterator it = dict->find(key);
        return it!=dict->end() ? it->second.c_str() : "";
    }
    return "";
}

CCISOXMLReader::CCISOXMLReader()
:m_pMap(NULL)
,m_nCurrentElement(0)
,m_uCurrentGid(0)
,m_nLayerAttribs(0)
,m_bStoringCharacters(0)
{

}

CCISOXMLReader::~CCISOXMLReader()
{
    CCLOG("CCISOXMLReader destroy");
    CC_SAFE_RELEASE(m_pMap);
}

CCISOXMLReader * CCISOXMLReader::formatWithXMLFile(const char *tmxFile)
{
    CCISOXMLReader *pRet = new CCISOXMLReader();
    if(pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOXMLReader * CCISOXMLReader::formatWithXML(const char* tmxString, const char* resourcePath)
{
    CCISOXMLReader *pRet = new CCISOXMLReader();
    if(pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCISOXMLReader::internalInit(const char* tmxFileName, const char* resourcePath)
{
    m_pMap=new CCISOTileMap();
    m_pMap->init();
    
        
    if (tmxFileName != NULL)
    {
        m_sTMXFileName = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(tmxFileName);
    }
    
    if (resourcePath != NULL)
    {
        m_sResources = resourcePath;
    }
    m_sCurrentString = "";
        
}

bool CCISOXMLReader::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool CCISOXMLReader::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(m_sTMXFileName.c_str());
}

bool CCISOXMLReader::parseXMLString(const char *xmlString)
{
    int len = strlen(xmlString);
    if (xmlString == NULL || len <= 0)
    {
        return false;
    }
    
    CCSAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);
    
    return parser.parse(xmlString, len);
}

bool CCISOXMLReader::parseXMLFile(const char *xmlFilename)
{
    CCSAXParser parser;
    
    if (false == parser.init("UTF-8") )
    {
        return false;
    }
    
    parser.setDelegator(this);
    
    return parser.parse(xmlFilename);
}


// the XML parser calls here with all the elements
void CCISOXMLReader::startElement(void *ctx, const char *name, const char **atts)
{
    CC_UNUSED_PARAM(ctx);
    std::string elementName = (char*)name;
    std::map<std::string, std::string> *attributeDict = new std::map<std::string, std::string>();
    if(atts && atts[0])
    {
        for(int i = 0; atts[i]; i += 2)
        {
            std::string key = (char*)atts[i];
            std::string value = (char*)atts[i+1];
            attributeDict->insert(std::pair<std::string, std::string>(key, value));
        }
    }
    if(elementName == "map")
    {
        std::string version = valueForKey("version", attributeDict);
        if ( version != "1.0")
        {
            CCLOG("cocos2d: TMXFormat: Unsupported TMX version: %@", version.c_str());
        }
//        std::string orientationStr = valueForKey("orientation", attributeDict);
//        if ( orientationStr  == "isometric")
//            m_pMap->setOrientation(CCTMXOrientationIso);
//        else
//            CCLOG("cocos2d: TMXFomat: Unsupported orientation: %d", m_pMap->getOrientation());
        
        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        m_pMap->setMapSize(s);
        
        s.width = (float)atof(valueForKey("tilewidth", attributeDict));
        s.height = (float)atof(valueForKey("tileheight", attributeDict));
        m_pMap->setTileSize(s);
        
        // The parent element is now "map"
        m_nCurrentElement=ISOPropertyMap;
        
    }
    else if(elementName == "tileset")
    {
        // If this is an external tileset then start parsing that
        std::string externalTilesetFilename = valueForKey("source", attributeDict);
        if (externalTilesetFilename != "")
        {
            if (m_sTMXFileName.find_last_of("/") != string::npos)
            {
                string dir = m_sTMXFileName.substr(0, m_sTMXFileName.find_last_of("/") + 1);
                externalTilesetFilename = dir + externalTilesetFilename;
            }
            else
            {
                externalTilesetFilename = m_sResources + "/" + externalTilesetFilename;
            }
            externalTilesetFilename = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(externalTilesetFilename.c_str());
            
            this->parseXMLFile(externalTilesetFilename.c_str());
        }
        else
        {
            CCISOTileset *tileset = new CCISOTileset();
            tileset->setName(valueForKey("name", attributeDict));
            tileset->setFirstGid((unsigned int)atoi(valueForKey("firstgid", attributeDict)));
            tileset->setTileSpacing((unsigned int)atoi(valueForKey("spacing", attributeDict)));
            tileset->setMargin((unsigned int)atoi(valueForKey("margin", attributeDict)));

            tileset->setTileWidth(atoi(valueForKey("tilewidth", attributeDict)));
            tileset->setTileHeight(atoi(valueForKey("tileheight", attributeDict)));
            
            m_pMap->getTilesetGroup()->addTileset(tileset);
            
            tileset->release();
        }
    }
    else if(elementName == "tile")
    {
        
        CCISOTileset* tileset = (CCISOTileset*) m_pMap->getTilesetGroup()->getTilesets()->lastObject();
        
        m_uCurrentGid= atoi(valueForKey("id", attributeDict));//+tileset->getFirstGid();
        
//        CCDictionary *dict = new CCDictionary();
//   
//        tileset->getTileProperties()->setObject(dict, m_uCurrentGid);
//        CC_SAFE_RELEASE(dict);
        
        CCISOTile* tile=new CCISOTile();
        tile->init(m_uCurrentGid, tileset);
        
        tileset->getTiles()->addObject(tile);
        tile->release();
        
        m_nCurrentElement=ISOPropertyTile;
        
    }
    else if(elementName == "layer")
    {
        CCTMXLayerInfo *layer = new CCTMXLayerInfo();
        layer->m_sName = valueForKey("name", attributeDict);
        
        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        layer->m_tLayerSize = s;
        
        std::string visible = valueForKey("visible", attributeDict);
        layer->m_bVisible = !(visible == "0");
        
        std::string opacity = valueForKey("opacity", attributeDict);
        if( opacity != "" )
        {
            layer->m_cOpacity = (unsigned char)(255 * atof(opacity.c_str()));
        }
        else
        {
            layer->m_cOpacity = 255;
        }
        
        float x = (float)atof(valueForKey("x", attributeDict));
        float y = (float)atof(valueForKey("y", attributeDict));
        layer->m_tOffset = ccp(x,y);
        
        m_pMap->getTileLayers()->addObject(layer);
        layer->release();
        
        // The parent element is now "layer"
        m_nCurrentElement=ISOPropertyLayer;
        
    }
    else if(elementName == "objectgroup")
    {
        CCISOObjectGroup *objectGroup = new CCISOObjectGroup();
        objectGroup->setName(valueForKey("name", attributeDict));
        CCPoint positionOffset;
        positionOffset.x = (float)atof(valueForKey("x", attributeDict)) * m_pMap->getTileSize().width;
        positionOffset.y = (float)atof(valueForKey("y", attributeDict)) * m_pMap->getTileSize().height;
        objectGroup->setOffset(positionOffset);
        
        m_pMap->getObjectGroups()->addObject(objectGroup);
        objectGroup->release();
        
        // The parent element is now "objectgroup"
        m_nCurrentElement=ISOPropertyObjectGroup;
        
    }
    else if(elementName == "image")
    {
        // build full path
        std::string imagename = valueForKey("source", attributeDict);
        
        if (m_sTMXFileName.find_last_of("/") != string::npos)
        {
            string dir = m_sTMXFileName.substr(0, m_sTMXFileName.find_last_of("/") + 1);
            imagename=dir+imagename;
            
        }
        else
        {
            imagename=m_sResources + (m_sResources.size() ? "/" : "") + imagename;

        }

        
        if ( m_nCurrentElement == ISOPropertyLayer ){
            
            CCISOTileset* tileset = (CCISOTileset*)m_pMap->getTilesetGroup()->getTilesets()->lastObject();
            tileset->setImageSource(imagename.c_str());
            
        }else if(m_nCurrentElement == ISOPropertyTile){
            CCISOTileset* tileset = (CCISOTileset*)m_pMap->getTilesetGroup()->getTilesets()->lastObject();
            
        }
    }
    else if(elementName == "data")
    {
        std::string encoding = valueForKey("encoding", attributeDict);
        std::string compression = valueForKey("compression", attributeDict);
        
        if( encoding == "base64" )
        {
            m_nLayerAttribs|=ISOLayerAttribBase64;
            m_bStoringCharacters=true;
            
            if( compression == "gzip" )
            {
                m_nLayerAttribs|=ISOLayerAttribGzip;
            } else
                if (compression == "zlib")
                {
                    m_nLayerAttribs|=ISOLayerAttribZlib;
                }
            CCAssert( compression == "" || compression == "gzip" || compression == "zlib", "TMX: unsupported compression method" );
        }
        CCAssert( m_nLayerAttribs != ISOLayerAttribNone, "TMX tile map: Only base64 and/or gzip/zlib maps are supported" );
    }
    else if(elementName == "object")
    {

        CCISOObjectGroup* objectGroup = (CCISOObjectGroup*)m_pMap->getObjectGroups()->lastObject();
        
        // The value for "type" was blank or not a valid class name
        // Create an instance of TMXObjectInfo to store the object and its properties
        CCISOObject *obj = new CCISOObject();
        
        obj->setName(valueForKey("name", attributeDict));
        
        obj->setType(valueForKey("type", attributeDict));
        
        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        obj->setSize(s);
               
        // But X and Y since they need special treatment
        // X
        CCPoint pos;
        const char* value = valueForKey("x", attributeDict);
        if( value )
        {
            pos.x = (float)atof(value) + objectGroup->getOffset().x;
        }
        
        // Y
        value = valueForKey("y", attributeDict);
        if( value )  {
            float y = (float)atof(value) + objectGroup->getOffset().y;
            
            // Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
            pos.y = (m_pMap->getMapSize().height * m_pMap->getTileSize().height) - y - s.height;
            
        }
        obj->setPosition(pos);
        
        // Add the object to the objectGroup
        objectGroup->getObjects()->addObject(obj);
        obj->release();
        
        // The parent element is now "object"
        m_nCurrentElement=ISOPropertyObject;
        
    }
    else if(elementName == "property")
    {
        if ( m_nCurrentElement == ISOPropertyNone )
        {
            CCLOG( "TMX tile map: Parent element is unsupported. Cannot add property named '%s' with value '%s'",
                  valueForKey("name", attributeDict), valueForKey("value",attributeDict) );
        }
        else if ( m_nCurrentElement == ISOPropertyMap )
        {
            // The parent element is the map
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            m_pMap->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_nCurrentElement == ISOPropertyLayer )
        {
            // The parent element is the last layer
            CCISOTileLayer* layer = (CCISOTileLayer*)m_pMap->getTileLayers()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            // Add the property to the layer
            layer->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_nCurrentElement == ISOPropertyObjectGroup )
        {
            // The parent element is the last object group
            CCISOObjectGroup* objectGroup = (CCISOObjectGroup*)m_pMap->getObjectGroups()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            objectGroup->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_nCurrentElement == ISOPropertyObject )
        {
            // The parent element is the last object
            CCISOObjectGroup* objectGroup = (CCISOObjectGroup*)m_pMap->getObjectGroups()->lastObject();
            CCISOObject* obj = (CCISOObject*)objectGroup->getObjects()->lastObject();
            
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            obj->getProperties()->setObject(value,key.c_str());
            value->release();
        }
        else if ( m_nCurrentElement == ISOPropertyTile )
        {
            CCISOTileset* tileset =(CCISOTileset*)m_pMap->getTilesetGroup()->getTilesets()->lastObject();
//            CCDictionary* tileProperties=tileset->getTileProperties();
//            CCDictionary* dict = (CCDictionary*)tileProperties->objectForKey(m_uCurrentGid);
            
            CCISOTile* tile=(CCISOTile*)tileset->getTiles()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            tile->getProperties()->setObject(value, key.c_str());
            value->release();
        }
    }
    else if (elementName == "polygon")
    {
        // find parent object's dict and add polygon-points to it
        // CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_pObjectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject(attributeDict objectForKey:@"points"] forKey:@"polygonPoints"];
        
    }
    else if (elementName == "polyline")
    {
        // find parent object's dict and add polyline-points to it
        // CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_pObjectGroups->lastObject();
        // CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
        // TODO: dict->setObject:[attributeDict objectForKey:@"points"] forKey:@"polylinePoints"];
    }
    
    if (attributeDict)
    {
        attributeDict->clear();
        delete attributeDict;
    }
}

void CCISOXMLReader::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    std::string elementName = (char*)name;
    
    int len = 0;
    
    if(elementName == "data" && m_nLayerAttribs&ISOLayerAttribBase64)
    {
        m_bStoringCharacters=false;
        
        CCISOTileLayer* layer = (CCISOTileLayer*)m_pMap->getTileLayers()->lastObject();
        
        std::string currentString = this->getCurrentString();
        unsigned char *buffer;
        len = base64Decode((unsigned char*)currentString.c_str(), (unsigned int)currentString.length(), &buffer);
        if( ! buffer )
        {
            CCLOG("cocos2d: TiledMap: decode data error");
            return;
        }
        
        if( m_nLayerAttribs & (ISOLayerAttribGzip | ISOLayerAttribZlib) )
        {
            unsigned char *deflated;
            CCSize s = layer->getLayerSize();
            // int sizeHint = s.width * s.height * sizeof(uint32_t);
            int sizeHint = (int)(s.width * s.height * sizeof(unsigned int));
            
            int inflatedLen = ZipUtils::ccInflateMemoryWithHint(buffer, len, &deflated, sizeHint);
            CCAssert(inflatedLen == sizeHint, "");
            
            inflatedLen = (size_t)&inflatedLen; // XXX: to avoid warnings in compiler
            
            delete [] buffer;
            buffer = NULL;
            
            if( ! deflated )
            {
                CCLOG("cocos2d: TiledMap: inflate data error");
                return;
            }
            
            layer->setTiles((unsigned int*) deflated);
        }
        else
        {
            layer->setTiles( (unsigned int*) buffer);
        }
        
        this->setCurrentString("");
        
    }
    else if (elementName == "map")
    {
        // The map element has ended
        m_nCurrentElement=ISOPropertyNone;
    }
    else if (elementName == "layer")
    {
        // The layer element has ended
        m_nCurrentElement=ISOPropertyNone;
    }
    else if (elementName == "objectgroup")
    {
        // The objectgroup element has ended
        m_nCurrentElement=ISOPropertyNone;
    }
    else if (elementName == "object")
    {
        // The object element has ended
        m_nCurrentElement=ISOPropertyNone;
    }
    else if (elementName == "tile")
    {
        // The tile element has ended
        m_nCurrentElement=ISOPropertyNone;
    }
}

void CCISOXMLReader::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    std::string pText((char*)ch,0,len);
    
    if (m_bStoringCharacters)
    {
        std::string currentString = this->getCurrentString();
        currentString += pText;
        this->setCurrentString(currentString.c_str());
    }
}

CCISOTileMap* CCISOXMLReader::getMap()
{
    return m_pMap;
}


NS_CC_END
