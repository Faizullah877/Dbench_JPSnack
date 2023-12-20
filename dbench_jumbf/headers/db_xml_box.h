#pragma once

#include "db_define.h"
#include "db_box.h"

namespace dbench {

	class DbXmlBox : public DbBox
	{
	public:
		DbXmlBox();
		~DbXmlBox();
		DbXmlBox(char* xml, uint64_t xml_size); 
		void set_box(char* xml, uint64_t xml_size);
	};

}