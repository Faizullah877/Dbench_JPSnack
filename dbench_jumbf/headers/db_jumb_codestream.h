#pragma once

#include "db_define.h"
#include "db_box.h"
#include "db_codestream_box.h"
#include "db_jumb_box.h"



namespace dbench {

	class DbCodestreamJumbBox : public DbJumbBox
	{
	public:
		DbCodestreamJumbBox();
		~DbCodestreamJumbBox();
		DbCodestreamJumbBox(DbCodestreamBox codestream_box);
		DbCodestreamJumbBox(DbCodestreamBox codestream_box, DbFreeBox pading_box);
		DbCodestreamJumbBox(DbJumbDescBox desc_box);
		DbCodestreamJumbBox(DbJumbDescBox desc_box, DbCodestreamBox codestream_box);

		void set_content_box(DbCodestreamBox codestream_box);
		void set_description_box(bool requestable, std::string label, bool id_present, uint32_t id, unsigned char* hash, DbBox* private_box);

		void set_box_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

	private:
		DbCodestreamBox codestream_content_box_;
	};
}