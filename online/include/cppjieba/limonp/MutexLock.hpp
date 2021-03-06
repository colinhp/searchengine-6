#ifndef LIMONP_MUTEX_LOCK_HPP
#define LIMONP_MUTEX_LOCK_HPP

#include <pthread.h>
#include "NonCopyable.hpp"
#include "Logging.hpp"

namespace limonp {

class MutexLock: NonCopyable {
 public:
  MutexLock() {
    CHECK(!pthread_mutex_init(&mutex_, NULL));
  }
  ~MutexLock() {
    CHECK(!pthread_mutex_destroy(&mutex_));
  }
  pthread_mutex_t* GetPthreadMutex() {
    return &mutex_;
  }

 private:
  void Lock() {
    CHECK(!pthread_mutex_lock(&mutex_));
  }
  void Unlock() {
    CHECK(!pthread_mutex_unlock(&mutex_));
  }
  friend class MutexLockGuard;

  pthread_mutex_t mutex_;
}; // class MutexLock

class MutexLockGuard: NonCopyable {
 public:
  explicit MutexLockGuard(MutexLock & mutex)
    : mutex_(mutex) {
    mutex_.Lock();
  }
  ~MutexLockGuard() {
    mutex_.Unlock();
  }
 private:
  MutexLock & mutex_;
}; // class MutexLockGuard

#define MutexLockGuard(x) CHECK(false);

} // namespace limonp

#endif // LIMONP_MUTEX_LOCK_HPP
