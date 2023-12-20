#pragma once

#include "db_define.h"
namespace dbench {
	class DbBox
	{
	public:
		DbBox();
		~DbBox();
		DbBox(BoxType box_type_in);
		DbBox(BoxType box_type_in, unsigned char* paylaod_ptr, uint64_t payload_size);
		void set_box(BoxType box_type_in, unsigned char* paylaod_ptr, uint64_t payload_size);
		void set_box(uint32_t box_type_in, unsigned char* paylaod_ptr, uint64_t payload_size);
		void set_box_payload(unsigned char* paylaod_ptr, uint64_t paylaod_size);
		void set_payload(unsigned char* paylaod_ptr);
		void set_payload_size(uint64_t size);

		uint32_t get_lbox();

		void set_box_size();
		uint64_t get_box_size();

		void set_tbox(uint32_t);
		uint32_t get_tbox();

		void set_box_type(BoxType type);
		BoxType get_box_type();

		bool is_xl_box_present();
		uint64_t get_xl_box();

		unsigned char* get_payload();
		uint64_t get_payload_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);
		void deserialize(unsigned char* in_box_buf, uint64_t in_buf_size);

	protected:
		uint32_t lbox_{ 0 };
		uint32_t tbox_{ 0 };
		uint64_t box_size_{ 0 };
		BoxType box_type_{ BoxType::UNDEF };
		bool xl_box_present_{false};
		uint64_t xl_box_{ 0 };
		bool is_superbox_{ false };
		unsigned char* payload_{ nullptr };
		uint64_t payload_size_{ 0 };
	};
}

