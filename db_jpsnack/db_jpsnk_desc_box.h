#pragma once
#include "db_box.h"

#include <iostream>
#include <list>

namespace dbench {

struct Composition
{
	uint8_t composition_id_{ 1 };
	uint8_t no_of_objects_{ 0 };
	std::list<uint8_t> objects_ids_;
};

class DbJPSnackDescBox : DbBox
{
public:
	DbJPSnackDescBox();
	~DbJPSnackDescBox();

	void set_start_time(uint64_t s_time);
	uint64_t get_start_time();
	void set_num_of_compositions(uint8_t no);
	uint8_t get_num_of_compositions();
	bool is_num_of_composition_present();
	bool is_composition_id_present();
	void add_composition(Composition* c);
	void set_box(uint64_t start_time, uint8_t no_of_objects, std::list<uint8_t> obj_ids);
	void set_box_size();
	uint64_t get_box_size();
	void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

private:
	uint8_t version_{ 1 };
	uint64_t start_time_{ 0 };

	// Number of Composition is optional, that's why a flag is provided. 
	bool no_compositions_present_{ false };
	uint8_t no_compositions_{ 0 };
	bool composition_id_present_{ true };
	std::list<Composition*> compositions_; // this list will alway contain 1 composition as per specification of version 1. 
};


}