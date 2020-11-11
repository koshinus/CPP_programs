#pragma once

#include <iostream>
#include <string>
#include <coroutine>
#include <exception>
#include <cassert>

struct resumable
{
    struct promise_type
    {
        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object()
        {
            return coro_handle::from_promise(*this);
        }
        auto initial_suspend()
        {
            return std::suspend_always();
        }
        auto final_suspend()
        {
            return std::suspend_always();
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    resumable(coro_handle handle_): handle(handle_) {}
    resumable(const resumable & other) = delete;
    resumable & operator=(const resumable & other) = delete;
    resumable(resumable && other): handle(other.handle)
    {
        other.handle = nullptr;
    }
    resumable & operator=(resumable && other)
    {
        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }
    bool resume()
    {
        if(!handle.done())
            handle.resume();
        return handle.done();
    }
    ~resumable(){ handle.destroy(); }
private:
    coro_handle handle;
};

struct resumable_no_own
{
    struct promise_type
    {
        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object()
        {
            return coro_handle::from_promise(*this);
        }
        auto initial_suspend()
        {
            return std::suspend_never();
        }
        auto final_suspend()
        {
            return std::suspend_never();
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    resumable_no_own(coro_handle handle_){}
    resumable_no_own(const resumable_no_own &){};
    resumable_no_own & operator=(const resumable_no_own &){};
    resumable_no_own(resumable_no_own &&) {}
    resumable_no_own & operator=(resumable_no_own &&){}
};

struct suspend_tunable
{
    using coro_handle = std::coroutine_handle<>;
    bool should_continue;
    suspend_tunable(bool should_continue_ = true): should_continue(should_continue_) {}
    bool await_ready() const noexcept { return should_continue; }
    void await_suspend(coro_handle) const noexcept {}
    void await_resume() const noexcept {}
};

struct resumable_cancelable
{
    struct promise_type
    {
        bool is_canceled = false;

        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object(){ return coro_handle::from_promise(*this); }
        auto initial_suspend(){ return std::suspend_always(); }
        auto final_suspend(){ return std::suspend_always(); }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }

        auto await_transform(std::suspend_always)
        {
            if(is_canceled)
                return suspend_tunable{true};
            return suspend_tunable{false};
        }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    resumable_cancelable(coro_handle handle_): handle(handle_) {}
    resumable_cancelable(const resumable_cancelable & other) = delete;
    resumable_cancelable & operator=(const resumable_cancelable & other) = delete;
    resumable_cancelable(resumable_cancelable && other): handle(other.handle)
    {
        other.handle = nullptr;
    }
    resumable_cancelable & operator=(resumable_cancelable && other)
    {
        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }
    bool resume()
    {
        if(!handle.done())
            handle.resume();
        return handle.done();
    }
    bool cancel()
    {
        handle.promise().is_canceled = true;
        if(!handle.done())
            handle.resume();
        return handle.done();
    }
    ~resumable_cancelable(){ handle.destroy(); }
private:
    coro_handle handle;
};

struct resumable_noinc
{
    struct promise_type
    {
        using coro_handle = std::coroutine_handle<promise_type>;
        auto get_return_object()
        {
            return coro_handle::from_promise(*this);
        }
        auto initial_suspend()
        {
            return std::suspend_always();
        }
        auto final_suspend()
        {
            return std::suspend_always();
        }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using coro_handle = std::coroutine_handle<promise_type>;
    resumable_noinc(coro_handle handle_): handle(handle_) {}
    resumable_noinc(const resumable_noinc & other) = delete;
    resumable_noinc & operator=(const resumable_noinc & other) = delete;
    resumable_noinc(resumable_noinc && other): handle(other.handle)
    {
        other.handle = nullptr;
    }
    resumable_noinc & operator=(resumable_noinc && other)
    {
        handle = other.handle;
        other.handle = nullptr;
        return *this;
    }
    bool resume()
    {
        if(!handle.done())
            handle.resume();
        return handle.done();
    }
    ~resumable_noinc()
    {
        if(handle)
            handle.destroy();
    }
    coro_handle get_handle()
    {
        coro_handle h = handle;
        handle = nullptr;
        return h;
    }
private:
    coro_handle handle;
};
