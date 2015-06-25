#ifndef _HTTPREQUESTTEST_H_
#define _HTTPREQUESTTEST_H_

#include "cocos2d.h"
#include "network\HttpRequest.h"
#include "network\HttpClient.h"
#include "json\document.h"

#include "json\rapidjson.h"

USING_NS_CC;
using namespace cocos2d::network;

class HttpRequestTest : public cocos2d::Layer
{
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HttpRequestTest);


	void httpRequest();
	virtual void callback(HttpClient* pSender , HttpResponse* response );

	void htttpRequestJson();
	void httpResponseJson(HttpClient* pSender, HttpResponse* response );

	void httpRequestImage();
	void httpResponseImage(HttpClient* client , HttpResponse* response);

	void showText(std::string st , int i);


private:

};

#endif /* _HTTPREQUESTTEST_H_ */