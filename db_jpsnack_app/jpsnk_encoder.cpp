#include <iostream>
#include "jpsnk_encoder.h"
#include "jpsnk_cmd_params.h"
using namespace std;


Encoder::Encoder()
{
}

Encoder::~Encoder()
{
}

void Encoder::initiate(int argc, const char* argv[])
{
	for (int i = 2; i < argc; i++) {
		std::string arg = argv[i++];
		if (arg == opt_cfg_file) {
			cfg_file_name = argv[i];
			break;
		}
	}
	cfg_file.open(cfg_file_name.c_str(), fstream::in);

}

void Encoder::set_background_image_fname(std::string fname)
{
	background_image_fname = fname;
}

void Encoder::set_bg_img_fname_cfg_file()
{
	if(cfg_file.is_open())
	string line;
	do {
		std::getline(cfg_file, line);
		if (line.empty())
			continue;
		if (line.front() == '#') {
			continue;
		}
		else {
			if (line.find("default_image_path") != string::npos) {
				size_t pos = line.find(" = ");
				set_background_image_fname(line.substr(pos + 2));
				break;
			}
		}
	} while (1);
}

void Encoder::set_output_fname_cfg_file()
{
}
