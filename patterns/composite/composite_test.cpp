#include <iostream>
#include <vector>

/*
Компоновщик - шаблон, предназначенный для взаимодействия с объектами,
    которые могут быть представлены в виде дерева.
*/

struct node
{
    node(): price(0) {}
    virtual size_t say_price() = 0;
    virtual void add(node * node_) {};
protected:
    size_t price;
};

struct leaf: public node
{
    leaf(size_t price_): node()
    {
        price = price_;
    }
    virtual size_t say_price() override { return price; }
};

struct box: public node
{
    virtual void add(node * node_) { children.push_back(node_); };
    virtual size_t say_price() override
    {
        size_t full_price = 0;
        for(node * node_ : children)
            full_price += node_->say_price();
        return full_price;
    }
private:
    std::vector<node *> children;
};

int main()
{
    // По идее, код создания и заполнения надо вынести непосредственно в классы выше
    node * leaf1 = new leaf(1),
            * leaf2 = new leaf(2),
            * leaf3 = new leaf(3),
            * leaf4 = new leaf(4);
    node * box1 = new box(), * box2 = new box();
    box1->add(leaf1); box1->add(box2);
    box2->add(leaf2); box2->add(leaf3); box2->add(leaf4);
    std::cout << "In the subtree we have " << box2->say_price()
                << ". And the full price is " << box1->say_price() << std::endl;
    delete leaf1, leaf2, leaf3, leaf4, box1, box2;
}
