#include <node.h>
#include "IOModuleWrapper.h"
#include <string>

using namespace v8;

Persistent<Function> IOModuleWrapper::constructor;

IOModuleWrapper::IOModuleWrapper(uint8_t _add){
  io = new IOModule(_add);
}

IOModuleWrapper::~IOModuleWrapper(){
}

void IOModuleWrapper::release(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  IOModuleWrapper* temp_obj = ObjectWrap::Unwrap<IOModuleWrapper>(args.Holder());
  temp_obj->io->release();
  delete temp_obj->io;
}

void IOModuleWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"IOModuleWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"readSensor1", readSensor1);
  NODE_SET_PROTOTYPE_METHOD(tpl,"readSensor2", readSensor2);
  NODE_SET_PROTOTYPE_METHOD(tpl,"setMotor1", setMotor1);
  NODE_SET_PROTOTYPE_METHOD(tpl,"setMotor2", setMotor2);
  NODE_SET_PROTOTYPE_METHOD(tpl,"release", release);

  constructor.Reset(isolate,tpl->GetFunction());
}

void IOModuleWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _add = 0x00;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  IOModuleWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 0:
        obj = new IOModuleWrapper();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      case 1:
        _add = (uint8_t) args[0]->NumberValue();
        obj = new IOModuleWrapper(_add);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      default:
        isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    if(_argc > 1){
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments...")));
    }
    Local<Value>* argv = new Local<Value>[_argc];
    for(uint8_t i = 0; i < _argc; i++){
      argv[i] = args[i];
    }
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(_argc, argv));
  }
}

void IOModuleWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // printf("Args Count: %d\n",_argc);
  if(_argc > 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }
  Handle<Value>* argv = new Handle<Value>[_argc];
  for(uint8_t i = 0; i < _argc; i++){
    argv[i] = args[i];
  }
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(_argc, argv);

  args.GetReturnValue().Set(instance);
}

void IOModuleWrapper::readSensor1(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() > 0){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  IOModuleWrapper* temp_obj = ObjectWrap::Unwrap<IOModuleWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->io->readSensor1()));
}

void IOModuleWrapper::readSensor2(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);


  IOModuleWrapper* temp_obj = ObjectWrap::Unwrap<IOModuleWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->io->readSensor2()));
}

void IOModuleWrapper::setMotor1(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  uint8_t motorState = (uint8_t) args[0]->NumberValue();

  IOModuleWrapper* temp_obj = ObjectWrap::Unwrap<IOModuleWrapper>(args.Holder());

    temp_obj->io->setMotor1(motorState);
}

void IOModuleWrapper::setMotor2(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  if(args.Length() != 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "Wrong arguments...")));
  }

  uint8_t motorState = (uint8_t) args[0]->NumberValue();
  
  IOModuleWrapper* temp_obj = ObjectWrap::Unwrap<IOModuleWrapper>(args.Holder());

    temp_obj->io->setMotor2(motorState);
  //  args.GetReturnValue().Set(Number::New(isolate,temp_obj->io->setMotor2(motorState)));
}
