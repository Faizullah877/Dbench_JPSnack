#pragma once

#include "db_define.h"
#include "db_box.h"
#include "db_xml_box.h"
#include "db_jumb_box.h"



namespace dbench{

	class DbXmlJumbBox : public DbJumbBox
	{
	public:
		DbXmlJumbBox();
		~DbXmlJumbBox();
		DbXmlJumbBox(DbXmlBox xml_box);
		DbXmlJumbBox(DbXmlBox xml_box, DbFreeBox pading_box);
		DbXmlJumbBox(DbJumbDescBox desc_box);
		DbXmlJumbBox(DbJumbDescBox desc_box, DbXmlBox xml_box);

		void set_content_box(DbXmlBox xml_box);
		void set_description_box(bool requestable, std::string label, bool id_present, uint32_t id, unsigned char* hash, DbBox* private_box);

		void set_box_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

	private:
		DbXmlBox xml_content_box_;
		
	};
}