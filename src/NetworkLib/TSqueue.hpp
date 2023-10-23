//
// Created by Clément Lagasse on 20/09/2023.
//

#pragma once

#include <iostream>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <functional>

namespace Network {

    template<typename T>
    class TSQueue {
    public:
        TSQueue()
      : muxQueue()
      {
        }

        TSQueue(const TSQueue<T> &) = delete;

        virtual ~TSQueue() {
            clear();
        }

    public:
        const T &getFront() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.front();
        }

        const T &getBack() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.back();
        }

        T popFront() {
            std::scoped_lock lock(muxQueue);
            auto t = std::move(deqQueue.front());
            deqQueue.pop_front();
            return t;
        }

        T popBack() {
            std::scoped_lock lock(muxQueue);
            auto t = std::move(deqQueue.back());
            deqQueue.pop_back();
            return t;
        }

        void pushBack(const T &item) {
            std::scoped_lock lock(muxQueue);
            deqQueue.emplace_back(std::move(item));
        }

        void pushFront(const T &item) {
            std::scoped_lock lock(muxQueue);
            deqQueue.emplace_front(std::move(item));
        }

        bool empty() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.empty();
        }

        size_t count() {
            std::scoped_lock lock(muxQueue);
            return deqQueue.size();
        }

        void clear() {
            std::scoped_lock lock(muxQueue);
            deqQueue.clear();
        }

        void lock () {
            muxQueue.lock();
        }

        void unlock () {
            muxQueue.unlock();
        }

        std::size_t getMaxSize() {
            return deqQueue.max_size();
        }

        void sortQueue(std::function<bool(const T&, const T&)> compFunc) {
            std::scoped_lock lock(muxQueue);
            std::sort(deqQueue.begin(), deqQueue.end(), compFunc);
        }

    private:
        std::mutex muxQueue;
        std::deque<T> deqQueue;
    };
}