#include "httpRequest\HttpRequestTest.h"

USING_NS_CC;
using namespace cocos2d::network;

#define winsize Director::getInstance()->getVisibleSize()


Scene* HttpRequestTest::createScene()
{
	auto scene = Scene::create();
	auto layer = HttpRequestTest::create();

	scene->addChild(layer);

	return scene;
}

bool HttpRequestTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	httpRequest();
	htttpRequestJson();
	httpRequestImage();

	return true;
}


//////////////////////////////////////////////////////////////////////////
//Test1 - Call HttpRequest
//////////////////////////////////////////////////////////////////////////

void HttpRequestTest::httpRequest()
{
	auto httpRequest = new HttpRequest();
	httpRequest->setUrl("http://localhost/cocos2dx/demo.html");
	httpRequest->setRequestType(HttpRequest::Type::GET);
	httpRequest->setResponseCallback(this, httpresponse_selector(HttpRequestTest::callback));

	HttpClient::getInstance()->send(httpRequest);
}

void HttpRequestTest::callback(HttpClient* pSender, HttpResponse* response)
{
	std::vector<char> *data = response->getResponseData();
	std::string result(data->begin(), data->end());
	log("%s ", result.c_str());

}

//////////////////////////////////////////////////////////////////////////
// Test2- Using HttpRequest get Json data and parser json data
//////////////////////////////////////////////////////////////////////////

void HttpRequestTest::htttpRequestJson()
{
	HttpRequest* request = new HttpRequest();
	request->setUrl("http://localhost/cocos2dx/hightScore.json");
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(HttpRequestTest::httpResponseJson, this));
	request->setTag("json");
	HttpClient::getInstance()->send(request);
	request->release();

	/*
	HttpRequest* request1 = new HttpRequest();
	request1->setUrl("http://api.map.baidu.com/telematics/v3/weather?location=%E5%8C%97%E4%BA%AC&output=json&ak=Gk0Bbh9H4iREjesugyEqySN7");
	request1->setRequestType(HttpRequest::Type::GET);
	request1->setResponseCallback(CC_CALLBACK_2(HttpRequestTest::httpResponseJson, this));
	request1->setTag("json1");
	HttpClient::getInstance()->send(request1);
	request1->release();
	*/

}


void HttpRequestTest::httpResponseJson(HttpClient* client, HttpResponse* response)
{
	///////////////////////////////////
	// Parser Json 中国
	///////////////////////////////////
	
	/*
	if (!response)
	{
		return;
	}

	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed ", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};

	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	log("response code: %ld", statusCode);

	if (!response->isSucceed()) {
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;

	}

	std::vector<char>* buffer = response->getResponseData();
	printf("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++) {
		printf("%c", (*buffer)[i]);
	}
  
	std::string backStr = std::string(&(*buffer->begin()), buffer->size());
	std::string anotherStr;
	anotherStr.insert(anotherStr.begin(), buffer->begin(), buffer->end());
	printf("%s\n", backStr.c_str());
	printf("%s\n", anotherStr.c_str());
	printf("\n");


	if (strcmp(response->getHttpRequest()->getTag(), "json1") == 0) {
		rapidjson::Document doc;
		doc.Parse<0>(backStr.c_str());
		const rapidjson::Value& v = doc["status"];
		printf("status is : %s", v.GetString());
		const rapidjson::Value& dir = doc["results"];
		if (dir.IsArray()) {
			unsigned int i = 0;
			const rapidjson::Value& city = dir[i]["currentCity"];
			log("city is %s", city.GetString());
			const rapidjson::Value& title = doc["results"][(unsigned int)0]["index"][(unsigned int)2]["title"];
			log("the title is %s", title.GetString());
		}
	}

	*/

	///////////////////////////////////
	// Parser Json HightScore
	//////////////////////////////////

	std::vector<char> *data = response->getResponseData();
	std::string result(data->begin(), data->end());
	if (strcmp(response->getHttpRequest()->getTag() , "json") == 0)
	{
		rapidjson::Document document;
		document.Parse<0>(result.c_str());

		if (document.IsArray())
		{

			rapidjson::SizeType size = document.Size();

			Vec2 pos = Vec2(100, 100);

			for (rapidjson::SizeType  i = 0; i < size ; i++)
			{
				const rapidjson::Value& name = document[i]["player_name"]; // string
				const rapidjson::Value& score = document[i]["score"]; // string
				const rapidjson::Value& pos = document[i]["position"]; // int
				const rapidjson::Value& id = document[i]["player_id"]; // string

				// Convert int to string
				std::stringstream pos1;
				pos1 << "" << pos.GetInt();

				std::stringstream str;
				str << "Namne: " << name.GetString() << " & pos: " << pos1.str();
				showText(str.str(), i);
			}
		}
	}

}


void HttpRequestTest::showText(std::string str , int i)
{
	auto label = Label::create("" , "Arial" , 20);
	label->setString(str);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(Vec2(winsize.width / 2 , winsize.height - label->getContentSize().height / 2 - 10 - 20*i));

	this->addChild(label);
}


//////////////////////////////////////////////////////////////////////////
//Test3 - Using HttpRequest get Image Data
//////////////////////////////////////////////////////////////////////////

void HttpRequestTest::httpRequestImage()
{
	HttpRequest* request = new HttpRequest();
	request->setUrl("http://localhost/cocos2dx/HelloWorld.png");

	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(HttpRequestTest::httpResponseImage, this));

	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpRequestTest::httpResponseImage(HttpClient* client, HttpResponse* response)
{
	if (!response)
	{
		return;
	}

	if (!response->isSucceed())
	{
		log("response failed");
		return;
	}

	std::vector<char>* data = response->getResponseData();

	Image* image = new Image();

	image->initWithImageData(reinterpret_cast<unsigned char*>(&(data->front())), data->size());

	Texture2D* texture = new Texture2D();
	texture->initWithImage(image);
	Sprite* sprite = Sprite::createWithTexture(texture);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	sprite->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));


	addChild(sprite);

}
