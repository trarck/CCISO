#include "CCMessageManager.h"
#include "CCMessageTarget.h"

NS_CC_BEGIN


void CCMessageTarget::registerMessage(MessageType type,SEL_MessageHandler handle , CCObject* sender)
{
    CCMessageManager::defaultManager()->registerReceiver(this,handle,type,sender);
}

void CCMessageTarget::unregisterMessage(MessageType type ,SEL_MessageHandler handle ,CCObject* sender)
{
    CCMessageManager::defaultManager()->removeReceiver(this,type,sender,handle);
}

void CCMessageTarget::sendMessage(MessageType type ,CCObject* receiver ,CCObject* data)
{
    CCMessageManager::defaultManager()->dispatchMessageWithType(type,this,receiver,data);
}

void CCMessageTarget::sendMessage(MessageType type ,CCObject* receiver)
{
    CCMessageManager::defaultManager()->dispatchMessageWithType(type,this,receiver);
}

void CCMessageTarget::cleanupMessages()
{
    CCMessageManager::defaultManager()->removeReceiver(this);
}

NS_CC_END
