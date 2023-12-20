#pragma once
#include "db_define.h"
#include "db_box.h"
#include "db_bfdb_box.h"
#include "db_binary_data_box.h"
#include "db_jumb_box.h"

namespace dbench {

	class DbEmbdFileJumbBox : public DbJumbBox
	{
	public:
		DbEmbdFileJumbBox();
		~DbEmbdFileJumbBox();
		DbEmbdFileJumbBox(DbFileDescBox file_desc_bx, DbBinaryDataBox binary_box);
		DbEmbdFileJumbBox(DbJumbDescBox desc_box);
		DbEmbdFileJumbBox(DbJumbDescBox desc_box, DbFileDescBox file_desc_bx, DbBinaryDataBox binary_box);

		void set_content_box(DbFileDescBox file_desc_bx, DbBinaryDataBox binary_box);
		
		void set_description_box(bool requestable, std::string label, bool id_present, uint32_t id, unsigned char* hash, DbBox* private_box);

		void set_box_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

	private:

		DbFileDescBox file_desc_box_;
		DbBinaryDataBox binary_data_box_;
	};
}