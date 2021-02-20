#pragma once

#include <memory>
#include <chrono>
#include <map>
#include <mutex>
#include <condition_variable>

#include "blockid.hpp"

namespace smartdb {
  class lock_table {
  public:
    lock_table();
    void slock(std::shared_ptr<block_id> pBlockId);
    void xlock(std::shared_ptr<block_id> pBlockId);
    void unlock(std::shared_ptr<block_id> pBlockId);
    
  private:
    const int mMaxTime = 10000;
    std::map<std::shared_ptr<block_id>, int> mLocks;
    std::mutex mMutex;
    std::condition_variable mCondVar;

    bool has_xlock(std::shared_ptr<block_id> pBlockId);
    bool has_other_slocks(std::shared_ptr<block_id> pBlockId);
    bool waiting_too_long(std::chrono::time_point<std::chrono::high_resolution_clock> pStartTime);
    int get_lock_val(std::shared_ptr<block_id>);
  };
}
