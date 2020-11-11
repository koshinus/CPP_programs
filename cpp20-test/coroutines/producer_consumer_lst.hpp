#pragma once

#include <cassert>
#include <coroutine>
#include <list>

using coro_t = std::coroutine_handle<>;

class evt_awaiter_t
{
    struct awaiter;

    //
    std::list<awaiter> lst;
    bool set_flag;
    
    struct awaiter
    {
        evt_awaiter_t & event;
        coro_t coro = nullptr;
        awaiter(evt_awaiter_t & event_) noexcept : event(event_) {}
        bool await_ready() const noexcept { return event.is_set(); }
        void await_suspend(coro_t coro_) noexcept
        {
            coro = coro_;
            event.push_awaiter(*this);
        }
        void await_resume() noexcept { event.reset(); }
    };

public:
    evt_awaiter_t(bool set = false): set_flag(set) {}
    evt_awaiter_t(const evt_awaiter_t &) = delete;
    evt_awaiter_t & operator=(const evt_awaiter_t &) = delete;
    evt_awaiter_t(evt_awaiter_t && ) = delete;
    evt_awaiter_t & operator=(evt_awaiter_t && other) = delete;

public:
    bool is_set() { return set_flag; }
    void push_awaiter(awaiter some_awaiter) { lst.push_back(some_awaiter); }

    awaiter operator co_await() noexcept { return awaiter(*this); }

    void set() noexcept
    {
        set_flag = true;
#if INEFF
        auto ntoresume = lst.size();
        while(ntoresume > 0)
        {
            lst.front().coro.resume();
            lst.pop_front();
            ntoresume--;
        }
#else
        std::list<awaiter> toresume;
        toresume.splice(toresume.begin(), lst);
        for(auto aw : toresume)
            aw.coro.resume();
#endif
    }
    void reset() noexcept { set_flag = false; }
};
