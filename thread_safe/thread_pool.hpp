#include"thread_safe_queue.hpp"
#include"join_threads.hpp"
#include<atomic>

class thread_pool
{
    std::atomic_bool done;
    thread_safe_queue<std::function<void()> > work_queue;
    std::vector<std::thread> threads;
    join_threads joiner;

    void work_thread()
    {
        while(!done)
        {
            std::function<void()> task;
            if(work_queue.try_pop(task) )
            {
                task();
            }else{
                std::this_thread::yield();
            }
        }
    }
    public:
        thread_pool():done(false),joiner(threads)
        {
            unsigned const thread_count = std::thread::hardware_concurrency();
            std::cout<<thread_count<<std::endl;
            try{
                for(unsigned i = 0;i<thread_count;++i)
                {
                    threads.push_back(std::thread(&thread_pool::work_thread,this));
                }
            }catch(...)
            {
                done=true;
                throw;
            }
        }

        ~thread_pool()
        {
            done=true;
        }

        template<typename func>
        void submit(func f)
        {
            work_queue.push(std::function<void()> (f));
        }
};