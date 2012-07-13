#ifndef EXAMPLE_DLL_H
#define EXAMPLE_DLL_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BUILDING_EXAMPLE_DLL
#define EXAMPLE_DLL __declspec(dllexport)
#else
#define EXAMPLE_DLL __declspec(dllimport)
#endif

void  EXAMPLE_DLL hello(const char *s);

int EXAMPLE_DLL Double(int x);
void EXAMPLE_DLL CppFunc(void);

#ifdef __cplusplus
}
#endif

// NOTE: this function is not declared extern "C"

// NOTE: this class must not be declared extern "C"
class EXAMPLE_DLL MyClass
{
public:
        MyClass() {};
        virtual ~MyClass() {};
        void func(void);
};

#endif  // EXAMPLE_DLL_H