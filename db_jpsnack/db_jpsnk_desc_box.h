#pragma once
#include "db_jumbf_lib.h"

using namespace dbench;

class DbJPSnackDescBox : DbBox
{
public:
	DbJPSnackDescBox();
	~DbJPSnackDescBox();

	void set_start_time(uint64_t s_time);
	uint64_t get_start_time();
	void set_num_of_comp(uint8_t no);
	uint8_t get_num_of_comp();
	bool is_num_of_comp_present();

private:
	uint8_t version_{ 1 };
	uint64_t start_time_{ 0 };
	bool num_comp_present{ false };
	uint8_t num_comp{ 0 };
	

};

