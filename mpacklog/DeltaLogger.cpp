// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron

#include "mpacklog/DeltaLogger.h"

#include <string>

namespace mpacklog {

DeltaLogger::DeltaLogger(const std::string &path, bool append)
    : Logger(path, append) {}

bool DeltaLogger::put(const Dictionary &dict) {
  if (is_first_dict_) {
    full_dict_.update(dict);
    is_first_dict_ = false;
    return Logger::put(dict);
  }

  Dictionary delta = dict.difference(full_dict_);
  full_dict_.update(dict);
  return Logger::put(delta);
}

}  // namespace mpacklog
