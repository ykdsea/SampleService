#include "ISampleService.h"
#include <utils/RefBase.h>
#include <utils/Errors.h>
#include <stdint.h>
#include <sys/types.h>
#include <binder/IServiceManager.h>
#include <cutils/log.h>
#include <utils/threads.h>
#include <binder/IPCThreadState.h>


using namespace android;

static bool deathCalled  = false;
class DeathCallBack : public IBinder::DeathRecipient {
public:
    virtual void binderDied(const wp<IBinder>& who) {
        ALOGE("SampleService remote died");
        deathCalled  = true;
    }
};


int main(int argc, char** argv) {
    ProcessState::self()->setThreadPoolMaxThreadCount(999);
    IPCThreadState::self()->bDebug = true;

    
    sp<ISampleService> sampleSrv;
    sp<ISampleService> sampleSrv2;

    ALOGE("****test BpBinder onFirstsRef****");

    if(getService(String16("SampleService"), &sampleSrv) != NO_ERROR){
        ALOGE("get SampleService fail");
        return 0;
    }

    if(getService(String16("SampleService"), &sampleSrv2) != NO_ERROR){
        ALOGE("get SampleService fail");
        return 0;
    }

    ALOGE("****test BpBinder onLastStrongRef****");
    sampleSrv = NULL;
    sampleSrv2= NULL;


    ALOGE("regitster death callback");
    sp<DeathCallBack> deathCb(new DeathCallBack());
    sampleSrv->asBinder()->linkToDeath(deathCb);

    
    ALOGE("To re-get SampleService");
    if(getService(String16("SampleService"), &sampleSrv) != NO_ERROR){
        ALOGE("get SampleService fail");
        return 0;
    }
    ALOGE("*** call sayHello()***");
    sampleSrv->sayHello(String8("SampleClient"));

    ALOGE("*** call sayHelloAsync()***");
    sampleSrv->sayHelloAsync(String8("SampleClient"));

#if 0
    do{
        sleep(2);
        if(deathCalled){
            ALOGE("death callback called\n");
            break;
        }
    }while(1);
 #else
    IPCThreadState::self()->joinThreadPool(true);
 #endif
       return 1;
}


