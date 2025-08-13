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

#include "gtest/gtest.h"
#include "mpacklog/CircularBuffer.h"

namespace mpacklog {

TEST(CircularBuffer, PushAndPop) {
  CircularBuffer<double, 10> buffer;
  double popped;
  buffer.push(1.);
  buffer.push(2.);
  buffer.pop(popped);
  ASSERT_FALSE(buffer.empty());
  buffer.pop(popped);
  ASSERT_TRUE(buffer.empty());
}

TEST(CircularBuffer, CannotPushForever) {
  CircularBuffer<double, 3> buffer;
  ASSERT_TRUE(buffer.push(1.));
  ASSERT_TRUE(buffer.push(2.));
  ASSERT_TRUE(buffer.push(3.));
  ASSERT_FALSE(buffer.push(4.));
  ASSERT_FALSE(buffer.push(5.));

  double popped;
  ASSERT_TRUE(buffer.pop(popped));
  ASSERT_TRUE(buffer.pop(popped));
  ASSERT_TRUE(buffer.pop(popped));
  ASSERT_FALSE(buffer.pop(popped));
  ASSERT_FALSE(buffer.pop(popped));
}

TEST(CircularBuffer, Size) {
  CircularBuffer<int, 5> buffer;

  // Initially empty
  EXPECT_EQ(buffer.size(), 0u);
  EXPECT_TRUE(buffer.empty());

  // Add items and check size increases
  buffer.push(1);
  EXPECT_EQ(buffer.size(), 1u);
  EXPECT_FALSE(buffer.empty());

  buffer.push(2);
  EXPECT_EQ(buffer.size(), 2u);

  buffer.push(3);
  EXPECT_EQ(buffer.size(), 3u);

  // Pop items and check size decreases
  int popped;
  buffer.pop(popped);
  EXPECT_EQ(buffer.size(), 2u);

  buffer.pop(popped);
  EXPECT_EQ(buffer.size(), 1u);

  buffer.pop(popped);
  EXPECT_EQ(buffer.size(), 0u);
  EXPECT_TRUE(buffer.empty());
}

TEST(CircularBuffer, OrderPreservation) {
  CircularBuffer<int, 10> buffer;

  // Push sequence of values
  for (int i = 1; i <= 5; ++i) {
    ASSERT_TRUE(buffer.push(i));
  }

  // Pop and verify order (FIFO)
  int popped;
  for (int expected = 1; expected <= 5; ++expected) {
    ASSERT_TRUE(buffer.pop(popped));
    EXPECT_EQ(popped, expected);
  }

  EXPECT_TRUE(buffer.empty());
}

TEST(CircularBuffer, WrappingBehavior) {
  CircularBuffer<char, 3> buffer;

  // Fill buffer to capacity
  ASSERT_TRUE(buffer.push('a'));
  ASSERT_TRUE(buffer.push('b'));
  ASSERT_TRUE(buffer.push('c'));
  EXPECT_EQ(buffer.size(), 3u);

  // Cannot push more
  ASSERT_FALSE(buffer.push('d'));
  EXPECT_EQ(buffer.size(), 3u);

  // Pop one item, then can push again
  char popped;
  ASSERT_TRUE(buffer.pop(popped));
  EXPECT_EQ(popped, 'a');
  EXPECT_EQ(buffer.size(), 2u);

  ASSERT_TRUE(buffer.push('d'));
  EXPECT_EQ(buffer.size(), 3u);

  // Verify remaining order
  ASSERT_TRUE(buffer.pop(popped));
  EXPECT_EQ(popped, 'b');
  ASSERT_TRUE(buffer.pop(popped));
  EXPECT_EQ(popped, 'c');
  ASSERT_TRUE(buffer.pop(popped));
  EXPECT_EQ(popped, 'd');

  EXPECT_TRUE(buffer.empty());
}

TEST(CircularBuffer, DifferentTypes) {
  // Test with string type
  CircularBuffer<std::string, 5> str_buffer;
  ASSERT_TRUE(str_buffer.push("hello"));
  ASSERT_TRUE(str_buffer.push("world"));
  EXPECT_EQ(str_buffer.size(), 2u);

  std::string popped_str;
  ASSERT_TRUE(str_buffer.pop(popped_str));
  EXPECT_EQ(popped_str, "hello");

  // Test with pair type
  CircularBuffer<std::pair<int, double>, 3> pair_buffer;
  ASSERT_TRUE(pair_buffer.push(std::make_pair(1, 1.5)));
  ASSERT_TRUE(pair_buffer.push(std::make_pair(2, 2.5)));
  EXPECT_EQ(pair_buffer.size(), 2u);

  std::pair<int, double> popped_pair;
  ASSERT_TRUE(pair_buffer.pop(popped_pair));
  EXPECT_EQ(popped_pair.first, 1);
  EXPECT_EQ(popped_pair.second, 1.5);
}

TEST(CircularBuffer, EmptyBuffer) {
  CircularBuffer<int, 10> buffer;

  // Empty buffer operations
  EXPECT_TRUE(buffer.empty());
  EXPECT_EQ(buffer.size(), 0u);

  // Cannot pop from empty buffer
  int popped;
  EXPECT_FALSE(buffer.pop(popped));
}

TEST(CircularBuffer, SingleElementBuffer) {
  CircularBuffer<int, 1> buffer;

  // Can push one element
  ASSERT_TRUE(buffer.push(42));
  EXPECT_EQ(buffer.size(), 1u);
  EXPECT_FALSE(buffer.empty());

  // Cannot push another
  ASSERT_FALSE(buffer.push(43));
  EXPECT_EQ(buffer.size(), 1u);

  // Can pop the element
  int popped;
  ASSERT_TRUE(buffer.pop(popped));
  EXPECT_EQ(popped, 42);
  EXPECT_TRUE(buffer.empty());

  // Cannot pop again
  ASSERT_FALSE(buffer.pop(popped));
}

}  // namespace mpacklog
