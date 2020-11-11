export module module_test;

//export template<typename T> module_add(T a, T b) -> decltype(a+b)
//export template<typename T> T module_add(T a, T b)
export int module_add(int a, int b)
{
    return a+b;
}
