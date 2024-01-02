// db_jpsnack_app.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include <chrono>

#include "db_jpsnk_desc_box.h"
#include "db_jpsnk_instruction.h"
#include "db_jpsnk_inst_set_box.h"
#include "db_jpsnk_obmb.h"
#include "db_jpsnack_jumbf.h"
#include "jpsnk_cmd_params.h"



using namespace std;
using namespace dbench;

int main(int argc, const char* argv[])
{
	if (argc < 2) {
		cout << "Error: input arguments are not enough." << endl;
		print_usage();
		return -1;
	}
	try
	{
		auto start1 = chrono::high_resolution_clock::now();
		auto start_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
		WorkType task = WorkType::UNKNOWN;
		for (int i = 1; i < argc; i++) {
			std::string arg = argv[i];
			if (arg == opt_type_encoding) {
				task = WorkType::ENCODE;
				break;
			}
			else if (arg == opt_type_parse) {
				task = WorkType::PARSE;
				break;
			}
			else if (arg == "-h" || arg == "-help") {
				print_usage();
				exit(EXIT_SUCCESS);
			}
			else if (arg == "-v" || arg == "-version") {
				print_version();
				exit(EXIT_SUCCESS);
			}
		}

		if (task == WorkType::ENCODE) {
			string cfg_file{ "" };
			for (int i = 1; i < argc; i++) {

				std::string arg = argv[i++];
				if (arg == opt_cfg_file) {
					cfg_file = argv[i];
					break;
				}
			}





		}
		else if (task == WorkType::PARSE) {
			cout << "Parsing Functionality is not implemented yet." << endl;
		}
		else {
			cout << "Error: Unkown worktype." << endl;
			cout << "       Please provide switch \"-encode\" or \"-extract\"." << endl;
			print_usage();
		}

		auto finish = chrono::high_resolution_clock::now();
		auto elapsed = finish - start1;
		cout << "Process Time : " << dec << elapsed / std::chrono::milliseconds(1) / 1000.0 << " seconds" << endl;
		exit(EXIT_SUCCESS);

	}
	catch (const std::exception& e)
	{
		std::cout << " a standard exception was caught, with message '"
			<< e.what() << "'\n";
	}
	return 0;


	list<uint8_t> obj_ids;
	obj_ids.push_back(5);

	DbJPSnackDescBox jpsnk_desc_box;
	jpsnk_desc_box.set_box(2000, 1, obj_ids);

	DbJPSnackInstruction* inst = new DbJPSnackInstruction;
	inst->set_xo_yo(0, 0);
	inst->set_width_height(512, 256);
	inst->set_persist_life_nextuse(0, 12, 0);

	DbInstSetBox inst_set_box;
	inst_set_box.set_repetition(1);
	inst_set_box.set_tick(1000);
	inst_set_box.set_xo_yo_flag(true);
	inst_set_box.set_width_height_flag(true);
	inst_set_box.set_persist_life_nextuse_flag(true);
	inst_set_box.insert_instruction(inst);


	DbObjMetaDataBox box;

	box.set_object_id(5);
	box.set_media_type("image/jpg");
	box.set_no_of_media(6);
	box.add_location("self#jumbf=Object1");
	box.add_location("self#jumbf=Object2");
	box.add_location("self#jumbf=Object3");
	box.add_location("self#jumbf=Object4");
	box.add_location("self#jumbf=Object5");
	box.add_location("self#jumbf=Object6");

	DbJPSnackJumbBox jumbf_box;
	jumbf_box.set_jpsnk_desc_box(&jpsnk_desc_box);
	jumbf_box.set_jpsnk_inst_box(&inst_set_box);
	jumbf_box.insert_object_metadata_box(&box);

	unsigned char* jumbf_buf{ nullptr };
	uint64_t jumbf_buf_size{ 0 };
	jumbf_box.serialize(&jumbf_buf, &jumbf_buf_size);

	delete[] jumbf_buf;


	std::cout << "Hello World!\n";
	return 0;
}
