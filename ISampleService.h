#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <utils/RefBase.h>
#include <utils/Errors.h>
#include <stdint.h>
#include <sys/types.h>
#include <utils/String8.h>

namespace android {

class ISampleService : public IInterface {
public:
    DECLARE_META_INTERFACE(SampleService);
    
    //declear interface funs
   virtual int sayHello(const String8& clientName) = 0;
    //declear interface funs
   virtual int sayHelloAsync(const String8& clientName) = 0;
};


class BnSampleService : public BnInterface<ISampleService> {
public:
    enum {
        SAY_HELLO = IBinder::FIRST_CALL_TRANSACTION,
        SAY_HELLO_ASYNC,
    };

    virtual status_t onTransact(uint32_t code, const Parcel& data,
            Parcel* reply, uint32_t flags = 0);
};

};
