#include "db_instruction_set_box.h"

namespace dbench {
DbInstSetBox::DbInstSetBox()
{
	set_box_type(BoxType::INST);
}

DbInstSetBox::~DbInstSetBox()
{
}

void DbInstSetBox::set_repetition(uint16_t rept_v)
{
	rept_ = rept_v;
}

void DbInstSetBox::set_tick(uint32_t t)
{
	tick_ = t;
}

void DbInstSetBox::set_xo_yo_flag(bool xo_yo_present)
{
	xo_yo_present_ = xo_yo_present;
	instructions_present_ = true;
}

void DbInstSetBox::set_width_height_flag(bool w_h_present)
{
	width_height_present_ = w_h_present;
	instructions_present_ = true;
}

void DbInstSetBox::set_persist_life_nextuse_flag(bool l_nu_p_present)
{
	life_nextuse_persist_present_ = l_nu_p_present;
	instructions_present_ = true;
}

void DbInstSetBox::set_crop_params_flag(bool crop_params_present)
{
	crop_params_present_ = crop_params_present;
	instructions_present_ = true;
}

void DbInstSetBox::set_rotation_flag(bool rot_present)
{
	rotation_present_ = rot_present;
	instructions_present_ = true;
}

void DbInstSetBox::insert_instruction(DbJPSnackInstruction* inst)
{
	instructions_ptrs_.push_back(inst);
	instructions_present_ = true;
}

void DbInstSetBox::generate_ityp()
{
	
	if (xo_yo_present_) { // switch rightmost (0th) bit ON)
		ityp_ = ityp_ | uint16_t(1);
	}
	if (width_height_present_) {// switch 2nd from right (1th) bit ON)
		ityp_ = ityp_ | uint16_t(2);
	}
	if (life_nextuse_persist_present_){// switch 4th from right bit ON)
		ityp_ = ityp_ | uint16_t(8);
	}
	if (crop_params_present_) {// switch 6th from right  bit ON)
		ityp_ = ityp_ | uint16_t(32);
	}
	if (rotation_present_) {// switch 7th from right  bit ON)
		ityp_ = ityp_ | uint16_t(64);
	}
}

void DbInstSetBox::set_box_size()
{
	box_size_ = 8; // lbox(4) + tbox(4);
	box_size_ += (static_cast<unsigned long long>(2 + 2) + 4); // ityp (2) + rept(2) + tick(4);
	if (instructions_present_) {
		for (auto i = 0; i < instructions_ptrs_.size(); i++) {
			if (xo_yo_present_) {
				box_size_ += 8;
			}
			if (width_height_present_) {
				box_size_ += 8;
			}
			if (life_nextuse_persist_present_) {
				box_size_ += 9; // 1 byte for persist
			}
			if (crop_params_present_) {
				box_size_ += 16;
			}
			if (rotation_present_) {
				box_size_ += 2;
			}
		}
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

void DbInstSetBox::serialize(unsigned char** out_buf, uint64_t* out_buf_size)
{
	set_box_size();		
	uint64_t buf_size_t = get_box_size();

	*out_buf = new unsigned char[buf_size_t];

	unsigned char* buf = *out_buf;
	uint32_t bytes_done = 0;
	db_put_4byte(&buf, lbox_);
	db_put_4byte(&buf, tbox_);
	bytes_done += 8;

	// putting xl_box field
	if (xl_box_present_) {
		db_put_8byte(&buf, xl_box_);
	}
	generate_ityp();
	db_put_2byte(&buf, ityp_);
	db_put_2byte(&buf, rept_);
	db_put_4byte(&buf, tick_);

	for (auto inst : instructions_ptrs_) {
		if (xo_yo_present_) {
			db_put_4byte(&buf, inst->get_xo());
			db_put_4byte(&buf, inst->get_yo());
		}
		if (width_height_present_) {
			db_put_4byte(&buf, inst->get_width());
			db_put_4byte(&buf, inst->get_height());
		}
		if (life_nextuse_persist_present_) {
			db_put_byte(&buf, inst->is_persitant());
			db_put_4byte(&buf, inst->get_life());
			db_put_4byte(&buf, inst->get_next_use());
		}
		if (crop_params_present_) {
			db_put_4byte(&buf, inst->get_xc());
			db_put_4byte(&buf, inst->get_yc());
			db_put_4byte(&buf, inst->get_wc());
			db_put_4byte(&buf, inst->get_hc());
		}
		if (rotation_present_) {
			db_put_2byte(&buf, inst->get_rot_value());
		}
	}


}

}