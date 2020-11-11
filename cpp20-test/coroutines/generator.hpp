#pragma once

#include <coroutine>
#include <exception>

template<typename T>
struct generator
{
    struct promise_type
    {
        T val;

        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object(){ return coro_handle::from_promise(*this); }
        auto initial_suspend(){ return std::suspend_always(); }
        auto final_suspend(){ return std::suspend_always(); }
        auto yield_value(T val_)
        {
            val = val_;
            return std::suspend_always();
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    generator(coro_handle handle_): handle(handle_) {}
    generator(const generator & other) = delete;
    generator & operator=(const generator & other) = delete;
    generator(generator && other): handle(other.handle) { other.handle = nullptr; }
    generator & operator=(generator && other)
    {
        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }
    bool move_next(){ return handle ? (handle.resume(), !handle.done()) : false; }
    T current_value() const { return handle.promise().val; }
    ~generator(){ if(handle) handle.destroy(); }
private:
    coro_handle handle;
};
