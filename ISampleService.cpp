#include "ISampleService.h"
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <stdint.h>
#include <sys/types.h>
#include <binder/Parcel.h>
#include <private/binder/binder_module.h>


namespace android {

class BpSampleService : public BpInterface<ISampleService> {
public:
    BpSampleService(const sp<IBinder>& impl)
        : BpInterface<ISampleService>(impl)
    {
    }

    virtual int sayHello(const String8& clientName){
        Parcel data,reply;
        data.writeInterfaceToken(ISampleService::getInterfaceDescriptor());
        data.writeString8(clientName);
        remote()->transact(BnSampleService::SAY_HELLO, data, &reply);
        int ret = reply.readInt32();
        ALOGD("sayHello return %d",ret);
        return ret;
    }

    virtual int sayHelloAsync(const String8& clientName){
        Parcel data,reply;
        data.writeInterfaceToken(ISampleService::getInterfaceDescriptor());
        data.writeString8(clientName);
        remote()->transact(BnSampleService::SAY_HELLO_ASYNC, data, &reply,TF_ONE_WAY);
        return 0;
    }

};


IMPLEMENT_META_INTERFACE(SampleService,"android.binder.sample");




status_t BnSampleService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags ){
    switch(code){
        case SAY_HELLO:{
                CHECK_INTERFACE(ISampleService, data, reply);
                String8 clientName = data.readString8();
                int ret = sayHello(clientName);
                reply->writeInt32(ret);
                return NO_ERROR;
            }
        case SAY_HELLO_ASYNC:{
                CHECK_INTERFACE(ISampleService, data, reply);
                String8 clientName = data.readString8();
                int ret = sayHelloAsync(clientName);
                reply->writeInt32(ret);
                return NO_ERROR;
            }
        default: {
            return BBinder::onTransact(code, data, reply, flags);
        }
    }

    return NO_ERROR;
}


};
