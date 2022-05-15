#pragma once
#include "pch.hpp"

 

int s_main(HINSTANCE)
{
  ::Log<Console>::Write("hello");
     
 
    return 0;
};

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
int wWinMain(_In_ HINSTANCE hinst, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int){ return Invoke(s_main, hinst); };
int main() { return Invoke(s_main, (HINSTANCE)&__ImageBase); };


