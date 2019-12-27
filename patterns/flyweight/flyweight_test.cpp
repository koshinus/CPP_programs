#include <iostream>
#include <cstddef>

/*
Легковес/Приспособленец(Flyweight) - шаблон предназначен для удешевления по потреблению
    памяти некоего компонента программы. Достигается это путём выноса тяжеловесных полей
    группы однотипных объектов в отдельный объект и использование его в рамках общего
    доступа, вместо использования в каждом объекте группы своей копии.
*/

struct rgb_color
{
    rgb_color(): red(std::byte(0x00)), green(std::byte(0x00)), blue(std::byte(0x00)) {}
    rgb_color(std::byte r, std::byte g, std::byte b):
        red(r), green(g), blue(b) {}
    /*
    rgb_color(const rgb_color & color)
    {
        red = color.red;
        green = color.green;
        blue = color.blue;
    }
    */
    std::byte red;
    std::byte green;
    std::byte blue;
};

struct picture
{
    picture()
    {
        data = new rgb_color[1000000];
    }
    ~picture() { delete data; }
    rgb_color * data;
};

// Белая и чёрная картинки - наш тяжеловесы, который будут использовать
// объекты легковесы
struct white_picture: public picture
{
    white_picture(): picture()
    {
        for(int i = 0; i < 1000000; i++)
            data[i] = rgb_color();
    }
};

struct black_picture: public picture
{
    black_picture(): picture()
    {
        for(int i = 0; i < 1000000; i++)
            data[i] = rgb_color(std::byte(0xff),std::byte(0xff),std::byte(0xff));
    }
};

enum class pic_color{ WHITE, BLACK };

class picture_factory
{
    static const picture * pictures[2];
public:
    picture_factory()
    {
        pictures[0] = new white_picture();
        pictures[1] = new black_picture();
    }
    ~picture_factory() { delete pictures[0], pictures[1]; }
    static const picture * get_picture(pic_color color) 
    {
        return color == pic_color::WHITE ?
            pictures[0] :
            pictures[1];
    }
};

struct color_flyweight
{
    color_flyweight(pic_color color): pic(picture_factory::get_picture(color)) {}
    void draw_nth_byte(size_t n)
    {
        std::cout << "N'th byte is "
            << static_cast<int>(pic->data[n].red)   << ' '
            << static_cast<int>(pic->data[n].green) << ' '
            << static_cast<int>(pic->data[n].blue)  << std::endl;
    }
private:
    const picture * pic;
};

int main()
{
    color_flyweight fl_white(pic_color::WHITE), fl_black(pic_color::BLACK);
    fl_white.draw_nth_byte(1);
    fl_black.draw_nth_byte(1);
    return 0;
}
