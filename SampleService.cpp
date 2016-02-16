#include "ISampleService.h"
#include <utils/RefBase.h>
#include <utils/Errors.h>

#include <binder/IInterface.h>
#if defined(HAVE_PTHREADS)
#include <sys/resource.h>
#endif
#include <stdint.h>
#include <sys/types.h>
#include <cutils/sched_policy.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/log.h>
#include <utils/threads.h>


namespace android{

class SampleService : public BnSampleService {
public:
    SampleService(){}
    //service interface
    int sayHello(const String8& clientName);
    int sayHelloAsync(const String8& clientName);

};

int SampleService::sayHello(const String8& clientName){
    ALOGD("Hello %s",clientName.string());
    return 1;
}

int SampleService::sayHelloAsync(const String8& clientName){
    ALOGD("Async Hello to %s",clientName.string());
    return 0;
}


};

using namespace android;
int main(int argc, char** argv) {

    //set debug flag
    ProcessState::self()->setThreadPoolMaxThreadCount(999);
    IPCThreadState::self()->bDebug = true;

    //Just set as surfaceflinger, we will check it later.
    ProcessState::self()->setThreadPoolMaxThreadCount(4);

    sp<SampleService> samplesrv = new SampleService();

#if defined(HAVE_PTHREADS)
    setpriority(PRIO_PROCESS, 0, PRIORITY_URGENT_DISPLAY);
#endif
    set_sched_policy(0, SP_FOREGROUND);

    // publish SampleService
    sp<IServiceManager> sm(defaultServiceManager());    
    sm->addService(String16("SampleService"), samplesrv, false);

    IPCThreadState::self()->joinThreadPool();
    return 0;
}


