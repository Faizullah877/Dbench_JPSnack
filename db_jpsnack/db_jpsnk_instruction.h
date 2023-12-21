#pragma once
#include "db_jumbf_lib.h"
#include "db_jpsnack_define.h"

using namespace std;
using namespace dbench;
class DbJPSnackInstruction
{
public:
	DbJPSnackInstruction();
	~DbJPSnackInstruction();
	void set_xo(uint32_t xo);
	uint32_t get_xo();
	void set_yo(uint32_t yo);
	uint32_t get_yo();

	void set_width(uint32_t w);
	uint32_t get_width();
	void set_height(uint32_t h);
	uint32_t get_height();

	void set_persistance(bool p);
	bool is_persitant();

	void set_life(uint32_t life);
	uint32_t get_life();

	void set_next_use(uint32_t n_u);
	uint32_t get_next_use();

	void set_xc(uint32_t xc);
	uint32_t get_xc();

	void set_yc(uint32_t yc);
	uint32_t get_yc();
	
	void set_wc(uint32_t wc);
	uint32_t get_wc();

	void set_hc(uint32_t hc);
	uint32_t get_hc();

	void set_rot(Rotation rot);
	Rotation get_rot();




private:
	uint32_t xo_{ 0 }; // horizontal offset
	uint32_t yo_{ 0 }; // vertical offset
	uint32_t width_{ 0 }; 
	uint32_t height_{ 0 };
	bool persist_{ 0 };
	uint32_t life_{ 0 };
	uint32_t next_use_{ 0 };
	uint32_t xc_{ 0 }; // horzontal crop offset
	uint32_t yc_{ 0 }; // vertical crop offset
	uint32_t wc_{ 0 }; // cropped width
	uint32_t hc_{ 0 }; // cropped height
	uint32_t rot_{ 0 }; // rotation

};

