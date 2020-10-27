/*
 * TASK: You are given three functions A(), B() and C() which define the work
 *       of three different types of threads a, b and c respectively. Design a
 *       mechanism such that when n instances of each thread a, b and c are
 *       created in any order, we always have the following execution chain:
 *
 *       A() -> B() -> C() -> A() -> B() -> C() -> ...
 *
 *       In other words, A() must be called exactly once before B() can be
 *       called and B() must be called exactly once before C() can be called.
 *       This must hold for all subsequent calls of A(), B() and C().
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

/*
 * mutex_B guarantees that B will never run before A, mutex_C guarantees that C
 * will never run before B and mutex_A guarantees that a set of threads {A,B,C}
 * must be entirely executed before a new set of threads {A,B,C} is allowed to
 * run, i.e., that as soon as A is called, C (and therefore also B) must be
 * executed before another A can begin.
 */
std::mutex mutex_A;
std::mutex mutex_B;
std::mutex mutex_C;

/* thread execution sequence (A -> 0, B -> 1 -> C -> 2) */
std::vector<int> sequence;

void A()
{
    mutex_A.lock();
    sequence.push_back(0);
    mutex_B.unlock();
}

void B()
{
    mutex_B.lock();
    sequence.push_back(1);
    mutex_C.unlock();
}

void C()
{
    mutex_C.lock();
    sequence.push_back(2);
    mutex_A.unlock();
}

int main()
{
    std::random_device device;
    std::mt19937 generator(device());

    /* the first thread to run must be an A */
    mutex_B.lock();
    mutex_C.lock();

    for (size_t n = 0; n <= 100; ++n)
    {
        std::vector<std::thread> threads;
        std::vector<void (*)()> functions;

        /* n instances of each thread type */
        while (functions.size() < 3 * n)
        {
            functions.push_back(A);
            functions.push_back(B);
            functions.push_back(C);
        }

        /* start the threads in random order */
        std::shuffle(functions.begin(), functions.end(), generator);

        sequence.clear();

        for (const auto& f : functions)
        {
            threads.push_back(std::thread(f));
        }

        for (std::thread& t : threads)
        {
            t.join();
        }

        assert(sequence.size() == 3 * n);

        /* check if the thread execution sequence is correct */
        int next = 0;
        for (const int i : sequence)
        {
            assert(i == next);
            next = (next + 1) % 3;
        }

        std::cout << "passed random test for call sequence of size " << n
                  << std::endl;
    }

    return EXIT_SUCCESS;
}
