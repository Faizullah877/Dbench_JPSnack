#pragma once

#include "db_define.h"
#include "db_box.h"
#include "db_uuid_box.h"
#include "db_jumb_box.h"



namespace dbench {

	class DbUuidJumbBox : public DbJumbBox
	{
	public:
		DbUuidJumbBox();
		~DbUuidJumbBox();
		DbUuidJumbBox(DbUuidBox uuid_box);
		DbUuidJumbBox(DbUuidBox uuid_box, DbFreeBox pading_box);
		DbUuidJumbBox(DbJumbDescBox desc_box);
		DbUuidJumbBox(DbJumbDescBox desc_box, DbUuidBox uuid_box);

		void set_content_box(DbUuidBox uuid_box);
		void set_description_box(bool requestable, std::string label, bool id_present, uint32_t id, unsigned char* hash, DbBox* private_box);

		void set_box_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);


	private:
		DbUuidBox uuid_content_box_;
	};
}