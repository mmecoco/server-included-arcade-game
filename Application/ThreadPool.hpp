#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>

template <typename T, typename U>
class ThreadPool
{
private:
    using Task = std::function<void(T &, U &)>;

    std::vector<std::thread> m_thread;
    bool isDone = false;
    std::mutex mEventMutex;
    std::condition_variable_any m_working;
    std::queue<Task> m_queue;
    std::queue<U> m_entities;
    T &m_event;

    void startThread() {
        for (;;) {
            Task newTask;
            {
                std::unique_lock<std::mutex> lock{mEventMutex};
                m_working.wait(lock, [=] {return isDone || !m_queue.empty();});
                if (m_queue.empty() && isDone)
                    break;
            }
            newTask = std::move(m_queue.front());
            m_queue.pop();
            U ent = std::move(m_entities.front());
            m_entities.pop();

            newTask(m_event, ent);
        }
    }

public:
    ThreadPool(T &event, int nbThread = 10) : m_event(event)
    {
        for (int i = 0; i < nbThread; i++) {
            m_thread.push_back(std::thread(&ThreadPool::startThread, this));
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            isDone = true;
        }
        m_working.notify_all();
        for (auto &Thread : m_thread) {
            if (Thread.joinable())
                Thread.join();
        }
    }

    void enqueue(Task &&task, U &Entities)
    {
        {
            std::unique_lock<std::mutex> lock{mEventMutex};
            m_queue.emplace(std::move(task));
            m_entities.emplace(std::move(Entities));
        }
        m_working.notify_one();
    }
};