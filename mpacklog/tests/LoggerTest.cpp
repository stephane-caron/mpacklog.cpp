/*
 * Copyright 2022 Stéphane Caron
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "mpacklog/Logger.h"

namespace mpacklog::logging {

TEST(Logger, Foo) { Logger logger("test.log"); }

TEST(Logger, BufferSize) {
  Logger logger("test_buffer_size.log");

  // Initially, buffer should be empty
  EXPECT_EQ(logger.buffer_size(), 0u);

  // Add some log entries and check buffer size increases
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

}  // namespace mpacklog::logging
