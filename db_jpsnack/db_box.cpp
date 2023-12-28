#include "db_box.h"

namespace dbench {
	DbBox::DbBox()
	{
	}

	DbBox::~DbBox()
	{

	}

	DbBox::DbBox(BoxType box_type_in)
	{
		set_box_type(box_type_in);
	}

	DbBox::DbBox(BoxType box_type_in, unsigned char* paylaod_ptr, uint64_t payload_size)
	{
		set_box_type(box_type_in);
		payload_ = paylaod_ptr;
		payload_size_ = payload_size;
		set_box_size();
	}

	void DbBox::set_box(BoxType box_type_in, unsigned char* paylaod_ptr, uint64_t payload_size)
	{
		set_box_type(box_type_in);
		payload_ = paylaod_ptr;
		payload_size_ = payload_size;
		set_box_size();
	}

	void DbBox::set_box(uint32_t box_type_in, unsigned char* paylaod_ptr, uint64_t payload_size)
	{
		set_tbox(box_type_in);
		payload_ = paylaod_ptr;
		payload_size_ = payload_size;
		set_box_size();
	}

	void DbBox::set_box_payload(unsigned char* paylaod_ptr, uint64_t paylaod_size)
	{
		payload_ = paylaod_ptr;
		payload_size_ = paylaod_size;
		set_box_size();
	}

	void DbBox::set_payload(unsigned char* paylaod_ptr)
	{
		payload_ = paylaod_ptr;
	}

	void DbBox::set_payload_size(uint64_t size)
	{
		payload_size_ = size;
	}


	uint32_t DbBox::get_lbox()
	{
		return this->lbox_;
	}

	void DbBox::set_tbox(uint32_t type)
	{
		this->tbox_ = type;
		this->box_type_ = db_identify_box_type(type);
	}
	uint32_t DbBox::get_tbox()
	{
		return this->tbox_;
	}

	void DbBox::set_box_type(BoxType type)
	{
		this->box_type_ = type;
		this->set_tbox(uint32_t(type));
	}
	BoxType DbBox::get_box_type()
	{
		return this->box_type_;
	}


	void DbBox::set_box_size()
	{
		box_size_ = 8 + payload_size_;
		if (box_size_ > MAX_32BIT_UINT_VALUE)
		{
			lbox_ = 1;
			xl_box_ = box_size_;
			xl_box_present_ = true;
		}
		else {
			lbox_ = static_cast<uint32_t>(box_size_);
			xl_box_present_ = false;
		}
	}

	uint64_t DbBox::get_box_size()
	{
		return this->box_size_;
	}


	bool DbBox::is_xl_box_present()
	{
		return this->xl_box_present_;
	}
	uint64_t DbBox::get_xl_box()
	{
		return this->xl_box_;
	}

	unsigned char* DbBox::get_payload()
	{
		return payload_;
	}

	uint64_t DbBox::get_payload_size()
	{
		uint64_t boxsize = get_box_size();
		if (xl_box_present_)
			return (boxsize - 16);
		else
			return (boxsize - 8);
	}

	void DbBox::serialize(unsigned char** out_buf, uint64_t* out_buf_size)
	{
		set_box_size();
		*out_buf_size = box_size_;
		*out_buf = new unsigned char[box_size_];

		uint64_t header_size = 8;
		unsigned char* buf = *out_buf;
		db_put_4byte(&buf, lbox_);
		db_put_4byte(&buf, tbox_);

		// putting xl_box field
		if (xl_box_present_) {
			db_put_8byte(&buf, xl_box_);
			header_size += 8;
		}
		memcpy_s(buf, box_size_, payload_, static_cast<rsize_t>(box_size_) - header_size);
	}

	void DbBox::deserialize(unsigned char* in_box_buf, uint64_t in_buf_size)
	{
		unsigned char* buf = in_box_buf;
		uint64_t header_size{ 8 };
		lbox_ = db_get_4byte(&buf);
		tbox_ = db_get_4byte(&buf);
		box_type_ = db_identify_box_type(tbox_);
		if (lbox_ == 1) {
			xl_box_ = db_get_8byte(&buf);
			xl_box_present_ = true;
			header_size += 8;
			box_size_ = xl_box_;
		}
		else if (lbox_ == 0) {
			box_size_ = in_buf_size;
		}
		else
			box_size_ = lbox_;

		payload_ = buf;
		payload_size_ = box_size_ - header_size;
	}

}