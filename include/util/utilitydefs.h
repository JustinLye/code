//Determine the operating system
//If the operating system cannot be determined
//a preprocessor error is invoked.

#if !defined(IS_WINDOWS) && !defined(IS_LINUX)
    #if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
        #define IS_WINDOWS
    #elif defined(linux) || defined(unix) || defined(_linux) || defined(__linux) || defined(__linux__) || defined(_UNIX)
        #define IS_LINUX
    #else
        #error OS not defined
    #endif
#endif

//modified solution taken from: https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
#if !defined(JL_FILENAME) // JL_FILENAME removes the directory path from __FILE__ leaving just the file name
    #include<string>
    #if defined(IS_WINDOWS)
        #define JL_FILENAME ((strrchr(__FILE__, '\\')) ? strrchr(__FILE__, '\\') + 1 : __FILE__)
    #elif defined(IS_LINUX)
       #define JL_FILENAME ((strrchr(__FILE__, '/')) ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #else
       #error OS not defined
    #endif
#endif

#if defined(MAKEDLL)
    #define DLLEXPORT __declspec(dllexport)
#else
    #define DLLEXPORT __declspec(dllimport)
#endif //DLLEXPORT

//Get system error is a method to quickly retrieve a system error
#if !defined(GET_SYSTEM_ERROR)
    #if defined(IS_WINDOWS)
        #if !defined(FormatMessage)
            #include<Windows.h>
        #endif
        #define GET_SYSTEM_ERROR(errorCode, pBuffer) \
                    FormatMessage( \
                        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, \
                        nullptr, \
                        errorCode, \
                        0, \
                        (LPSTR)&pBuffer, \
                        0, \
                        nullptr \
                    )
    #elif defined(IS_LINUX)
        #include<errno.h>
        #include<string.h>
        #define GET_SYSTEM_ERROR(Error_code, Buffer) \
                    strerror_r(Error_code, NULL, 0)
    #else
        #error OS not defined
    #endif
#endif //GET_SYSTEM_ERROR

//FILE_TO_STR reads content of file into a string
#if !defined(FILE_TO_CSTR)
    #include<string>
    #include<fstream>
    #include<sstream>
    #include<stdexcept>
    #define FILE_TO_CSTR(Filepath, File_content) \
    { \
        File_content.clear(); \
	std::ifstream File_stream; \
	std::stringstream File_string_stream; \
	File_stream.exceptions(std::ifstream::badbit); \
	try { \
		File_stream.open(Filepath); \
		File_string_stream << File_stream.rdbuf(); \
		File_stream.close(); \
		File_content = File_string_stream.str().c_str(); \
	} catch (std::ifstream::failure& e) { \
		File_content = ""; \
		throw std::runtime_error(e.what()); \
	} \
    }   
#endif

