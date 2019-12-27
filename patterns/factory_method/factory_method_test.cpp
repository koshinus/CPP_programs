#include <iostream>
#include <string>

/*
Фабричный метод/фабрика - шаблон предназначенный для единообразного создания
    объектов различных типов, реализующих один интерфейс. 
*/

struct game
{
    virtual void about() = 0;
};

struct strategy: public game
{
    virtual void about() override { std::cout << "This is the strategy game!" << std::endl; }
};

struct shooter: public game
{
    virtual void about() override { std::cout << "This game is the shooter!" << std::endl; }
};

struct factory
{
    virtual game * create() = 0;
};

struct strategy_game_creator: public factory
{
    virtual game * create() override { return new strategy(); }
};

struct shooter_game_creator: public factory
{
    virtual game * create() override { return new shooter(); }
};

int main()
{
    std::string game_genre;
    std::cin >> game_genre;
    game * game;
    factory * game_creator;
    // Данный порождающий код, при желании, можно вынести в отдельный класс-создатель
    if(game_genre == "strategy")
        game_creator = new strategy_game_creator();
    else if(game_genre == "shooter")
        game_creator = new shooter_game_creator();
    else
        std::exit(1);

    game = game_creator->create();
    game->about();
    delete game, game_creator;
}
