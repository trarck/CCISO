#ifndef __CCMessage_Target_H__
#define __CCMessage_Target_H__

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"

NS_CC_BEGIN

class CCMessageTarget : public CCObject {
public:
    
  
    //message operate
    virtual void registerMessage(MessageType type,SEL_MessageHandler handle , CCObject* sender);
    virtual void unregisterMessage(MessageType type ,SEL_MessageHandler handle ,CCObject* sender);
    virtual void sendMessage(MessageType type ,CCObject* receiver ,CCObject* data);
    virtual void sendMessage(MessageType type ,CCObject* receiver);
	virtual void cleanupMessages();

    
    
protected:

};

NS_CC_END


#endif //__CCMessage_Target_H__
