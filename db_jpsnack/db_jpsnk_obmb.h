#pragma once
#include <string>
#include <list>

#include "db_box.h"


namespace dbench {

	class DbObjMetaDataBox : public DbBox
	{
	public:
		DbObjMetaDataBox();
		~DbObjMetaDataBox();

		void set_object_id(uint8_t id);
		void set_media_type(std::string mtype);
		void set_no_of_media(uint8_t no_m);
		void set_opacity(float opc);
		void set_style(std::string styl);
		void add_location(std::string loc);
		uint8_t get_object_id();
		uint8_t get_no_of_media();
		std::string get_media_type();


		void set_box_size();
		uint64_t get_box_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

	private:
		uint8_t toggle_{ 0 };
		uint8_t object_id_{ 0 };
		std::string media_type_{ "" };

		bool no_of_media_present_{ false };
		uint8_t no_of_media_{ 0 };
		
		bool opacity_present_{ false };
		float opacity_{ 0 };

		bool style_present_{ false };
		std::string style_{ "" };

		std::list<std::string> locations_;

		void set_toggle_byte();



	};




}