#pragma once

#include "db_define.h"
#include "db_box.h"
#include "db_json_box.h"
#include "db_jumb_box.h"



namespace dbench {

	class DbJsonJumbBox : public DbJumbBox
	{
	public:
		DbJsonJumbBox();
		~DbJsonJumbBox();
		DbJsonJumbBox(DbJsonBox json_box);
		DbJsonJumbBox(DbJsonBox json_box, DbFreeBox pading_box);
		DbJsonJumbBox(DbJumbDescBox desc_box);
		DbJsonJumbBox(DbJumbDescBox desc_box, DbJsonBox json_box);

		void set_content_box(DbJsonBox json_box);
		void set_description_box(bool requestable, std::string label, bool id_present, uint32_t id, unsigned char* hash, DbBox* private_box);

		void set_box_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);
	private:
		DbJsonBox json_content_box_;

	};
}