#include <iostream>
#include <string>

#include "jpsnk_encoder.h"
#include "jpsnk_cmd_params.h"
using namespace std;
using namespace dbench;


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

void Encoder::set_output_jpsnk_file_name(std::string fname)
{
	output_jpsnk_fname = fname;
}

void Encoder::set_bg_img_fname_cfg_file()
{
	set_background_image_fname(get_str_from_cfg_file_for("default_image_path"));
}

std::string Encoder::get_str_from_cfg_file_for(std::string search_str)
{
	std::string line;
	std::string value_str{ "" };
	if (!cfg_file.is_open()) {
		cfg_file.open(cfg_file_name.c_str(), fstream::in);
	}
	while (getline(cfg_file, line))
	{
		if (line.find(search_str) != std::string::npos) {
			size_t pos = line.find(" = ");
			value_str = line.substr(pos + 2);
			size_t a = value_str.find("#");
			if (a != std::string::npos) {
				value_str = value_str.substr(0, a);
			}
			break;
		}
	}
	return value_str;
}


void Encoder::set_no_of_object_value()
{
	string objNo_str = get_str_from_cfg_file_for("No_of_Objects");
	no_of_objects = uint8_t(stoul(objNo_str));
}

void Encoder::set_start_time_value()
{
	string s_time = get_str_from_cfg_file_for("start_time");
	start_time = stoul(s_time);;
}

void Encoder::set_objects_data()
{
	for (auto i = 0; i < no_of_objects; i++) {
		JPSnackObject* obj = new JPSnackObject;
		string str = get_str_from_cfg_file_for("ID ");
		obj->object_id = uint8_t(stoul(str));
		obj->meta.set_media_type(get_str_from_cfg_file_for("Media Type "));
		string style = get_str_from_cfg_file_for("Style");
		if(style != "NULL")
			obj->meta.set_style(style);
		str = get_str_from_cfg_file_for("Opacity");
		if (str != "NULL")
			obj->meta.set_opacity(stof(str));

		obj->meta.set_no_of_media(uint8_t(stoul(get_str_from_cfg_file_for("No. of Media"))));
		for (auto x = 0; x < obj->meta.get_no_of_media(); x++) {
			string str_s = "media file " + to_string(x) + "path ";
			obj->media_paths.push_back(get_str_from_cfg_file_for(str_s));
		}


	}
}



void Encoder::set_output_fname_cfg_file()
{
	set_output_jpsnk_file_name(get_str_from_cfg_file_for("jpsnk_file"));
}

void Encoder::set_number_of_objects(uint8_t no)
{
	no_of_objects = no;
}

