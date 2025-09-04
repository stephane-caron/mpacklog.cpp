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

TEST(DeltaLogger, PutDictionary) {
  DeltaLogger logger("test_delta_put.log");

  palimpsest::Dictionary dict1;
  dict1("counter") = 1;
  dict1("name") = "first";

  palimpsest::Dictionary dict2;
  dict2("counter") = 2;
  dict2("name") = "second";

  // Put first dictionary
  bool success1 = logger.put(dict1);
  EXPECT_TRUE(success1);

  // Put second dictionary
  bool success2 = logger.put(dict2);
  EXPECT_TRUE(success2);

  // Both puts should succeed
  EXPECT_TRUE(success1 && success2);
}

TEST(DeltaLogger, MultipleDictionaries) {
  DeltaLogger logger("test_delta_multiple.log");

  // Test logging multiple dictionaries with similar structure
  for (int i = 0; i < 5; ++i) {
    palimpsest::Dictionary dict;
    dict("iteration") = i;
    dict("value") = i * 10;
    dict("constant") = "unchanged";

    bool success = logger.put(dict);
    EXPECT_TRUE(success);
  }

  // Verify buffer has entries
  EXPECT_GT(logger.buffer_size(), 0u);
}

}  // namespace mpacklog::delta_logging
