#pragma once

#include "db_define.h"
#include "db_box.h"
#include "db_cbor_box.h"
#include "db_jumb_box.h"



namespace dbench {

	class DbCborJumbBox : public DbJumbBox
	{
	public:
		DbCborJumbBox();
		~DbCborJumbBox();
		DbCborJumbBox(DbCborBox cbor_box);
		DbCborJumbBox(DbCborBox cbor_box, DbFreeBox pading_box);
		DbCborJumbBox(DbJumbDescBox desc_box);
		DbCborJumbBox(DbJumbDescBox desc_box, DbCborBox cbor_box);
		DbCborJumbBox(DbJumbDescBox desc_box, DbCborBox cbor_box, DbFreeBox padding_box);

		void set_content_box(DbCborBox cbor_box);
		void set_description_box(bool requestable, std::string label, bool id_present, uint32_t id, unsigned char* hash, DbBox* private_box);

		void set_box_size();

		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

	private:
		DbCborBox cbor_content_box_;
	};
}