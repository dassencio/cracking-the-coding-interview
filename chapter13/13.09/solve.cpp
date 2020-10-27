/*
 * TASK: Implement a smart pointer.
 */

#include <cassert>
#include <iostream>
#include <random>

/**
 * @brief A very simple smart pointer class: no move operations, no comparison
 *        operators, no reset operations etc.
 */
template<typename T>
class smart_ptr
{
public:
    smart_ptr(T* object = nullptr) : object_(object), count_(new int(1))
    {
        /* nothing needs to be done here */
    }

    smart_ptr(const smart_ptr& p) : object_(p.object_), count_(p.count_)
    {
        ++(*count_);
    }

    ~smart_ptr()
    {
        decrease_ref();
    }

    smart_ptr& operator=(const smart_ptr& p)
    {
        if (this != &p)
        {
            /* if p is a smart_ptr for another object */
            if (object_ != p.object_)
            {
                decrease_ref();
            }

            count_ = p.count_;
            object_ = p.object_;

            ++(*count_);
        }

        return *this;
    }

    int use_count() const
    {
        return *count_;
    }

    T& operator*() const
    {
        return *object_;
    }

    T* operator->() const
    {
        return object_;
    }

private:
    void decrease_ref()
    {
        --(*count_);

        if (*count_ == 0)
        {
            delete count_;
            delete object_;
        }
    }

    T* object_;
    int* count_;
};

struct test
{
    int x = 0;
};

int main()
{
    /* test: constructor with given pointer */
    smart_ptr<int> p1(new int(2));
    assert(p1.use_count() == 1);

    /* test: copy constructor */
    smart_ptr<int> p2(p1);
    assert(p1.use_count() == 2 && p2.use_count() == 2);

    /* test: change value of object pointed to */
    (*p2) = 3;
    assert(*p1 == 3 && *p2 == 3);
    assert(p1.use_count() == 2 && p2.use_count() == 2);

    /* test: copy assignment (to smart pointer pointing to nullptr) */
    smart_ptr<int> p3;
    p3 = p1;
    (*p3) = 7;
    assert(*p1 == 7 && *p2 == 7 && *p3 == 7);
    assert(p1.use_count() == 3 && p2.use_count() == 3 && p3.use_count() == 3);

    /* test: self copy assignment (should have no effect) */
    p3 = p3;
    assert(*p1 == 7 && *p2 == 7 && *p3 == 7);
    assert(p1.use_count() == 3 && p2.use_count() == 3 && p3.use_count() == 3);

    /* test: copy assignment (involving object destruction) */
    smart_ptr<int> p4(new int(4));
    p4 = p1;
    assert(*p1 == 7 && *p2 == 7 && *p3 == 7 && *p4 == 7);
    assert(p1.use_count() == 4 && p2.use_count() == 4 && p3.use_count() == 4 &&
           p4.use_count() == 4);

    /* test: destructor */
    {
        smart_ptr<int> p5 = p1;
    }
    assert(*p1 == 7 && *p2 == 7 && *p3 == 7 && *p4 == 7);
    assert(p1.use_count() == 4 && p2.use_count() == 4 && p3.use_count() == 4 &&
           p4.use_count() == 4);

    /* test: access pointed-to object using the -> operator */
    smart_ptr<test> ps1(new test{});
    smart_ptr<test> ps2(ps1);
    ps2->x = 2;
    assert(ps1->x == 2);

    std::cout << "passed all tests" << std::endl;

    return EXIT_SUCCESS;
}
