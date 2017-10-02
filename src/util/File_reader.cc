#include"File_reader.h"

File_reader* File_reader::Instance_ptr = nullptr;

File_reader::File_reader()
{

}

File_reader::~File_reader()
{

}

void File_reader::file_to_string(const char* File_path, std::string& File_content)
{
	std::lock_guard<std::mutex> Locker(Read_mtx);
	File_content.clear();
	std::ifstream Input_file;
	std::stringstream File_str_stream;
	Input_file.exceptions(std::ifstream::badbit);
	Input_file.open(File_path);
	if (!Input_file)
	{
		throw std::runtime_error("Input file could not be opened");
	}
	File_str_stream << Input_file.rdbuf();
	Input_file.close();
	File_content = File_str_stream.str();
}

File_reader* File_reader::file_reader()
{
	if (Instance_ptr == nullptr)
		Instance_ptr = new File_reader;
	return Instance_ptr;
}