#pragma once
#include <vector>
#include "db_jumbf_lib.h"
#include "db_jpsnk_instruction.h"

using namespace std;
namespace dbench {

	class DbInstSetBox : public DbBox
	{
	public:
		DbInstSetBox();
		~DbInstSetBox();

	private:
		uint16_t ityp_{ 0 };
		bool instructions_present_{ false };
		bool xo_yo_present_{ false };
		bool width_height_present_{ false };
		bool life_nextuse_persis_present_{ false };
		bool crop_params_present_{ false };
		bool rotation_present_{ false };
		uint16_t rept_{ 0 };
		uint32_t tick_{ 0 };
		vector<DbJPSnackInstruction> instructions_;


		
	};


}