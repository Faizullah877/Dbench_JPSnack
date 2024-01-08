#pragma once
#include <iostream>
#include <string>
#include <list>
#include "db_jpsnk_instruction.h"
#include "db_jpsnk_obmb.h"

using namespace std;
using namespace dbench;

class JPSnackObject
{
public:
	JPSnackObject();
	~JPSnackObject();
	DbObjMetaDataBox meta;

	uint8_t object_id{ 0 };
	uint16_t rept_{ 0 };
	uint32_t tick_{ 0 };

	list<string> media_paths;

	DbJPSnackInstruction inst;

};

