#include <iostream>
#include <string>

/*
Строитель - шаблон используется в случае, когда необходима сложная поэтапная инициализация
    некоторого объекта, притом на выходе могут получиться разные по функциональности и внутреннему
    устройству объекты.
*/

enum class BACKEND_LANGS
{
    GO, C_SHARP, HASKELL
};

enum class FRONTEND_LANGS
{
    JAVASCRIPT, TYPESCRIPT, WEBASSEMBLY
};

class web_app
{
    std::string app_type;
public:
    web_app(std::string type): app_type(type){}
    void about() { std::cout << "My application type is " << app_type << std::endl; }
};


class web_builder
{
protected:
    std::string backend_lang;
    std::string frontend_lang;
    void about()
    {
        std::cout << "We use " << backend_lang << " as backend and " << frontend_lang << " as frontend." << std::endl;
    }
public:
    web_builder(): backend_lang(), frontend_lang(){}
    virtual web_app * build() = 0;
    virtual void set_frontend(std::string front) { frontend_lang = front; }
    virtual void set_backend(std::string back) { backend_lang = back; }
    virtual ~web_builder() = default;
};

class home_bulder: public web_builder
{
public:
    home_bulder(): web_builder()
    {
        backend_lang = "PHP";
        frontend_lang = "JavaScript";
    }
    virtual web_app * build() override
    {
        web_app * app = new web_app("Home Project");
        about();
        return app;
    }
    virtual ~home_bulder() = default;
};

class enterprise_bulder: public web_builder
{
    size_t price;
public:
    enterprise_bulder(): web_builder(), price(0) {}
    virtual web_app * build() override
    {
        web_app * app = new web_app("Enterprise Project");
        about();
        std::cout << "We make this small application just for " << price << " billion dollars." << std::endl;
        return app;
    }
    virtual void set_frontend(std::string front) override
    {
        web_builder::set_frontend(front);
        price += 10;
    }
    virtual void set_backend(std::string front) override
    {
        web_builder::set_backend(front);
        price += 5;
    }
    virtual ~enterprise_bulder() = default;
};

class hipster_bulder: public web_builder
{
public:
    virtual web_app * build() override
    {
        web_app * app = new web_app("MY BEST UNIQUE PROJECT EVER!!!!");
        about();
        return app;
    }
    virtual ~hipster_bulder() = default;
};

// Директор - класс, который предоставляет быстрый доступ 
// для создания самых популярных вариантов конфигурации.
class director
{
public:
    static web_app * web_app_home_variant()
    {
        home_bulder builder;
        return builder.build();
    }
    static web_app * web_app_enterprise_variant(BACKEND_LANGS backend, FRONTEND_LANGS frontend)
    {
        enterprise_bulder builder;

        if(backend == BACKEND_LANGS::GO)
            builder.set_backend("Go");
        else if(backend == BACKEND_LANGS::C_SHARP)
            builder.set_backend("C#");
        else
            builder.set_backend("Java");

        if(frontend == FRONTEND_LANGS::WEBASSEMBLY)
            builder.set_frontend("WebAssembly");
        else if(frontend == FRONTEND_LANGS::TYPESCRIPT)
            builder.set_frontend("TypeScript");
        else
            builder.set_frontend("Javascript");

        return builder.build();
    }
    static web_app * web_app_hipster_variant(BACKEND_LANGS backend)
    {
        hipster_bulder builder;

        if(backend == BACKEND_LANGS::GO)
            builder.set_backend("Go");
        else
            builder.set_backend("Haskell");

        builder.set_frontend("WebAssembly");

        return builder.build();
    }
};

int main()
{
    web_app * app1 = director::web_app_home_variant(),
            * app2 = director::web_app_enterprise_variant(BACKEND_LANGS::GO, FRONTEND_LANGS::TYPESCRIPT),
            * app3 = director::web_app_hipster_variant(BACKEND_LANGS::C_SHARP);
    app1->about(); app2->about(); app3->about();
    delete app1, app2, app3;
    return 0;
}
