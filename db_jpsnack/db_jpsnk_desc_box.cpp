#include "db_jpsnk_desc_box.h"

DbJPSnackDescBox::DbJPSnackDescBox()
{
	set_tbox(0x6a736462); // jsdb = jpeg snack description box
}

DbJPSnackDescBox::~DbJPSnackDescBox()
{
}

void DbJPSnackDescBox::set_start_time(uint64_t s_time)
{
	start_time_ = s_time;
}

uint64_t DbJPSnackDescBox::get_start_time()
{
	return start_time_;
}

void DbJPSnackDescBox::set_num_of_compositions(uint8_t no)
{
	if (no == 0) {
		no_compositions_ = 0;
		no_compositions_present_ = false;
	}
	else {
		no_compositions_ = no;
		no_compositions_present_ = true;
	}
}

uint8_t DbJPSnackDescBox::get_num_of_compositions()
{
	return no_compositions_;
}

bool DbJPSnackDescBox::is_num_of_composition_present()
{
	return no_compositions_present_;
}

void DbJPSnackDescBox::add_composition(Composition* c)
{
	if (compositions_.size() > 0) {
		std::cout << "Error: More than 1 compositions is not supported." << std::endl;
	}
	compositions_.push_back(c);
	no_compositions_++;

	if (!no_compositions_present_)
		no_compositions_present_ = true;

}

// set box with only one composition 
void DbJPSnackDescBox::set_box(uint8_t ver, uint64_t start_time, uint8_t composition_id, uint8_t no_of_objects, std::list<uint8_t> obj_ids)
{
	if (ver != 1) {
		throw std::runtime_error("Error: Version Number other than 1 is not allowed.");
	}
	version_ = ver;
	start_time_ = start_time;
	no_compositions_present_ = false;
	Composition* comp = new Composition;
	comp->composition_id_ = composition_id;
	comp->no_of_objects_ = no_of_objects;
	for (auto id : obj_ids) {
		comp->objects_ids_.push_back(id);
	}
	compositions_.push_back(comp);
	set_box_size();
}

void DbJPSnackDescBox::set_box_size()
{
	box_size_ = 17; //lbox(4bytes) + tbox(4bytes) + version (1byte) + start time (8bytes)
	if (no_compositions_present_)
		box_size_ += 1;

	for (auto comp : compositions_) {
		box_size_ += 2; // (composition Id(1 byte) + number of objects (1byte)
		for (auto ob_id : comp->objects_ids_) {
			box_size_++;
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
void DbJPSnackDescBox::serialize(unsigned char** out_buf, uint64_t* out_buf_size)
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

	db_put_byte(&buf, version_);
	db_put_8byte(&buf, start_time_);
	for (auto comp : compositions_) {
		db_put_byte(&buf, comp->composition_id_);
		db_put_byte(&buf, comp->no_of_objects_);
		for (auto id : comp->objects_ids_) {
			db_put_byte(&buf, id);
		}
	}
}

