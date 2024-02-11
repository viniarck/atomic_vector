#include "atomic_vector.h"
#include "gtest/gtest.h"
#include <iostream>
#include <thread>

TEST(atomic_vector, first) { EXPECT_EQ(1, 1); }

TEST(atomic_vector, push_back) {
    auto v = atomic_vector<int>();
    auto n = 1000;
    for (int i = 0; i < n; i++) {
        v.push_back(i);
        EXPECT_EQ(v.at(i), i);
    }
    EXPECT_EQ(v.size(), n);
}

TEST(atomic_vector, push_back_concurrent) {
    auto v = atomic_vector<int>();
    auto n = 10000;
    auto threads = std::vector<std::thread>{};
    auto n_threads = 10;

    auto fill_vec = [](atomic_vector<int> &vec, int from, int to) {
        for (int i = from; i < to; i++) {
            vec.push_back(i);
        }
    };

    auto ratio = int(n / n_threads);
    for (int i = 0; i < n_threads; i++) {
        threads.push_back(std::thread([&fill_vec, &v, i, ratio]() {
            fill_vec(v, i * ratio, (i + 1) * ratio);
        }));
    }
    for (int i = 0; i < n_threads; i++) {
        threads[i].join();
    }

    EXPECT_EQ(v.size(), n);
}
