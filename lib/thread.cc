// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
#include "thread.h"

#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

namespace rgb_matrix {
void *Thread::PthreadCallRun(void *tobject) {
  reinterpret_cast<Thread*>(tobject)->Run();
  return NULL;
}

Thread::Thread() : started_(false) {}
Thread::~Thread() {
  WaitStopped();
}

void Thread::WaitStopped() {
  if (!started_) return;
  int result = pthread_join(thread_, NULL);
  if (result != 0) {
    fprintf(stderr, "err code: %d %s\n", result, strerror(result));
  }
  started_ = false;
}

void Thread::Start(int priority) {
  assert(!started_);
  pthread_create(&thread_, NULL, &PthreadCallRun, this);

  if (priority > 0) {
    struct sched_param p;
    p.sched_priority = priority;
    pthread_setschedparam(thread_, SCHED_FIFO, &p);
  }

  started_ = true;
}

}  // namespace rgb_matrix
