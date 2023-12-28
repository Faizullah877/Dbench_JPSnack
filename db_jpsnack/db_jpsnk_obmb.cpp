#include "db_jpsnk_obmb.h"

namespace dbench {
DbObjMetaDataBox::DbObjMetaDataBox()
{
	set_box_type(BoxType::OBMB);
}

DbObjMetaDataBox::~DbObjMetaDataBox()
{
}
void DbObjMetaDataBox::set_object_id(uint8_t id)
{
	object_id_ = id;
}
void DbObjMetaDataBox::set_media_type(std::string mtype)
{
	media_type_ = mtype;
}
void DbObjMetaDataBox::set_no_of_media(uint8_t no_m)
{
	no_of_media_ = no_m;
	no_of_media_present_ = true;
}

void DbObjMetaDataBox::set_opacity(float opc)
{
	opacity_ = opc;
	opacity_present_ = true;
}

void DbObjMetaDataBox::set_style(std::string styl)
{
	style_ = styl;
	style_present_ = true;
}

void DbObjMetaDataBox::add_location(std::string loc)
{
	locations_.push_back(loc);
}

void DbObjMetaDataBox::set_box_size()
{
	box_size_ = 10; // lbox(4) + tbox(4)+ toggle(1(byte) + object id(1)
	box_size_ += static_cast<uint64_t>(media_type_.length()) + 1; // +1 for null char
	if (no_of_media_present_) {
		box_size_ += 1;
	}
	if (opacity_present_) {
		box_size_ += 4;
	}
	if (style_present_) {
		box_size_ += static_cast<uint64_t>(style_.length()) + 1; // +1 for null char
	}
	for (auto& loc : locations_) {
		box_size_+= static_cast<uint64_t>(loc.length()) + 1;
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

void DbObjMetaDataBox::serialize(unsigned char** out_buf, uint64_t* out_buf_size)
{
	set_box_size();
	uint64_t buf_size_t = get_box_size();

	*out_buf = new unsigned char[buf_size_t];

	unsigned char* buf = *out_buf;
	db_put_4byte(&buf, lbox_);
	db_put_4byte(&buf, tbox_);
	// putting xl_box field
	if (xl_box_present_) {
		db_put_8byte(&buf, xl_box_);
	}
	set_toggle_byte();
	db_put_byte(&buf, toggle_);
	db_put_byte(&buf, object_id_);
	for (int i = 0; i < int(media_type_.length()+1); i++) {
		db_put_byte(&buf, media_type_[i]);
	}

	if (no_of_media_present_) {
		db_put_byte(&buf, no_of_media_);
	}

	if (opacity_present_) {
		db_put_4byte(&buf, opacity_); // need to check
	}

	if (style_present_) {
		for (int i = 0; i < int(style_.length() + 1); i++) {
			db_put_byte(&buf, style_[i]);
		}
	}

	for (auto& loc : locations_) {
		for (int i = 0; i < int( loc.length() + 1); i++) {
			db_put_byte(&buf, loc[i]);
		}
	}
	*out_buf_size = buf_size_t;
}

void DbObjMetaDataBox::set_toggle_byte()
{
	if (no_of_media_present_) {
		toggle_ = toggle_ | uint8_t(1);
	}
	if (style_present_) {
		toggle_ = toggle_ | uint8_t(2);
	}
	if (opacity_present_) {
		toggle_ = toggle_ | uint8_t(4);
	}
}


}