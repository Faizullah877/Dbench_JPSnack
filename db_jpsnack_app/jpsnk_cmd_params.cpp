#include "jpsnk_cmd_params.h"
#include <iostream>
#include <iomanip>


void print_version()

{
	cout << "dbench_jpsnk version : v" << version_major << "." << version_minor << "." << version_patch << endl;
}

void print_usage() {
	print_version();
	cout << "Usage : db_jumbf_app.exe <options>" << endl;
	cout << "Options: " << endl;
	cout << "\t-encode                        Encoding/Generating JPEG Snack File (default)" << endl;
	// cout << "\t-parse                         Parse a .jumbf or .jpg file" << endl;
	cout << "\t-cfg_file      INPUT_CONFIG_FILENAME   Specify input configuration file name" << endl;
	cout << "\t										  .cfg, .jtxt" << endl;
	cout << "\t-o             OUTPUTFILENAME          Specify output file name. " << endl;
	cout << "\t                                       .jpg, .jpeg" << endl;

	cout << "\t-h                  Print usage." << endl;
	cout << "\t-help               Print usage." << endl;
	cout << "\t-v                  Print version." << endl;
	cout << "\t-version            Print version." << endl;


	cout << endl;
}