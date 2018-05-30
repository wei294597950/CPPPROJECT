#include<mutex>
#include<queue>
#include<memory>
#include<condition_variable>
template<typename T>
class thread_safe_queue
{
    private:
        mutable std::mutex mux;
        std::queue<std::shared_ptr<T> > data_queue;
        std::condition_variable data_cond;
    public:
        thread_safe_queue()
        {}
        void wait_and_pop(T& value)
        {
            std::unique_lock<std::mutex> lk(mux);
            data_cond.wait(lk,[this]{return !data_queue.empty();});
            value = std::move(*data_queue.front());
            data_queue.pop();
        }

        bool try_pop(T& value)
        {
            std::lock_guard<std::mutex> lk(mux);
            if(data_queue.empty())
            {
                return false;
            }
            value = std::move(*data_queue.front());
            data_queue.pop();
            return true;
        }

        std::shared_ptr<T> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(mux);
            data_cond.wait(lk,[this]{return !data_queue.empyt();});
            std::shared_ptr<T> res = data_queue.front();
            data_queue.pop();
            return res;
        }

        std::shared_ptr<T> try_pop()
        {
            std::lock_guard<std::mutex> lk(mux);
            if(data_queue.empty())
                return std::shared_ptr<T>();
            std::shared_ptr<T> res = data_queue.front();
            data_queue.pop();
            return res;
        }

        void push(T new_value)
        {
            std::shared_ptr<T> data(
                std::make_shared<T>(std::move(new_value)));
            std::lock_guard<std::mutex> lk(mux);
            data_queue.push(data);
            data_cond.notify_one();
        }

        bool empty()
        {
            std::lock_guard<std::mutex> lk(mux);
            return data_queue.empty();
        }
};