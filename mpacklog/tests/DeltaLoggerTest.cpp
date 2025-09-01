// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "mpacklog/DeltaLogger.h"
#include "palimpsest/Dictionary.h"

namespace mpacklog::delta_logging {

TEST(DeltaLogger, Constructor) {
  DeltaLogger logger("test_delta.log");
  EXPECT_EQ(logger.buffer_size(), 0u);
}

TEST(DeltaLogger, InheritanceFromLogger) {
  // Test that DeltaLogger can be used wherever Logger is expected
  std::unique_ptr<Logger> logger =
      std::make_unique<DeltaLogger>("test_inheritance.log");

  palimpsest::Dictionary dict;
  dict("test") = "inheritance";

  bool success = logger->put(dict);
  EXPECT_TRUE(success);
}

}  // namespace mpacklog::delta_logging
