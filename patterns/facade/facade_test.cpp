#include <iostream>

/*
Фасад - шаблон, призванный скрыть от пользователя сложные интерфейс и внутреннее
    устройство некоторой системы, предоставив лишь минимальный набор необходимых функций.
*/

// Класс-фасад скрывает сложную трёхступенчатую процедуру создания исполняемого файла.
class CPP_compiler_facade
{
    struct CPP_compiler
    {
        struct abstract_syntax_tree;
        abstract_syntax_tree * process_frontend(const char * filename_and_options)
        {
            std::cout << "Processing frontend for given args: " << filename_and_options << std::endl;
            return nullptr;
        }
        const char * process_middlend(abstract_syntax_tree * tree)
        {
            std::cout << "Processing middlend: optimize given AST." << std::endl;
            return nullptr;
        }
        void process_backend(const char * temporary_bin_filename)
        {
            std::cout << "Processing backend. Generating executable from temporary binary files." << std::endl;
        }
    };
    CPP_compiler compiler;
public:
    CPP_compiler_facade(): compiler(){}
    void compile(const char * filename_and_options)
    {
        compiler.process_backend( compiler.process_middlend( compiler.process_frontend( filename_and_options ) ) );
    }
};

int main()
{
    CPP_compiler_facade facade;
    facade.compile("g++ -std=c++17 builder_test.cpp -o test.x");
    return 0;
}
