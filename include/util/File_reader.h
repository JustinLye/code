#ifndef __FILE_READER_H_INCLUDED__
#define __FILE_READER_H_INCLDUED__

#include<string>
#include<fstream>
#include<sstream>
#include<mutex>

class File_reader
{
public:
	void file_to_string(const char* File_path, std::string& File_content);
	static File_reader* file_reader();
private:
	File_reader();
	File_reader(const File_reader&) {}
	File_reader(File_reader&&) {}
	~File_reader();
	static File_reader* Instance_ptr;
	std::mutex Read_mtx;
};

#endif