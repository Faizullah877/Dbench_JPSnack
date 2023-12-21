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
		uint16_t rept_{ 0 };
		uint32_t tick_{ 0 };
		vector<DbJPSnackInstruction> instructions_;



		
	};


}