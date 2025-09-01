// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron

#include "mpacklog/DeltaLogger.h"

#include <string>

namespace mpacklog {

DeltaLogger::DeltaLogger(const std::string &path, bool append)
    : Logger(path, append) {}

bool DeltaLogger::put(const Dictionary &dict) {
  if (is_first_dict_) {
    // Initialize internal dictionary
    std::vector<char> buffer;
    size_t size = dict.serialize(buffer);
    full_dict_.update(buffer.data(), size);
    is_first_dict_ = false;

    // Serialize the full dictionary
    return Logger::put(dict);
  }

  // TODO(scaron): Implement delta compression below.
  // For now, we just call the parent's put method as a placeholder
  // In the next iteration, this will compute the delta between
  // dict and full_dict_, then log only the difference.
  std::vector<char> buffer;
  size_t size = dict.serialize(buffer);
  full_dict_.update(buffer.data(), size);
  return Logger::put(dict);
}

}  // namespace mpacklog
