// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron
/*
 * This file incorporates work covered by the following copyright and
 * permission notice:
 *
 *     Logger class of mc_rtc
 *     Copyright 2015-2019 CNRS-UM LIRMM, CNRS-AIST JRL
 *     License: BSD-2-Clause (see licenses/LICENSE-mc_rtc)
 */

#include "mpacklog/Logger.h"

#include <string>

namespace mpacklog {

Logger::Logger(const std::string &path, bool append) {
  auto flags = std::ofstream::binary;
  if (append) {
    flags |= std::ofstream::app;
  }
  file_.open(path, flags);
  if (!file_) {
    throw std::runtime_error("Cannot open " + path + " for writing");
  }
  thread_ = std::thread([this]() {
#ifdef __APPLE__
    pthread_setname_np("logger_thread");
#else
    pthread_setname_np(pthread_self(), "logger_thread");
#endif
    while (keep_going_) {
      flush_buffer();

      // The sleep duration doesn't have a big influence, no need to wake up
      // too often. This value assumes a > 1 ms long control period.
      std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    flush_buffer();
  });
}

Logger::~Logger() {
  keep_going_ = false;
  if (thread_.joinable()) {
    thread_.join();
  }
  file_.close();
}

bool Logger::put(char *data, size_t size) {
  last_size_ = size;
  char *ndata = new char[size];
  std::memcpy(ndata, data, size);
  return buffer_.push({ndata, size});
}

void Logger::flush_buffer() {
  while (buffer_.pop(pop_)) {
    char *data = pop_.first;
    size_t size = pop_.second;
    file_.write(data, static_cast<int>(size));
    delete[] data;

    // Also flush the output stream, otherwise buffering tends to increase
    // variance / cause spikes in consumer loop rates.
    file_.flush();
  }
}

}  // namespace mpacklog
