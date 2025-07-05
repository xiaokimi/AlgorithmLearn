#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <shared_mutex>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

class OrderProcessor;

struct Order
{
    std::string originId;
    std::chrono::steady_clock::time_point createTime;

    std::string handleId;
    std::chrono::steady_clock::time_point handleTime;
};

class Consumer
{
private:
    struct OrderCompare
    {
        bool operator()(const Order& A, const Order& B) const
        {
            return A.handleTime > B.handleTime;
        }
    };

public:
    Consumer(OrderProcessor* processor, int id, int priority, std::chrono::milliseconds timeout)
        : mProcessor(processor)
        , mId(id)
        , mPriority(priority)
        , mTimeout(timeout)
        , mRunning(true)
        , mCapacity(1)
        , mWorker(&Consumer::Working, this)
    {

    }

    virtual ~Consumer()
    {
        mRunning = false;
        if (mWorker.joinable())
        {
            mWorker.join();
        }
    }

    bool IsAvailable()
    {
        std::shared_lock<std::shared_mutex> lock(mMutex);
        return mCapacity > 0;
    }

    bool AddOrder(Order& order)
    {
        std::unique_lock<std::shared_mutex> lock(mMutex);
        if (mCapacity <= 0)
        {
            return false;
        }

        mCapacity--;
        mPendingOrders.push(order);
        return true;
    }

private:
    void Working()
    {
        while (mRunning)
        {
            std::unique_lock<std::shared_mutex> lock(mMutex);
            if (!mPendingOrders.empty())
            {
                auto now = std::chrono::steady_clock::now();
                if (now - mPendingOrders.top().handleTime > mTimeout)
                {
                    if (mProcessor)
                    {
                        mProcessor->ReInsertOrder(mPendingOrders.top());
                        mPendingOrders.pop();
                        mCapacity++;
                    }
                }
            }
            else
            {
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

private:
    OrderProcessor* mProcessor;

    int mId;
    int mPriority;
    std::chrono::milliseconds mTimeout;
    std::atomic_bool mRunning;

    int mCapacity;
    std::thread mWorker;
    mutable std::shared_mutex mMutex;
    std::priority_queue<Order, std::vector<Order>, OrderCompare> mPendingOrders;
};

class OrderProcessor
{
public:
    OrderProcessor()
        : mRunning(true)
        , mDispatcher(& OrderProcessor::DispatchOrders, this)
    {

    }

    virtual ~OrderProcessor()
    {
        mRunning = false;
        if (mDispatcher.joinable())
        {
            mDispatcher.join();
        }

        {
            std::unique_lock<std::shared_mutex> lock(mConsumerMutex);
            mConsumers.clear();
        }
    }

    void RegisterConsumer(std::unique_ptr<Consumer> consumer)
    {
        std::unique_lock<std::shared_mutex> lock(mConsumerMutex);
        mConsumers.push_back(std::move(consumer));
    }

    void AddOrder(Order& order)
    {
        std::unique_lock<std::shared_mutex> lock(mQueueMutex);
        order.createTime = std::chrono::steady_clock::now();
        mOrderQueue.push(order);
    }

    void ReInsertOrder(const Order& order)
    {
        std::unique_lock<std::shared_mutex> lock(mQueueMutex);
        mOrderQueue.push(order);
    }

private:
    void DispatchOrders()
    {
        while (mRunning)
        {
            std::unique_lock<std::shared_mutex> lock(mQueueMutex);
            if (!mOrderQueue.empty())
            {
                Order order = mOrderQueue.front();
                mOrderQueue.pop();
                lock.unlock();

                bool dispatched = false;
                {
                    std::shared_lock<std::shared_mutex> consumeLock(mConsumerMutex);
                    for (std::unique_ptr<Consumer>& consumer : mConsumers)
                    {
                        if (consumer->IsAvailable())
                        {
                            order.handleId = CreateOrderId();
                            order.handleTime = std::chrono::steady_clock::now();
                            if (consumer->AddOrder(order))
                            {
                                dispatched = true;
                                break;
                            }
                        }
                    }
                }

                if (!dispatched)
                {
                    std::unique_lock<std::shared_mutex> relock(mQueueMutex);
                    mOrderQueue.push(order);
                }
            }
            else
            {
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }

    std::string CreateOrderId()
    {
        std::unique_lock<std::shared_mutex> lock(mOrderIdMutex);

        std::string today = GetCurrentDate();
        if (today != mCurrentDate)
        {
            mCurrentDate = today;
            mSequnceId = 0;
        }

        std::stringstream ss;
        ss << mCurrentDate << std::setw(6) << std::setfill('0') << ++mSequnceId;
        return ss.str();
    }

    std::string GetCurrentDate()
    {
        auto now = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&time);

        std::stringstream ss;
        ss << std::put_time(&tm, "%Y%m%d");
        return ss.str();
    }

private:
    std::atomic_bool mRunning;
    std::thread mDispatcher;

    std::shared_mutex mQueueMutex;
    std::queue<Order> mOrderQueue;

    std::shared_mutex mConsumerMutex;
    std::vector<std::unique_ptr<Consumer>> mConsumers;

    std::shared_mutex mOrderIdMutex;
    uint32_t mSequnceId = 0;
    std::string mCurrentDate;
};

