#pragma once  

#ifdef MATHLIBRARY_EXPORTS  
#define MATHLIBRARY_API __declspec(dllexport)   
#else  
#define MATHLIBRARY_API __declspec(dllimport)   
#endif  

// This class is exported from the MathLibrary.dll  
 
	// Returns a + b  
	MATHLIBRARY_API int Add(int a, int b);  

	// Returns a * b  
	MATHLIBRARY_API int Multiply(int a, int b);  

	// Returns a + (a * b)  
	MATHLIBRARY_API int AddMultiply(int a, int b);  
