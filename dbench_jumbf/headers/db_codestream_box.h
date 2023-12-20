#pragma once

#include "db_box.h"
#include "db_define.h"

namespace dbench {

	class DbCodestreamBox : public DbBox
	{
	public:
		DbCodestreamBox();
		~DbCodestreamBox();

		DbCodestreamBox(unsigned char* codestream_data, uint64_t codestream_data_size);
		void set_box(unsigned char* codestream_data, uint64_t codestream_data_size);
	};



}