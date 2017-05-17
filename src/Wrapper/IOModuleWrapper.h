#ifndef IOMOULEWRAPPER_H
#define IOMOULEWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../Modules/IOModule.h"

class IOModuleWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit IOModuleWrapper(uint8_t _add = 0x04);
  ~IOModuleWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void readSensor1(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void readSensor2(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setMotor1(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void setMotor2(const v8::FunctionCallbackInfo<v8::Value>& args);

  static void release(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  IOModule *io;
};

#endif
