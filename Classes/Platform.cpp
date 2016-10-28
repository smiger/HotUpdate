
#include "Platform.h"

#ifdef __ANDROID__
#include<android/log.h>
#include "platform/android/jni/JniHelper.h"
#include "platform/CCPlatformMacros.h"
USING_NS_CC;

jstring stoJstring( JNIEnv* env, const char* pat )
{
	
	jclass strClass = (env)->FindClass("java/lang/String");
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = (env)->NewByteArray(strlen(pat));
	(env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	jstring encoding = (env)->NewStringUTF("GB2312");
	return (jstring)(env)->NewObject(strClass, ctorID, bytes, encoding);
}
char* jstringTostring(JNIEnv* env, jstring jstr)
{
       char* rtn = NULL;
       jclass clsstring = env->FindClass("java/lang/String");
       jstring strencode = env->NewStringUTF("utf-8");
       jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
       jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
       jsize alen = env->GetArrayLength(barr);
       jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
       if (alen > 0)
       {
                 rtn = (char*)malloc(alen + 1);
                 memcpy(rtn, ba, alen);
                 rtn[alen] = 0;
       }
       env->ReleaseByteArrayElements(barr, ba, 0);
       return rtn;
}
JNIEnv* GetJavaEnv(JavaVM* pJavaVM)
{
    JNIEnv* pEnv = 0;
    if (pJavaVM)
    {
        if (pJavaVM->GetEnv((void**)&pEnv, JNI_VERSION_1_4) != JNI_OK)
        {
            return 0;
        }
        
        if (pJavaVM->AttachCurrentThread(&pEnv, 0) < 0)
        {
            return 0;
        }
        
        return pEnv;
    }
    return 0;
}



Platform::Platform(void)
{
}


Platform::~Platform(void)
{
}
void AndroidPlatform::WeiXinPay(string consumerId, string consumerkey,string order,string url,float money)
{
	JniMethodInfo Info;
	
	if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","Pay","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;FI)V"))
	{
		jstring  id=stoJstring(Info.env,consumerId.c_str());
		jstring  key=stoJstring(Info.env,consumerkey.c_str());
		jstring  order_=stoJstring(Info.env,order.c_str());
		jstring  url_=stoJstring(Info.env,url.c_str());
		jfloat  pay=money*100;
		jint channel=0;
		Info.env->CallStaticVoidMethod(Info.classID, Info.methodID,id,key,order_,url_,pay,channel);
	}
}

void AndroidPlatform::ZhiFuBaoPay(string order,string url,float money)
{
	JniMethodInfo Info;
	
	//if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","Pay","(Ljava/lang/String;Ljava/lang/String;FI)V"))
	if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","Pay","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;FI)V"))
	{
		jstring  id=stoJstring(Info.env,"");
		jstring  key=stoJstring(Info.env,"");
		jstring  order_=stoJstring(Info.env,order.c_str());
		jstring  url_=stoJstring(Info.env,url.c_str());
		jfloat  pay=money;
		jint channel=1;
		//Info.env->CallStaticObjectMethod(Info.classID, Info.methodID,order_,url_,pay,channel);
		Info.env->CallStaticVoidMethod(Info.classID, Info.methodID,id,key,order_,url_,pay,channel);
	}
}
int AndroidPlatform::GetLocalAddr()
{
	JniMethodInfo Info;
	
	if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","getLocalIpAddress","()I"))
	{
		
		 jint iret=(jint)Info.env->CallStaticIntMethod(Info.classID, Info.methodID);
		 return iret;
	}
	return 0;
}
string AndroidPlatform::GetMachineID()
{
	JniMethodInfo Info;
	
	if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","GetMachineID","()Ljava/lang/String;"))
	{
		
		 jstring iret=(jstring)Info.env->CallStaticObjectMethod(Info.classID, Info.methodID);
		 return jstringTostring(Info.env,iret);
	}
	return "";
}
void AndroidPlatform::installApk(string file)
{
	JniMethodInfo Info;
	
	if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","installApk","(Ljava/lang/String;)V"))
	{
		jstring  jfile=stoJstring(Info.env,file.c_str());
		Info.env->CallStaticVoidMethod(Info.classID, Info.methodID,jfile);
		return;
	}
}
string AndroidPlatform::GetPackegPath()
{
	JniMethodInfo Info;
	
	if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","GetApkPath","()Ljava/lang/String;"))
	{
		
		 jstring path=(jstring)Info.env->CallStaticObjectMethod(Info.classID, Info.methodID);
		 return jstringTostring(Info.env,path);
	}
	return "";
}
void AndroidPlatform::loadsoFile()
{
	JniMethodInfo Info;

	if(JniHelper::getStaticMethodInfo(Info,"org/cocos2dx/cpp/AppActivity","load","()V"))
	{
		Info.env->CallStaticVoidMethod(Info.classID, Info.methodID);
		return;
	}
}
#elif CC_TARGET_OS_IPHONE

#endif
