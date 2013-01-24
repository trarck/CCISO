#include "CCISOCoordinate.h"
#include "CCISOTileLayer.h"

NS_CC_BEGIN

CCISOTileLayer::CCISOTileLayer()
:m_iStartX(0)
,m_iStartY(0)
,m_tLayerSize(CCSizeZero)
,m_tMapTileSize(CCSizeZero)
,m_pProperties(NULL)
,m_sLayerName("")
{
	
}

CCISOTileLayer::~CCISOTileLayer()
{
    CC_SAFE_RELEASE(m_pProperties);
}

bool CCISOTileLayer::init()
{
	m_tOffset=CCPointZero;   
	return true;
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


void CCISOTileLayer::releaseMap()
{
    CCLOG("CCISOTileLayer::releaseMap");

}

void CCISOTileLayer::setupTiles()
{
    CCLOG("CCISOTileLayer::setupTiles");
}

/**
 * 获取tile
 */
CCSprite* CCISOTileLayer::tileAt(float x,float y)
{
    CCLOG("CCISOTileLayer::tileAt");
    return NULL;
}


CCSprite* CCISOTileLayer::tileAt(const CCPoint& tileCoordinate)
{
    CCLOG("CCISOTileLayer::tileAt");
    return NULL;
}

void CCISOTileLayer::removeTileAt(float x,float y)
{
    CCLOG("CCISOTileLayer::removeTileAt");
}

void CCISOTileLayer::removeTileAt(const CCPoint& pos)
{
    CCLOG("CCISOTileLayer::removeTileAt");
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
NS_CC_END
