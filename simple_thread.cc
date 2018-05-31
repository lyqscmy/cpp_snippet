// ©2013 Cameron Desrochers

#include "simple_thread.h"

#include <thread>

struct SimpleThread::ThreadRef {
  std::thread thread;

  static void threadProc(ThreadRef *threadRef) {
    threadRef->callbackFunc(threadRef->callbackObj);
  }

  ThreadRef(void *callbackObj, CallbackFunc callbackFunc)
      : callbackObj(callbackObj), callbackFunc(callbackFunc) {}

  void *callbackObj;
  CallbackFunc callbackFunc;
};

void SimpleThread::startThread(void *callbackObj, CallbackFunc callbackFunc) {
  thread = new ThreadRef(callbackObj, callbackFunc);
  thread->thread = std::thread(&ThreadRef::threadProc, thread);
}

void SimpleThread::join() {
  if (thread != nullptr && thread->thread.joinable()) {
    thread->thread.join();
  }
}

SimpleThread::~SimpleThread() {
  if (thread != nullptr) {
    join();
    delete thread;
  }
}
