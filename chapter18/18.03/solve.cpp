/*
 * TASK: Implement a template singleton class. This class must have a method
 *       instance() which returns a pointer to the instance of the singleton
 *       associated with it. Try also to make your singleton class be thread
 *       safe.
 */

#include <cassert>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

template<typename T>
class singleton
{
public:
    singleton() = delete;

    static T* instance()
    {
        static T* object = nullptr;
        static std::mutex barrier;

        /* create the singleton object if it does not exist */
        if (object == nullptr)
        {
            barrier.lock();

            /*
             * because multiple threads might have waited for the
             * lock to be available, make sure that the thread which
             * is currently holding the lock does not overwrite an
             * already created singleton object (we could have
             * always locked outside the if block to prevent this
             * situation, but that means we would lock for every
             * call of instance(), which is unnecessary and
             * expensive)
             */
            if (object == nullptr)
            {
                object = new T{};
            }

            barrier.unlock();
        }

        return object;
    }
};

void worker(int i)
{
    static std::mutex output_barrier;

    output_barrier.lock();
    std::cout << "start thread " << i << std::endl;
    output_barrier.unlock();

    assert(singleton<int>::instance() != nullptr);

    output_barrier.lock();
    std::cout << "finish thread " << i << std::endl;
    output_barrier.unlock();
}

int main()
{
    std::vector<std::thread> threads(10);

    int i = 0;

    for (std::thread& t : threads)
    {
        t = std::thread(worker, i);
        ++i;
    }

    for (std::thread& t : threads)
    {
        t.join();
    }

    delete singleton<int>::instance();

    return EXIT_SUCCESS;
}
