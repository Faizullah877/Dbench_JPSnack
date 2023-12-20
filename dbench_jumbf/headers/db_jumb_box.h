#pragma once

#include <list>
#include "db_define.h"
#include "db_box.h"
#include "db_jumd_box.h"
#include "db_free_box.h"

namespace dbench {
	class DbJumbBox : public DbBox
	{
	public:
		DbJumbBox();
		~DbJumbBox();
		DbJumbBox(DbJumbDescBox ds_box); 
		DbJumbBox(DbJumbDescBox ds_box, DbFreeBox fre_box);

		void set_jumbf_description_box(DbJumbDescBox desc_box_in);
		void insert_content_box(DbBox box_in);
		void set_free_box(DbFreeBox free_box);
		void set_box_size();
		JumbfContentType get_jumb_content_type();

		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);
		void deserialize(unsigned char* in_box_buf, uint64_t in_buf_size);

		DbJumbDescBox desc_box_;
		std::list<DbBox> content_boxes_;
		DbFreeBox padding_box_;
		bool padding_box_present_ = false;
	};

}