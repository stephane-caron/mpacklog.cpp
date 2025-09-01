// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron
/*
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *     CircularBuffer class of mc_rtc
 *     Copyright 2012-2019 CNRS-UM LIRMM, CNRS-AIST JRL
 *     License: BSD-2-Clause (see licenses/LICENSE-mc_rtc)
 */

#pragma once

#include <spdlog/spdlog.h>

#include <atomic>

namespace mpacklog {

/*! Lock-free, thread-safe, single-producer single-consumer circular buffer.
 *
 * Loosely based off the article:
 * https://www.codeproject.com/Articles/43510/Lock-Free-Single-Producer-Single-Consumer-Circular
 */
template <typename T, size_t Size>
struct CircularBuffer {
 public:
  enum { Capacity = Size + 1 };

  //! Initialize buffer.
  CircularBuffer() : head_(0), tail_(0) {
    if (!tail_.is_lock_free()) {
      spdlog::warn(
          "Your platform does not support std::atomic_size_t as lock-free "
          "operations");
    }
  }

  /*! Push data to the buffer.
   *
   * \param[in] item New item to push.
   *
   * \return True if the item was pushed, false if the buffer is full.
   */
  bool push(const T& item) {
    size_t tail = tail_;
    auto next_tail = increment(tail);
    if (next_tail != head_) {
      data_[tail] = item;
      tail_ = next_tail;
      return true;
    }
    return false;
  }

  /*! Pop next item from the buffer.
   *
   * \param[out] item Popped item will be written there.
   *
   * \return True if an item was popped, false if the buffer is empty.
   */
  bool pop(T& item) {
    const size_t head = head_;
    if (head == tail_) {
      return false;
    }
    item = data_[head];
    head_ = increment(head);
    return true;
  }

  //! Check whether the buffer is empty.
  bool empty() const { return head_ == tail_; }

  //! Number of items in the buffer.
  size_t size() const { return (tail_ + Capacity - head_) % Capacity; }

 private:
  /*! Get next index in the circular buffer.
   *
   * \param idx Start index.
   *
   * \return Next index, either (idx + 1) or zero.
   */
  size_t increment(size_t idx) const { return (idx + 1) % Capacity; }

  //! Internal data
  T data_[Capacity];

  //! Index of current buffer head
  std::atomic_size_t head_;

  //! Index of current buffer tail
  std::atomic_size_t tail_;
};

}  // namespace mpacklog
