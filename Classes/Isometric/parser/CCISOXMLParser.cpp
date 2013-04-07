#include "CCISOCoordinate.h"
#include "CCISOXMLParser.h"
#include "support/zip_support/ZipUtils.h"
#include "support/CCPointExtension.h"
#include "support/base64.h"

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

CCISOXMLParser::CCISOXMLParser()
:m_pMapInfo(NULL)
{

}

CCISOXMLParser::~CCISOXMLParser()
{
    CCLOG("CCISOXMLParser destroy");
    CC_SAFE_RELEASE(m_pMapInfo);
}

CCISOXMLParser * CCISOXMLParser::formatWithXMLFile(const char *tmxFile)
{
    CCISOXMLParser *pRet = new CCISOXMLParser();
    if(pRet->initWithTMXFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CCISOXMLParser * CCISOXMLParser::formatWithXML(const char* tmxString, const char* resourcePath)
{
    CCISOXMLParser *pRet = new CCISOXMLParser();
    if(pRet->initWithXML(tmxString, resourcePath))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CCISOXMLParser::internalInit(const char* tmxFileName, const char* resourcePath)
{
    m_pMapInfo=new CCISOMapInfo();
    m_pMapInfo->init();
    
        
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
bool CCISOXMLParser::initWithXML(const char* tmxString, const char* resourcePath)
{
    internalInit(NULL, resourcePath);
    return parseXMLString(tmxString);
}

bool CCISOXMLParser::initWithTMXFile(const char *tmxFile)
{
    internalInit(tmxFile, NULL);
    return parseXMLFile(m_sTMXFileName.c_str());
}

bool CCISOXMLParser::parseXMLString(const char *xmlString)
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

bool CCISOXMLParser::parseXMLFile(const char *xmlFilename)
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
void CCISOXMLParser::startElement(void *ctx, const char *name, const char **atts)
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
        std::string orientationStr = valueForKey("orientation", attributeDict);
        if( orientationStr == "orthogonal")
            m_pMapInfo->setOrientation(CCTMXOrientationOrtho);
        else if ( orientationStr  == "isometric")
            m_pMapInfo->setOrientation(CCTMXOrientationIso);
        else if( orientationStr == "hexagonal")
            m_pMapInfo->setOrientation(CCTMXOrientationHex);
        else
            CCLOG("cocos2d: TMXFomat: Unsupported orientation: %d", m_pMapInfo->getOrientation());
        
        CCSize s;
        s.width = (float)atof(valueForKey("width", attributeDict));
        s.height = (float)atof(valueForKey("height", attributeDict));
        m_pMapInfo->setMapSize(s);
        
        s.width = (float)atof(valueForKey("tilewidth", attributeDict));
        s.height = (float)atof(valueForKey("tileheight", attributeDict));
        m_pMapInfo->setTileSize(s);
        
        // The parent element is now "map"
        m_pMapInfo->setParentElement(TMXPropertyMap);
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
            CCTMXTilesetInfo *tileset = new CCTMXTilesetInfo();
            tileset->m_sName = valueForKey("name", attributeDict);
            tileset->m_uFirstGid = (unsigned int)atoi(valueForKey("firstgid", attributeDict));
            tileset->m_uSpacing = (unsigned int)atoi(valueForKey("spacing", attributeDict));
            tileset->m_uMargin = (unsigned int)atoi(valueForKey("margin", attributeDict));
            CCSize s;
            s.width = (float)atof(valueForKey("tilewidth", attributeDict));
            s.height = (float)atof(valueForKey("tileheight", attributeDict));
            tileset->m_tTileSize = s;
            
            m_pMapInfo->getTilesets()->addObject(tileset);
            tileset->release();
        }
    }
    else if(elementName == "tile")
    {
        CCTMXTilesetInfo* info = (CCTMXTilesetInfo*)m_pMapInfo->getTilesets()->lastObject();
        CCDictionary *dict = new CCDictionary();
        m_pMapInfo->setParentGID(info->m_uFirstGid + atoi(valueForKey("id", attributeDict)));
        m_pMapInfo->getTileProperties()->setObject(dict, m_pMapInfo->getParentGID());
        CC_SAFE_RELEASE(dict);
        
        m_pMapInfo->setParentElement(TMXPropertyTile);
        
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
        
        m_pMapInfo->getLayers()->addObject(layer);
        layer->release();
        
        // The parent element is now "layer"
        m_pMapInfo->setParentElement(TMXPropertyLayer);
        
    }
    else if(elementName == "objectgroup")
    {
        CCTMXObjectGroup *objectGroup = new CCTMXObjectGroup();
        objectGroup->setGroupName(valueForKey("name", attributeDict));
        CCPoint positionOffset;
        positionOffset.x = (float)atof(valueForKey("x", attributeDict)) * m_pMapInfo->getTileSize().width;
        positionOffset.y = (float)atof(valueForKey("y", attributeDict)) * m_pMapInfo->getTileSize().height;
        objectGroup->setPositionOffset(positionOffset);
        
        m_pMapInfo->getObjectGroups()->addObject(objectGroup);
        objectGroup->release();
        
        // The parent element is now "objectgroup"
        m_pMapInfo->setParentElement(TMXPropertyObjectGroup);
        
    }
    else if(elementName == "image")
    {
        CCTMXTilesetInfo* tileset = (CCTMXTilesetInfo*)m_pMapInfo->getTilesets()->lastObject();
        
        // build full path
        std::string imagename = valueForKey("source", attributeDict);
        
        if (m_sTMXFileName.find_last_of("/") != string::npos)
        {
            string dir = m_sTMXFileName.substr(0, m_sTMXFileName.find_last_of("/") + 1);
            tileset->m_sSourceImage = dir + imagename;
        }
        else
        {
            tileset->m_sSourceImage = m_sResources + (m_sResources.size() ? "/" : "") + imagename;
        }
    }
    else if(elementName == "data")
    {
        std::string encoding = valueForKey("encoding", attributeDict);
        std::string compression = valueForKey("compression", attributeDict);
        
        if( encoding == "base64" )
        {
            int layerAttribs = m_pMapInfo->getLayerAttribs();
            m_pMapInfo->setLayerAttribs(layerAttribs | TMXLayerAttribBase64);
            m_pMapInfo->setStoringCharacters(true);
            
            if( compression == "gzip" )
            {
                layerAttribs = m_pMapInfo->getLayerAttribs();
                m_pMapInfo->setLayerAttribs(layerAttribs | TMXLayerAttribGzip);
            } else
                if (compression == "zlib")
                {
                    layerAttribs = m_pMapInfo->getLayerAttribs();
                    m_pMapInfo->setLayerAttribs(layerAttribs | TMXLayerAttribZlib);
                }
            CCAssert( compression == "" || compression == "gzip" || compression == "zlib", "TMX: unsupported compression method" );
        }
        CCAssert( m_pMapInfo->getLayerAttribs() != TMXLayerAttribNone, "TMX tile map: Only base64 and/or gzip/zlib maps are supported" );
        
    }
    else if(elementName == "object")
    {
        char buffer[32] = {0};
        CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_pMapInfo->getObjectGroups()->lastObject();
        
        // The value for "type" was blank or not a valid class name
        // Create an instance of TMXObjectInfo to store the object and its properties
        CCDictionary *dict = new CCDictionary();
        // Parse everything automatically
        const char* pArray[] = {"name", "type", "width", "height", "gid"};
        
        for( int i = 0; i < sizeof(pArray)/sizeof(pArray[0]); ++i )
        {
            const char* key = pArray[i];
            CCString* obj = new CCString(valueForKey(key, attributeDict));
            if( obj )
            {
                obj->autorelease();
                dict->setObject(obj, key);
            }
        }
        
        // But X and Y since they need special treatment
        // X
        
        const char* value = valueForKey("x", attributeDict);
        if( value )
        {
            int x = atoi(value) + (int)objectGroup->getPositionOffset().x;
            sprintf(buffer, "%d", x);
            CCString* pStr = new CCString(buffer);
            pStr->autorelease();
            dict->setObject(pStr, "x");
        }
        
        // Y
        value = valueForKey("y", attributeDict);
        if( value )  {
            int y = atoi(value) + (int)objectGroup->getPositionOffset().y;
            
            // Correct y position. (Tiled uses Flipped, cocos2d uses Standard)
            y = (int)(m_pMapInfo->getMapSize().height * m_pMapInfo->getTileSize().height) - y - atoi(valueForKey("height", attributeDict));
            sprintf(buffer, "%d", y);
            CCString* pStr = new CCString(buffer);
            pStr->autorelease();
            dict->setObject(pStr, "y");
        }
        
        // Add the object to the objectGroup
        objectGroup->getObjects()->addObject(dict);
        dict->release();
        
        // The parent element is now "object"
        m_pMapInfo->setParentElement(TMXPropertyObject);
        
    }
    else if(elementName == "property")
    {
        if ( m_pMapInfo->getParentElement() == TMXPropertyNone )
        {
            CCLOG( "TMX tile map: Parent element is unsupported. Cannot add property named '%s' with value '%s'",
                  valueForKey("name", attributeDict), valueForKey("value",attributeDict) );
        }
        else if ( m_pMapInfo->getParentElement() == TMXPropertyMap )
        {
            // The parent element is the map
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            m_pMapInfo->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_pMapInfo->getParentElement() == TMXPropertyLayer )
        {
            // The parent element is the last layer
            CCTMXLayerInfo* layer = (CCTMXLayerInfo*)m_pMapInfo->getLayers()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            std::string key = valueForKey("name", attributeDict);
            // Add the property to the layer
            layer->getProperties()->setObject(value, key.c_str());
            value->release();
            
        }
        else if ( m_pMapInfo->getParentElement() == TMXPropertyObjectGroup )
        {
            // The parent element is the last object group
            CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_pMapInfo->getObjectGroups()->lastObject();
            CCString *value = new CCString(valueForKey("value", attributeDict));
            const char* key = valueForKey("name", attributeDict);
            objectGroup->getProperties()->setObject(value, key);
            value->release();
            
        }
        else if ( m_pMapInfo->getParentElement() == TMXPropertyObject )
        {
            // The parent element is the last object
            CCTMXObjectGroup* objectGroup = (CCTMXObjectGroup*)m_pMapInfo->getObjectGroups()->lastObject();
            CCDictionary* dict = (CCDictionary*)objectGroup->getObjects()->lastObject();
            
            const char* propertyName = valueForKey("name", attributeDict);
            CCString *propertyValue = new CCString(valueForKey("value", attributeDict));
            dict->setObject(propertyValue, propertyName);
            propertyValue->release();
        }
        else if ( m_pMapInfo->getParentElement() == TMXPropertyTile )
        {
            CCDictionary* dict = (CCDictionary*)m_pMapInfo->getTileProperties()->objectForKey(m_pMapInfo->getParentGID());
            
            const char* propertyName = valueForKey("name", attributeDict);
            CCString *propertyValue = new CCString(valueForKey("value", attributeDict));
            dict->setObject(propertyValue, propertyName);
            propertyValue->release();
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

void CCISOXMLParser::endElement(void *ctx, const char *name)
{
    CC_UNUSED_PARAM(ctx);
    std::string elementName = (char*)name;
    
    int len = 0;
    
    if(elementName == "data" && m_pMapInfo->getLayerAttribs()&TMXLayerAttribBase64)
    {
        m_pMapInfo->setStoringCharacters(false);
        
        CCTMXLayerInfo* layer = (CCTMXLayerInfo*)m_pMapInfo->getLayers()->lastObject();
        
        std::string currentString = this->getCurrentString();
        unsigned char *buffer;
        len = base64Decode((unsigned char*)currentString.c_str(), (unsigned int)currentString.length(), &buffer);
        if( ! buffer )
        {
            CCLOG("cocos2d: TiledMap: decode data error");
            return;
        }
        
        if( m_pMapInfo->getLayerAttribs() & (TMXLayerAttribGzip | TMXLayerAttribZlib) )
        {
            unsigned char *deflated;
            CCSize s = layer->m_tLayerSize;
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
            
            layer->m_pTiles = (unsigned int*) deflated;
        }
        else
        {
            layer->m_pTiles = (unsigned int*) buffer;
        }
        
        this->setCurrentString("");
        
    }
    else if (elementName == "map")
    {
        // The map element has ended
        m_pMapInfo->setParentElement(TMXPropertyNone);
    }
    else if (elementName == "layer")
    {
        // The layer element has ended
        m_pMapInfo->setParentElement(TMXPropertyNone);
    }
    else if (elementName == "objectgroup")
    {
        // The objectgroup element has ended
        m_pMapInfo->setParentElement(TMXPropertyNone);
    }
    else if (elementName == "object")
    {
        // The object element has ended
        m_pMapInfo->setParentElement(TMXPropertyNone);
    }
}

void CCISOXMLParser::textHandler(void *ctx, const char *ch, int len)
{
    CC_UNUSED_PARAM(ctx);
    std::string pText((char*)ch,0,len);
    
    if (m_pMapInfo->getStoringCharacters())
    {
        std::string currentString = this->getCurrentString();
        currentString += pText;
        this->setCurrentString(currentString.c_str());
    }
}

CCISOMapInfo* CCISOXMLParser::getMapInfo()
{
    return m_pMapInfo;
}


NS_CC_END
