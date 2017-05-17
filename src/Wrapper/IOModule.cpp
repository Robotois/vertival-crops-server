#include <node.h>
#include "IOModuleWrapper.h"

using namespace v8;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  IOModuleWrapper::NewInstance(args);
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  IOModuleWrapper::Init();
  NODE_SET_METHOD(module,"exports",CreateObject);
}

NODE_MODULE(IOModule, InitAll)
