// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron

#pragma once

#include <palimpsest/Dictionary.h>

#include <string>

#include "mpacklog/Logger.h"

namespace mpacklog {

using palimpsest::Dictionary;

/*! Logger with delta compression.
 *
 * This logger inherits from Logger and overrides the put function to perform
 * delta compression (delta encoding) on dictionaries before logging them.
 * Delta compression stores only the differences between consecutive
 * dictionaries, reducing file size for similar sequential data.
 */
class DeltaLogger : public Logger {
 public:
  /*! Open a new log file and start the logging thread with delta compression.
   *
   * \param[in] path Path to the output log file.
   * \param[in] append If true, append to the log file if it exists.
   */
  explicit DeltaLogger(const std::string &path, bool append = false);

  /*! Save a dictionary to be written to the log with delta compression.
   *
   * This function computes the difference between the input dictionary and the
   * last put dictionary. Only that difference will be logged.
   *
   * \param dict Dictionary to log with delta compression.
   *
   * \return True if the dictionary was successfully stored for logging.
   */
  bool put(const Dictionary &dict);

 private:
  //! Uncompressed version of the last logged dictionary.
  Dictionary full_dict_;

  //! Flag to track if this is the first dictionary being logged.
  bool is_first_dict_ = true;
};

}  // namespace mpacklog
