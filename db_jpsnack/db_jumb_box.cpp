
#include "db_jumb_box.h"

namespace dbench {

	dbench::DbJumbBox::DbJumbBox()
	{
		set_box_type(BoxType::JUMB);
		is_superbox_ = true;
	}

	DbJumbBox::~DbJumbBox()
	{
		//set_box_size();
	}

	DbJumbBox::DbJumbBox(DbJumbDescBox ds_box)
	{
		set_box_type(BoxType::JUMB);
		is_superbox_ = true;
		set_jumbf_description_box(ds_box);
		set_box_size();
	}

	DbJumbBox::DbJumbBox(DbJumbDescBox ds_box, DbFreeBox fre_box)
	{
		set_box_type(BoxType::JUMB);
		is_superbox_ = true;
		set_jumbf_description_box(ds_box);
		set_free_box(fre_box);
		set_box_size();
	}

	void DbJumbBox::set_jumbf_description_box(DbJumbDescBox desc_box_in)
	{
		this->desc_box_ = desc_box_in;
		set_box_size();
	}

	void DbJumbBox::insert_content_box(DbBox box_in)
	{
		content_boxes_.push_back(box_in);
	}

	void DbJumbBox::set_free_box(DbFreeBox free_box)
	{
		padding_box_ = free_box;
		padding_box_present_ = true;
		set_box_size();
	}

	void DbJumbBox::set_box_size()
	{
		box_size_ = 8;
		box_size_ += desc_box_.get_box_size();
		for (auto& bx : content_boxes_) {
			box_size_ += bx.get_box_size();
		}
		if (padding_box_present_) {
			box_size_ += padding_box_.get_box_size();
		}

		if (box_size_ > MAX_32BIT_UINT_VALUE)
			box_size_ += (static_cast<uint64_t>(8)); // 8 xl_box


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

	JumbfContentType DbJumbBox::get_jumb_content_type()
	{
		return desc_box_.get_jumb_content_type();
	}

	void DbJumbBox::serialize(unsigned char** out_buf, uint64_t* out_buf_size)
	{
		set_box_size();

		*out_buf = new unsigned char[box_size_];
		*out_buf_size = box_size_;
		unsigned char* dst_buf_position = *out_buf;

		uint64_t bytes_done = 0;

		db_put_4byte(&dst_buf_position, lbox_);
		db_put_4byte(&dst_buf_position, tbox_);
		bytes_done += 8;
		if (xl_box_present_) {
			db_put_8byte(&dst_buf_position, xl_box_);
			bytes_done += 8;
		}

		// description box
		uint64_t desc_box_buf_size = 0;
		unsigned char* jumd_buf = nullptr;
		desc_box_.serialize(&jumd_buf, &desc_box_buf_size);
		memcpy_s(dst_buf_position, box_size_, jumd_buf, desc_box_buf_size);
		dst_buf_position += desc_box_buf_size;
		delete[] jumd_buf;
		bytes_done += desc_box_buf_size;

		// content boxes
		for (auto& bx : content_boxes_) {
			unsigned char* box_buf{ nullptr };
			uint64_t box_size{ 0 };
			bx.serialize(&box_buf, &box_size);
			memcpy_s(dst_buf_position, box_size_, box_buf, box_size);
			dst_buf_position += box_size;
			delete[] box_buf;
			bytes_done += box_size;
		}

		if (padding_box_present_) {
			unsigned char* free_box_buf{ nullptr };
			uint64_t free_box_size{ 0 };
			padding_box_.serialize(&free_box_buf, &free_box_size);
			memcpy_s(dst_buf_position, box_size_, free_box_buf, free_box_size);
			dst_buf_position += free_box_size;
			delete[] free_box_buf;
			bytes_done += free_box_size;
		}

		if (bytes_done != box_size_) {
			throw std::runtime_error("Error: Serializing Codestream Content JUMBF, sizes not matches.");
		}
	}
	void DbJumbBox::deserialize(unsigned char* in_box_buf, uint64_t in_buf_size)
	{
		uint64_t header_size{ 8 };
		uint64_t bytes_remaining = in_buf_size;

		unsigned char* buf = in_box_buf;

		lbox_ = db_get_4byte(&buf);
		tbox_ = db_get_4byte(&buf);
		box_type_ = db_identify_box_type(tbox_);
		if (box_type_ != BoxType::JUMB) {
			throw std::runtime_error("Error: De-Serializing JUMB, input buffer is not JUMB buffer.");
			return;
		}
		bytes_remaining -= 8;
		if (lbox_ == 1) {
			xl_box_ = db_get_8byte(&buf);
			xl_box_present_ = true;
			header_size += 8;
			box_size_ = xl_box_;
			bytes_remaining -= 8;
		}
		else if (lbox_ == 0) {
			box_size_ = in_buf_size;
		}
		else
			box_size_ = lbox_;

		DbJumbDescBox* desc_box = new DbJumbDescBox;
		desc_box->deserialize(buf, bytes_remaining);
		desc_box_ = *desc_box;
		buf += desc_box->get_box_size();

		bytes_remaining -= desc_box->get_box_size();

		while (bytes_remaining > 0)
		{
			DbBox* box = new DbBox;
			box->deserialize(buf, bytes_remaining);
			bytes_remaining -= box->get_box_size();
			buf += box->get_box_size();
			if (box->get_box_type() == BoxType::FREE) {
				uint64_t no_of_free_bytes{ 0 };
				DbFreeBox* free_box = new DbFreeBox;
				if(box->get_lbox() == 1){
					no_of_free_bytes = box->get_box_size() - 16;
				}
				else {
					no_of_free_bytes = box->get_box_size() - 8;
				}
				free_box->set_box(no_of_free_bytes);
				padding_box_ = *free_box;
				padding_box_present_ = true;
			}
			else {
				this->insert_content_box(*box);
			}
		}
	}
}