#include<iostream>
#include<iomanip>
#include<string>
#include<sstream>

#if !defined(__JL_MESSAGE_HEADER__)
#define __JL_MESSAGE_HEADER__
#include"utilitydefs.h"

namespace jl {

	struct Message_source {
		const char* File_name;
		const char* Function_name;
		int Line_number;
		int Thread_id;
		DLLEXPORT Message_source(
			const char* File = "NULL",
			const char* Function = "NULL",
			const int& Line = 0
		);
		DLLEXPORT friend std::ostream& operator<<(std::ostream& o, const Message_source& mb);
	};

	class Message {
	public:
		DLLEXPORT Message() {}
		DLLEXPORT Message(const Message_source& Msgb) : Msg_blck(Msgb) {}
		DLLEXPORT operator std::string();
		DLLEXPORT friend std::ostream& operator<<(std::ostream& o, const Message& m);
	protected:
		Message_source Msg_blck;
		
		DLLEXPORT virtual const char* type() const = 0;
		DLLEXPORT virtual const char* detail() const = 0;
		DLLEXPORT virtual void output(std::ostream& o) const;
	};

	class Info_message : public Message {
	public:
		DLLEXPORT Info_message() : Message(), Message_desc("NULL") {}
		DLLEXPORT Info_message(const jl::Message_source& mb, const char* Desc = "NULL") :
			Message(mb),
			Message_desc(Desc) {}
	protected:
		const char* Message_desc;
		DLLEXPORT virtual const char* type() const;
		DLLEXPORT virtual const char* detail() const;
	};

	class System_error_message : public Message {
	public:
		DLLEXPORT System_error_message();
		DLLEXPORT System_error_message(const jl::Message_source& mb, const int& Error_code);
	protected:
		int System_error_code;
		const char* System_error_desc;
		DLLEXPORT virtual const char* type() const;
		DLLEXPORT virtual const char* detail() const;
	};

	class Application_error_message : public Info_message {
	public:
		DLLEXPORT Application_error_message();
		DLLEXPORT Application_error_message(const jl::Message_source& mb, const char* Desc = "NULL");
	protected:
		DLLEXPORT virtual const char* type() const;

	};

} //jl namspace
#endif
