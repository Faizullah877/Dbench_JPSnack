#pragma once
#include <string>
#include <sstream>
#include <fstream>

using namespace std;


constexpr unsigned int version_major = 1;
constexpr unsigned int version_minor = 1;
constexpr unsigned int version_patch = 0;


static const string opt_cfg_file = "-cfg_file";
static const std::string opt_output = "-o";
static const std::string opt_type_encoding = "-encode";
static const std::string opt_type_parse = "-parse";


enum class WorkType {
	ENCODE = 0,
	PARSE,
	UNKNOWN
};

void print_version();
void print_usage();