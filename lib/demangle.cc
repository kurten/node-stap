// Copyright (c) 2015 Uber Technologies, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include <node.h>
#include <cstdlib>
#include <cxxabi.h>

using namespace v8;

void demangle(const FunctionCallbackInfo<Value> &args) {
    Isolate *isolate = args.GetIsolate();

    String::Utf8Value mangledStr(args[0]->ToString(isolate));

    int status;
    char * demangled = abi::__cxa_demangle(*mangledStr, NULL, NULL, & status);

    if (demangled) {
         args.GetReturnValue().Set(String::NewFromUtf8(isolate, demangled));
    } else {
         args.GetReturnValue().Set(args[0]);
    }
}

void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "demangle", demangle);
}

NODE_MODULE(demangle, init)
