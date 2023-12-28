#pragma once
#include "list"
#include "db_box.h"
#include "db_jpsnk_instruction.h"

using namespace std;
namespace dbench {

	class DbInstSetBox : public DbBox
	{
	public:
		DbInstSetBox();
		~DbInstSetBox();
		void set_repetition(uint16_t rept_v);
		void set_tick(uint32_t t);
		void set_xo_yo_flag(bool xo_yo_present);
		void set_width_height_flag(bool w_h_present);
		void set_persist_life_nextuse_flag(bool l_nu_p_present);
		void set_crop_params_flag(bool crop_params_present);
		void set_rotation_flag(bool rot_present);
		void insert_instruction(DbJPSnackInstruction* inst);

		void set_box_size();
		void serialize(unsigned char** out_buf, uint64_t* out_buf_size);

	private:
		uint16_t ityp_{ 0 };
		bool instructions_present_{ false };
		bool xo_yo_present_{ false };
		bool width_height_present_{ false };
		bool life_nextuse_persist_present_{ false };
		bool crop_params_present_{ false };
		bool rotation_present_{ false };
		uint16_t rept_{ 0 };
		uint32_t tick_{ 0 };
		list<DbJPSnackInstruction*> instructions_ptrs_;

		void generate_ityp();



		
	};


}