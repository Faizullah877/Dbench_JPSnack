#include "db_jpsnack_jumbf.h"
namespace dbench {

DbJPSnackJumbBox::DbJPSnackJumbBox()
{
	desc_box_.set_content_type(JumbfContentType::JPSNACK);
	desc_box_.set_label("Dbench_JPEGSnack");
}

DbJPSnackJumbBox::~DbJPSnackJumbBox()
{
}
void DbJPSnackJumbBox::set_jpsnk_desc_box(DbJPSnackDescBox *jpsnk_desc_box)
{
	jpsnk_desc_box_ptr_ = jpsnk_desc_box;
}
void DbJPSnackJumbBox::set_jpsnk_inst_box(DbInstSetBox* inst_box)
{
	jpsnk_inst_box_ptr_ = inst_box;
}
void DbJPSnackJumbBox::insert_object_metadata_box(DbObjMetaDataBox* obj_mdata_box)
{
	obj_mdata_boxes_.push_back(obj_mdata_box);
}
void DbJPSnackJumbBox::set_box_size()
{
	box_size_ = 8;
	box_size_ += desc_box_.get_box_size();
	box_size_ += jpsnk_desc_box_ptr_->get_box_size();
	box_size_ += jpsnk_inst_box_ptr_->get_box_size();
	for (auto md_box : obj_mdata_boxes_) {
		box_size_ += md_box->get_box_size();
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
uint64_t DbJPSnackJumbBox::get_box_size()
{
	set_box_size();
	return box_size_;
}
void DbJPSnackJumbBox::serialize(unsigned char** out_buf, uint64_t* out_buf_size)
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

	unsigned char* jpsnk_desc_box_buf{ nullptr };
	uint64_t jpsnk_desc_buf_size{ 0 };
	jpsnk_desc_box_ptr_->serialize(&jpsnk_desc_box_buf, &jpsnk_desc_buf_size);
	memcpy_s(dst_buf_position, box_size_, jpsnk_desc_box_buf, jpsnk_desc_buf_size);
	dst_buf_position += jpsnk_desc_buf_size;
	delete[] jpsnk_desc_box_buf;
	bytes_done += jpsnk_desc_buf_size;

	unsigned char* jpsnk_inst_box_buf{ nullptr };
	uint64_t jpsnk_inst_buf_size{ 0 };
	jpsnk_inst_box_ptr_->serialize(&jpsnk_inst_box_buf, &jpsnk_inst_buf_size);
	memcpy_s(dst_buf_position, box_size_, jpsnk_inst_box_buf, jpsnk_inst_buf_size);
	dst_buf_position += jpsnk_inst_buf_size;
	delete[] jpsnk_inst_box_buf;
	bytes_done += jpsnk_inst_buf_size;


	for (auto mdata_box : obj_mdata_boxes_) {
		unsigned char* mdata_box_buf{ nullptr };
		uint64_t mdata_buf_size{ 0 };
		mdata_box->serialize(&mdata_box_buf, &mdata_buf_size);
		memcpy_s(dst_buf_position, box_size_, mdata_box_buf, mdata_buf_size);
		dst_buf_position += mdata_buf_size;
		delete[] mdata_box_buf;
		bytes_done += mdata_buf_size;
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
}