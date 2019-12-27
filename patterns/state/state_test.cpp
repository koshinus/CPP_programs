#include <iostream>
#include <thread>
#include <chrono>

/*
Состояние - шаблон, предназначенный, для упрощения обработки конечного автомата.
*/

enum class STATES{ STANDING_BY, POUR, PAYMENT_RCV };

struct coffee_machine_state
{
    virtual coffee_machine_state * calc_new_state(STATES state, coffee_machine_state * all_states[]) = 0;
};

struct coffee_machine_standing_by: public coffee_machine_state
{
    virtual coffee_machine_state * calc_new_state(STATES state, coffee_machine_state * all_states[]) override;
};

struct coffee_machine_pour: public coffee_machine_state
{
    virtual coffee_machine_state * calc_new_state(STATES state, coffee_machine_state * all_states[]) override;
};

struct coffee_machine_payment_recieving: public coffee_machine_state
{
    virtual coffee_machine_state * calc_new_state(STATES state, coffee_machine_state * all_states[]) override;
};

coffee_machine_state * coffee_machine_standing_by::calc_new_state(STATES state, coffee_machine_state * all_states[])
{
    // Автомат в режиме ожидания, пришла команда налить
    if(state == STATES::POUR)
    {
        std::cout << "Waiting for payment..." << std::endl;
        // Состояние ожидания оплаты в статическом массиве 
        // кофе-автомата хранится в ячейке с номером 1
        return all_states[1];
    }
    std::cout << "Still standing by state." << std::endl;
    // Этот же самый объект будет хранится в all_states под номером 0
    return this;
}

coffee_machine_state * coffee_machine_payment_recieving::calc_new_state(STATES state, coffee_machine_state * all_states[])
{
    // Автомат в режиме ожидания оплаты, все деньги получены -
    // можно начинать наливать
    if(state == STATES::PAYMENT_RCV)
    {
        std::cout << "Payment accepted." << std::endl;
        // Состояние подачи кофе в статическом массиве 
        // кофе-автомата хранится в ячейке с номером 2
        return all_states[2]->calc_new_state(state, all_states);
    }
    std::cout << "Still waiting for payment." << std::endl;
    // Этот же самый объект будет хранится в all_states под номером 1
    return this;
}

coffee_machine_state * coffee_machine_pour::calc_new_state(STATES state, coffee_machine_state * all_states[])
{
    // Автомат в режиме подачи кофе, чтобы не нажимали, мы должны налить кофе и
    // перейти в состояние ожидания
    std::cout << "Start pouring..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "End pouring. Switch to stand-by state." << std::endl;
    return all_states[0];
}

class coffee_machine
{
    coffee_machine_state * all_states[3];
    coffee_machine_state * cur_state;
public:
    coffee_machine()
    {
        all_states[0] = new coffee_machine_standing_by();
        all_states[1] = new coffee_machine_payment_recieving();
        all_states[2] = new coffee_machine_pour();
        cur_state = all_states[0];
    }
    void handle_input(STATES state)
    {
        cur_state = cur_state->calc_new_state(state, all_states);
    }
    ~coffee_machine() { delete all_states[0], all_states[1], all_states[2]; }
};

int main()
{
    coffee_machine machine;
    machine.handle_input(STATES::POUR);
    machine.handle_input(STATES::PAYMENT_RCV);
    machine.handle_input(STATES::PAYMENT_RCV);
    return 0;
}
