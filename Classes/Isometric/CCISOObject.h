#ifndef ISO_CCISOObject_H_
#define ISO_CCISOObject_H_

#include "cocos2d.h"

NS_CC_BEGIN

class CCISOObject : public CCObject{

public:
    
    CCISOObject();   
  
    ~CCISOObject();
   
public:
    
    virtual void setName(const char *pName);
    virtual std::string& getName();
    virtual void setType(const char *pType);
    virtual std::string& getType();
    virtual void setPosition(CCPoint tPosition);
    virtual CCPoint getPosition();
    virtual void setSize(CCSize tSize);
    virtual CCSize getSize();
    virtual void setGid(unsigned int uGid);
    virtual unsigned int getGid();
    virtual void setVisible(bool bVisible);
    virtual bool getVisible();
    
    virtual void setProperties(CCDictionary* pProperties);
    virtual CCDictionary* getProperties();
    
protected:
    
    std::string m_sName;
    std::string m_sType;
    CCPoint m_tPosition;
    CCSize m_tSize;
    unsigned int m_uGid;
    bool m_bVisible;

    /**
     * 属性
     */
    CCDictionary* m_pProperties;
};


NS_CC_END

#endif //ISO_CCISOObject_H_
