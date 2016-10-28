#pragma once
#include <string>
using namespace std;
#ifdef __ANDROID__
#include "Types.h"
#include <vector>
#include <jni.h>
class AndroidPlatform
{
public:
	void WeiXinPay(string consumerId, string consumerkey,string order,string url,float money);
	void ZhiFuBaoPay(string order,string url,float money);
	int GetLocalAddr();
	void installApk(string file);
	string GetMachineID();
	string GetPackegPath();
	void loadsoFile();
private:
};
class Platform :public AndroidPlatform
{
public:
	Platform(void);
	~Platform(void);
	
};
#elif WIN32

class Platform
{
public:
	Platform(void){};
	~Platform(void){};
	void WeiXinPay(string consumerId, string consumerkey,string order,string url,float money){return;}
	void ZhiFuBaoPay(string order,string url,float money){return;}
	int GetLocalAddr(){return 0;}
	string GetMachineID(){return "";}
	string GetPackegPath(){return "";}
};
#elif CC_TARGET_OS_IPHONE
#include "IOSPlatform.hpp"
class Platform :public IOSPlatform
{
public:
    Platform(void){};
    ~Platform(void){};
    
   
    string GetMachineID(){return "";}
    string GetPackegPath(){return "";}
};
#endif


