#include "AppDelegate.h"
#include "TitleScene.h"
#include "HomeScene.hpp"
#include "UserData.hpp"
#include "dbIO.hpp"
#include <fstream>
#include <iostream>

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size smallResolutionSize = cocos2d::Size(640, 1136);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() :_home_scene(nullptr){

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("NeCollection", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("NeCollection");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);
    Size frameSize = glview->getFrameSize();
    
    /*
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
     */

    register_all_packages();
    
    if(!UserDefault::getInstance()->getBoolForKey("haveEverLaunched")){
        if(!initGame())return false;
    }
    
    FileUtils::getInstance()->addSearchPath("res/");
    auto scene = TitleScene::createScene();
    dynamic_cast<TitleScene*>(TitleScene::_titlescene)->beginAnimation();

    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    
    auto* running_scene = Director::getInstance()->getRunningScene()->getChildren().at(1);
    if(running_scene->getName() == "HomeScene"){
        dynamic_cast<HomeScene*>(running_scene)->saveScheduleTime();
    }
    
    Director::getInstance()->stopAnimation();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::launchGame(){
    auto scene = HomeScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    
    auto* running_scene = Director::getInstance()->getRunningScene()->getChildren().at(1);
    if(running_scene->getName() == "HomeScene"){
        dynamic_cast<HomeScene*>(running_scene)->refreshScene();
    }
    
    Director::getInstance()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

bool AppDelegate::initGame(){
    auto* tiny_data = UserDefault::getInstance();
    auto* db = dbIO::getInstance();
    std::string filepath = cocos2d::FileUtils::getInstance()->getWritablePath();
    std::time_t timer;
    struct std::tm *t_st;
    
    std::time(&timer);
    t_st = localtime(&timer);
    int _time = t_st->tm_sec + t_st->tm_min * 60 + t_st->tm_hour * 3600;
    
    tiny_data->setIntegerForKey("previous_time", _time);
    tiny_data->setIntegerForKey("time", 500);
    
    tiny_data->setBoolForKey("isCommingToy",false);
    tiny_data->setBoolForKey("isCommingMeal",false);
    tiny_data->setBoolForKey("isCommingFuton",false);
    tiny_data->setBoolForKey("isCommingTrimmer",false);
    
    std::array< CatObjectStatus,4 > data;
    for(auto&& obj: data)obj.isComing=false;
    data[static_cast<int>(PRODUCTS::MEAL)].id = 0; data[static_cast<int>(PRODUCTS::TOY)].id = 2;
    data[static_cast<int>(PRODUCTS::FUTON)].id = 3; data[static_cast<int>(PRODUCTS::TRIMMER)].id = 4;
    
    cocos2d::Data cos;
    cos.copy(reinterpret_cast<unsigned char*>(&data[0]), sizeof(CatObjectStatus)*4);
    tiny_data->setDataForKey("CatObjectStatuses", cos);
    
    /* initialize to debug  */
    db->queryTableWritable("drop table catbox");
    db->queryTableWritable("drop table productbox");
    db->queryTableWritable("drop table cat_isobtain");
    /* end debug code       */
    
    db->queryTableWritable("create table catbox(id integer primary key,date text,cat_id integer)");
    db->queryTableWritable("create table productbox(id integer primary key,isObtain integer);");
    db->queryTableWritable("create table cat_isobtain(id integer primary key,isObtain integer)");
    
    
    
    for(int i=0; i<NUMBER_OF_CATS; i++){
        db->queryTableWritable("insert into cat_isobtain values("+std::to_string(i)+",0)");
    }
    
    for(int i=0; i<NUMBER_OF_PRODUCTS; i++){
        db->queryTableWritable("insert into productbox values("+std::to_string(i)+",0)");
    }
    
    UserData::getInstance()->setMoney(500);
    
    /* add data to debug    */
    for(int i=0; i<NUMBER_OF_CATS; i++){
        UserData::getInstance()->addCats(i);
    }
    /* end debug code       */
    
    return true;
}
