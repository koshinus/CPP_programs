#pragma once

#include <cassert>
#include <coroutine>
#include <iostream>

using coro_t = std::coroutine_handle<>;

class evt_awaiter_t
{
    struct awaiter;

    //
    awaiter * top;
    bool set_flag;
    
    struct awaiter
    {
        evt_awaiter_t & event;
        awaiter * next;
        coro_t coro = nullptr;
        awaiter(evt_awaiter_t & event_) noexcept : event(event_) {}
        bool await_ready() const noexcept { return event.is_set(); }
        void await_suspend(coro_t coro_) noexcept
        {
            coro = coro_;
            event.push_awaiter(this);
        }
        void await_resume() noexcept { event.reset(); }
    };

public:
    evt_awaiter_t(bool set = false): set_flag(set), top(nullptr)
    {
        std::cout << "We are here!" << std::endl;
    }
    evt_awaiter_t(const evt_awaiter_t &) = delete;
    evt_awaiter_t & operator=(const evt_awaiter_t &) = delete;
    evt_awaiter_t(evt_awaiter_t && ) = delete;
    evt_awaiter_t & operator=(evt_awaiter_t && other) = delete;

    bool is_set() { return set_flag; }
    void push_awaiter(awaiter *some_awaiter)
    {
        awaiter * prev_top = top;
        top = some_awaiter;
        some_awaiter->next = prev_top;
    }

    awaiter operator co_await() noexcept { return awaiter(*this); }

    void set() noexcept
    {
        set_flag = true;
        awaiter * current = top;
        top = nullptr;
        while(current)
        {
            current->coro.resume();
            current = current->next;
        }
    }
    void reset() noexcept { set_flag = false; }
};
