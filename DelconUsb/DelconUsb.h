#define EXAMPLE_DLL __declspec(dllexport)

extern "C"
{


	class EXAMPLE_DLL DelconUsb
	{
	public:
		DelconUsb();
		virtual ~DelconUsb();

	};


void EXAMPLE_DLL CppFunc(void);


}