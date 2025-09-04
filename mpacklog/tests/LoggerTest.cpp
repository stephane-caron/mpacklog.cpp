// SPDX-License-Identifier: Apache-2.0
// Copyright 2022 Stéphane Caron

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "mpacklog/Logger.h"

namespace mpacklog::logging {

TEST(Logger, BufferSize) {
  Logger logger("test_buffer_size.log");

  // Initially, buffer should be empty
  EXPECT_EQ(logger.buffer_size(), 0u);

  // Add some log entries and check that the buffer size increases
  char msg1[] = "message1";
  logger.put(msg1, 8);
  EXPECT_EQ(logger.buffer_size(), 1u);

  char msg2[] = "message2";
  logger.put(msg2, 8);
  EXPECT_EQ(logger.buffer_size(), 2u);

  char msg3[] = "message3";
  logger.put(msg3, 8);
  EXPECT_EQ(logger.buffer_size(), 3u);
}

TEST(Logger, LastSize) {
  Logger logger("test_last_size.log");

  // Initially, last_size should be 0
  EXPECT_EQ(logger.last_size(), 0u);

  // Add messages of different sizes and check last_size
  char small_msg[] = "hi";
  logger.put(small_msg, 2);
  EXPECT_EQ(logger.last_size(), 2u);

  char medium_msg[] = "hello world";
  logger.put(medium_msg, 11);
  EXPECT_EQ(logger.last_size(), 11u);

  char large_msg[] = "this is a longer message for testing";
  logger.put(large_msg, 36);
  EXPECT_EQ(logger.last_size(), 36u);
}

TEST(Logger, PutReturnValue) {
  Logger logger("test_put_return.log");

  // put() should return true on successful storage
  char msg[] = "test message";
  EXPECT_TRUE(logger.put(msg, 12));

  char msg2[] = "another message";
  EXPECT_TRUE(logger.put(msg2, 15));
}

TEST(Logger, PutDifferentSizes) {
  Logger logger("test_put_sizes.log");

  // Test with various message sizes
  char empty_msg[] = "";
  logger.put(empty_msg, 0);
  EXPECT_EQ(logger.buffer_size(), 1u);
  EXPECT_EQ(logger.last_size(), 0u);

  char single_char[] = "a";
  logger.put(single_char, 1);
  EXPECT_EQ(logger.buffer_size(), 2u);
  EXPECT_EQ(logger.last_size(), 1u);

  char long_msg[256];
  for (int i = 0; i < 255; ++i) {
    long_msg[i] = 'x';
  }
  long_msg[255] = '\0';
  logger.put(long_msg, 255);
  EXPECT_EQ(logger.buffer_size(), 3u);
  EXPECT_EQ(logger.last_size(), 255u);
}

TEST(Logger, PutDictionary) {
  Logger logger("test_dict.log");

  // Test putting a dictionary
  Dictionary dict;
  dict("key1") = "value1";
  dict("key2") = 42;
  dict("key3") = 3.14;

  EXPECT_TRUE(logger.put(dict));
  EXPECT_EQ(logger.buffer_size(), 1u);

  // Dictionary should serialize to non-zero size
  EXPECT_GT(logger.last_size(), 0u);
}

TEST(Logger, Constructor) {
  // Test constructor with different file paths
  Logger logger1("test_constructor1.log");
  EXPECT_EQ(logger1.buffer_size(), 0u);
  EXPECT_EQ(logger1.last_size(), 0u);

  Logger logger2("test_constructor2.log", false);
  EXPECT_EQ(logger2.buffer_size(), 0u);
  EXPECT_EQ(logger2.last_size(), 0u);

  Logger logger3("test_constructor3.log", true);
  EXPECT_EQ(logger3.buffer_size(), 0u);
  EXPECT_EQ(logger3.last_size(), 0u);
}

}  // namespace mpacklog::logging
