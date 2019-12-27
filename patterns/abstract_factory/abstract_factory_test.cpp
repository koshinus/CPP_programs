#include <iostream>
#include <string>

/*
Абстрактная фабрика - шаблон предназначенный для единообразного создания объектов,
    которые можно сгруппировать по нескольким разным свойствам и для своего создания
    требуют несколько обычных фабрик.
*/

struct game_genre
{
    virtual void about() = 0;
};

struct strategy: public game_genre
{
    virtual void about() override { std::cout << "This is the strategy game!" << std::endl; }
};

struct shooter: public game_genre
{
    virtual void about() override { std::cout << "This game is the shooter!" << std::endl; }
};

struct racing: public game_genre
{
    virtual void about() override { std::cout << "This game is the racing!" << std::endl; }
};

struct game_dimension
{
    game_dimension(size_t dim): dimension(dim) {}
    virtual void dimension_info() { std::cout << "Dimension is " << dimension << std::endl; }
protected:
    size_t dimension;
};

struct game_2d: public game_dimension
{
    game_2d(): game_dimension(2), base_x_coord(0), base_y_coord(0) {}
    virtual void dimension_info() override
    {
        game_dimension::dimension_info();
        std::cout << "We have additional info: (" 
                    << base_x_coord << ',' << base_y_coord
                    << ") as start cordinates." << std::endl;
    }
private:
    size_t base_x_coord;
    size_t base_y_coord;
};

struct game_3d: public game_dimension
{
    game_3d(): game_dimension(3), base_x_coord(0), base_y_coord(0), base_z_coord(0) {}
    virtual void dimension_info() override
    {
        game_dimension::dimension_info();
        std::cout << "We have additional info: (" 
                    << base_x_coord << ',' << base_y_coord << ',' << base_z_coord
                    << ") as start cordinates." << std::endl;
    }
private:
    size_t base_x_coord;
    size_t base_y_coord;
    size_t base_z_coord;
};

struct vr_game: public game_dimension
{
    vr_game(): game_dimension(0) {}
    virtual void dimension_info() override { std::cout << "I'm just a small vr-experience." << std::endl; }
};

struct game
{
    game(): genre(nullptr), dim(nullptr) {}
    game(game_genre * genre_, game_dimension * dim_): genre(genre_), dim(dim_){}
    void about_game() { genre->about(); dim->dimension_info(); }
    ~game() { delete genre, dim; }
private:
    game_genre * genre;
    game_dimension * dim;
};

struct game_creator
{
    virtual game * create_strategy() = 0;
    virtual game * create_shooter() = 0;
    virtual game * create_racing() = 0;
};

struct game_2d_creator: public game_creator
{
    virtual game * create_strategy() { return new game(new strategy(), new game_2d()); }
    virtual game * create_shooter() { return new game(new shooter(), new game_2d()); }
    virtual game * create_racing() { return new game(new racing(), new game_2d()); }
};

struct game_3d_creator: public game_creator
{
    virtual game * create_strategy() { return new game(new strategy(), new game_3d()); }
    virtual game * create_shooter() { return new game(new shooter(), new game_3d()); }
    virtual game * create_racing() { return new game(new racing(), new game_3d()); }
};

struct vr_game_creator: public game_creator
{
    virtual game * create_strategy() { return new game(new strategy(), new vr_game()); }
    virtual game * create_shooter() { return new game(new shooter(), new vr_game()); }
    virtual game * create_racing() { return new game(new racing(), new vr_game()); }
};

/*
В случае, если надо добавить ещё одно архетипичное свойство (например, целевую платформу xbox,
    ps, pc и т.п.) можно создать класс-фабрику, инкапсулирующую game_creator и обращаться к ней.
*/

int main()
{
    // По идее, можно усложнить клиентский код, чтобы создавать
    // нужные фабрики и игры без перекомпиляции.
    game_creator * creator = new game_3d_creator();
    game * strategy = creator->create_strategy();
    strategy->about_game();
    delete creator, strategy;
}
