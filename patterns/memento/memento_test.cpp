#include <iostream>
#include <stack>

/*
Снимок(memento) - шаблон, предназначенный для работы с разными состояниями и версиями
    некой сущности, чтобы можно было "откатиться" к предыдущим версиям.
*/

enum class state{ A, B, C };

struct memento
{
    memento(state st): state_(st) {}
    state get_state() { return state_; }
private:
    state state_;
};

class originator
{
    state state_;
public:
    originator(): state_(state::A) {}
    void about() { std::cout << "Current state is " << static_cast<int>(state_) << std::endl; }
    memento save(int fst, int snd)
    {
        if(fst && snd)
            state_ = state::B;
        else if(!fst && !snd)
            state_ = state::C;            
        return memento(state_);
    }
    void restore(memento m) { state_ = m.get_state(); }
};

class caretaker
{
    //TODO: так и не понял, как работает схема, когда memento является
    // вложенным классом originator
    std::stack<memento> history;
    originator orig;
public:
    void do_thing()
    {
        int x, y;
        std::cin >> x >> y;
        history.push(orig.save(x,y));
        orig.about();
    }
    void undo()
    {
        memento back = history.top();
        history.pop();
        orig.restore(back);
        orig.about();
    }
};

int main()
{
    caretaker ct;
    ct.do_thing();
    ct.do_thing();
    ct.undo();
    return 0;
}
