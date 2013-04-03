#ifndef ISO_CCISOXMLParser_H_
#define ISO_CCISOXMLParser_H_

#include "cocos2d.h"
#include "CCISOTileMap.h"

NS_CC_BEGIN

class CCISOTileMap;

enum {
    ISOLayerAttribNone = 1 << 0,
    ISOLayerAttribBase64 = 1 << 1,
    ISOLayerAttribGzip = 1 << 2,
    ISOLayerAttribZlib = 1 << 3,
};

enum {
    ISOPropertyNone,
    ISOPropertyMap,
    ISOPropertyLayer,
    ISOPropertyObjectGroup,
    ISOPropertyObject,
    ISOPropertyTile,
    ISOPropertyImage
};

class CCISOXMLReader : public CCObject, public CCSAXDelegator
{

public:
    
    CCISOXMLReader();
    
    ~CCISOXMLReader();
    

    static CCISOXMLReader * formatWithXMLFile(const char *tmxFile);
    /** creates a TMX Format with an XML string and a TMX resource path */
    static CCISOXMLReader * formatWithXML(const char* tmxString, const char* resourcePath);
    /** initializes a TMX format with a  tmx file */
    bool initWithTMXFile(const char *tmxFile);
    /** initializes a TMX format with an XML string and a TMX resource path */
    bool initWithXML(const char* tmxString, const char* resourcePath);
    /** initializes parsing of an XML file, either a tmx (Map) file or tsx (Tileset) file */
    bool parseXMLFile(const char *xmlFilename);
    /* initializes parsing of an XML string, either a tmx (Map) string or tsx (Tileset) string */
    bool parseXMLString(const char *xmlString);
    

    
    // implement pure virtual methods of CCSAXDelegator
    void startElement(void *ctx, const char *name, const char **atts);
    void endElement(void *ctx, const char *name);
    void textHandler(void *ctx, const char *ch, int len);
    
    inline const char* getCurrentString(){ return m_sCurrentString.c_str(); }
    inline void setCurrentString(const char *currentString){ m_sCurrentString = currentString; }
    inline const char* getTMXFileName(){ return m_sTMXFileName.c_str(); }
    inline void setTMXFileName(const char *fileName){ m_sTMXFileName = fileName; }
    
    virtual CCISOTileMap* getMap();
    
private:
    void internalInit(const char* tmxFileName, const char* resourcePath);
    
    int m_nCurrentElement;
    
    unsigned int m_uCurrentGid;
    
    int m_nLayerAttribs;
    
    bool m_bStoringCharacters;
    
protected:
    //! tmx filename
    std::string m_sTMXFileName;
    // tmx resource path
    std::string m_sResources;
    //! current string
    std::string m_sCurrentString;
    //! tile properties
//    CCDictionary* m_pTileProperties;

    CCISOTileMap* m_pMap;	
};


NS_CC_END

#endif //ISO_CCISOXMLParser_H_
