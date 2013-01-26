#ifndef ISO_CCISOObjectLayer_H_
#define ISO_CCISOObjectLayer_H_

#include "cocos2d.h"
#include "cocoa/CCGeometry.h"
#include "cocoa/CCString.h"
#include "cocoa/CCArray.h"
#include "cocoa/CCDictionary.h"

NS_CC_BEGIN

/**
 * object layer
 * 只记录占有的数据
 */
class CCISOObjectLayer : public CCObject
{

public:

    CCISOObjectLayer();
    
    virtual ~CCISOObjectLayer();

    inline const char* getName(){ return m_sName.c_str(); }
    inline void setName(const char *name){ m_sName = name; }

    /** return the value for the specific property name */
    CCString *propertyNamed(const char* propertyName);

    /** return the dictionary for the specific object name.
    It will return the 1st object found on the array for the given name.
    */
    CCDictionary* objectNamed(const char *objectName);
    
    //============get set===========//
    virtual void setOffset(const CCPoint& tOffset);
    
    virtual const CCPoint& getOffset();
    
    virtual void setProperties(CCDictionary* pProperties);
    
    virtual CCDictionary* getProperties();
    
    virtual void setObjects(CCArray* pObjects);
    
    virtual CCArray* getObjects();
    
protected:    
    /** name of the group */
    std::string m_sName;
    
    CCPoint m_tOffset;
    
    CCDictionary* m_pProperties;
    
    CCArray* m_pObjects;

};

// end of tilemap_parallax_nodes group
/// @}

NS_CC_END

#endif //ISO_CCISOObjectLayer_H_