#include <iostream>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <vector>

#include "db_define.h"

namespace dbench {

	// n should be 1<=n<=8;
	bool isNthBitSet_1(unsigned char byte, int n)
	{
		if (n < 1 || n>8) {
			throw std::runtime_error("Error: Checking status of a bit in Byte, n should be 1<=n<=8.");
		}
		if ((byte >> (n - 1)) & 1)
			return true;
		else
			return false;
	}
	bool db_put_byte(unsigned char** dst_buf, char data)
	{

		**dst_buf = data;
		(*dst_buf)++;
		return true;
	}

	bool db_put_2byte(unsigned char** dst_buf, uint32_t data)
	{
		unsigned char temp_data = (unsigned char)(data >> 8);
		db_put_byte(dst_buf, temp_data);

		temp_data = (unsigned char)(data);
		db_put_byte(dst_buf, temp_data);

		return true;
	}

	bool db_put_4byte(unsigned char** dst_buf, uint32_t data)
	{
		unsigned char temp_data = (unsigned char)(data >> 24);
		db_put_byte(dst_buf, temp_data);

		temp_data = (unsigned char)(data >> 16);
		db_put_byte(dst_buf, temp_data);

		temp_data = (unsigned char)(data >> 8);
		db_put_byte(dst_buf, temp_data);
		temp_data = (unsigned char)(data);
		db_put_byte(dst_buf, temp_data);
		return true;
	}

	bool db_put_8byte(unsigned char** dst_buf, uint64_t value)
	{
		for (auto i = 7; i >= 0; i--) {
			unsigned char temp_data = (unsigned char)(value >> (8 * i));
			db_put_byte(dst_buf, temp_data);
		}
		return true;
	}

	unsigned char db_get_byte(unsigned char** buf)
	{
		unsigned char val;
		val = *(*buf)++;
		return val;
	}

	uint16_t db_get_2byte(unsigned char** buf)
	{
		int val1, val2;
		val1 = (db_get_byte(buf)) << 8;
		val2 = db_get_byte(buf);
		return val1 + val2;

	}

	uint32_t db_get_4byte(unsigned char** buf)
	{
		long val1, val2;
		val1 = (db_get_2byte(buf)) << 16;
		val2 = db_get_2byte(buf);

		return val1 + val2;
	}

	uint64_t db_get_8byte(unsigned char** buf)
	{
		uint64_t val1, val2;

		val1 = (static_cast<uint64_t>(db_get_4byte(buf))) << 32;
		val2 = static_cast<uint64_t>(db_get_4byte(buf));
		return val1 + val2;
	}

	unsigned char* db_get_jumbf_content_type_uuid(JumbfContentType type) {
		unsigned char* jumb_content_type_uuid = nullptr;
		//if (type == JumbfContentType::JPEG360)
		//{
		//	jumb_content_type_uuid = new unsigned char[16];
		//	unsigned char type_jpeg360[16] = { 0x78, 0x5F, 0x34, 0xB7, 0x5D, 0x4B, 0x47, 0x4C, 0xB8, 0x9F, 0x1D, 0x99, 0xE0, 0xE3, 0xA8, 0xDD };
		//	for (auto i = 0; i < 16; i++)
		//		jumb_content_type_uuid[i] = type_jpeg360[i];
		//}
		// else 
		if (type == JumbfContentType::CODESTREAM) {
			jumb_content_type_uuid = new unsigned char[16];
			unsigned char contiguous_codestream_type_uuid[16] = { 0x65, 0x79, 0xD6, 0xFB, 0xDB, 0xA2, 0x44, 0x6B, 0xB2, 0xAC, 0x1B, 0x82, 0xFE, 0xEB, 0x89, 0xD1 };
			for (auto i = 0; i < 16; i++)
				jumb_content_type_uuid[i] = contiguous_codestream_type_uuid[i];
		}
		else if (type == JumbfContentType::XML) {
			jumb_content_type_uuid = new unsigned char[16];
			unsigned char xml_content_type[16] = { 0x78, 0x6D, 0x6C, 0x20, 0x00, 0x11, 0x00, 0x10, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 };
			for (auto i = 0; i < 16; i++)
				jumb_content_type_uuid[i] = xml_content_type[i];
		}
		else if (type == JumbfContentType::JSON) {
			jumb_content_type_uuid = new unsigned char[16];
			unsigned char json_content_type[16] = { 0x6A, 0x73, 0x6F, 0x6E, 0x00, 0x11, 0x00, 0x10, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 };
			for (auto i = 0; i < 16; i++)
				jumb_content_type_uuid[i] = json_content_type[i];
		}
		else if (type == JumbfContentType::UUID) {
			jumb_content_type_uuid = new unsigned char[16];
			unsigned char uuid_content_type[16] = { 0x75, 0x75, 0x69, 0x64, 0x00, 0x11, 0x00, 0x10, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 };
			for (auto i = 0; i < 16; i++)
				jumb_content_type_uuid[i] = uuid_content_type[i];
		}
		//else if (type == JumbfContentType::JPEGSnack) {
		//	jumb_content_type_uuid = new unsigned char[16];
		//	unsigned char uuid_content_type[16] = { 0x16, 0xAD, 0x91, 0xE0, 0xA3, 0x7F, 0x11, 0xEB, 0x9D, 0x0D, 0x08, 0x00, 0x20, 0x0C, 0x9A, 0x66 };
		//	for (auto i = 0; i < 16; i++)
		//		jumb_content_type_uuid[i] = uuid_content_type[i];
		//}
		else if (type == JumbfContentType::EMBEDDED_File) {
			jumb_content_type_uuid = new unsigned char[16]; // 0x40CB0C32-BB8A-489D-A70B-2AD6F47F4369
			unsigned char uuid_content_type[16] = { 0x40, 0xCB, 0x0C, 0x32, 0xBB, 0x8A, 0x48, 0x9D, 0xA7, 0x0B, 0x2A, 0xD6, 0xF4, 0x7F, 0x43, 0x69 };
			for (auto i = 0; i < 16; i++)
				jumb_content_type_uuid[i] = uuid_content_type[i];
		}
		else if (type == JumbfContentType::CBOR) {
			jumb_content_type_uuid = new unsigned char[16]; // 0x63626F72-0011-0010-8000-00AA00389B71
			unsigned char uuid_content_type[16] = { 0x63, 0x62, 0x6F, 0x72, 0x00, 0x11, 0x00, 0x10, 0x80, 0x00, 0x00, 0xAA, 0x00, 0x38, 0x9B, 0x71 };
			for (auto i = 0; i < 16; i++)
				jumb_content_type_uuid[i] = uuid_content_type[i];
		}
		return jumb_content_type_uuid;
	}

	JumbfContentType db_identify_jumbf_content_type(unsigned char* type_16b)
	{
		unsigned char* orig = nullptr;

		orig = db_get_jumbf_content_type_uuid(JumbfContentType::CODESTREAM);
		if (memcmp(orig, type_16b, 16) == 0) {
			delete[] orig;
			return JumbfContentType::CODESTREAM;
		}
		orig = db_get_jumbf_content_type_uuid(JumbfContentType::XML);
		if (memcmp(orig, type_16b, 16) == 0) {
			delete[] orig;
			return JumbfContentType::XML;
		}

		orig = db_get_jumbf_content_type_uuid(JumbfContentType::JSON);
		if (memcmp(orig, type_16b, 16) == 0) {
			delete[] orig;
			return JumbfContentType::JSON;
		}

		orig = db_get_jumbf_content_type_uuid(JumbfContentType::UUID);
		if (memcmp(orig, type_16b, 16) == 0) {
			delete[] orig;
			return JumbfContentType::UUID;
		}

		orig = db_get_jumbf_content_type_uuid(JumbfContentType::EMBEDDED_File);
		if (memcmp(orig, type_16b, 16) == 0) {
			delete[] orig;
			return JumbfContentType::EMBEDDED_File;
		}

		orig = db_get_jumbf_content_type_uuid(JumbfContentType::CBOR);
		if (memcmp(orig, type_16b, 16) == 0) {
			delete[] orig;
			return JumbfContentType::CBOR;
		}

		//orig = db_get_jumbf_content_type_uuid(JumbfContentType::JPEG360);
		//if (memcmp(orig, type_16b, 16) == 0) {
		//	delete[] orig;
		//	return JumbfContentType::JPEG360;
		//}

		//orig = db_get_jumbf_content_type_uuid(JumbfContentType::JPEGSnack);
		//if (memcmp(orig, type_16b, 16) == 0) {
		//	delete[] orig;
		//	return JumbfContentType::JPEGSnack;
		//}
		delete[] orig;
		return JumbfContentType::UNDEF;
	}

	BoxType db_identify_box_type(uint32_t tbox)
	{
		BoxType type = BoxType::UNDEF;
		switch (tbox)
		{
		case 0x6a756d62:
			type = BoxType::JUMB;
			break;
		case 0x6a756d64:
			type = BoxType::JUMD;
			break;
		case 0X6A703263:
			type = BoxType::JP2C;
			break;
		case 0X786D6C20:
			type = BoxType::XML;
			break;
		case 0X6A736F6E:
			type = BoxType::JSON;
			break;
		case 0X75756964:
			type = BoxType::UUID;
			break;
		case 0x62696462:
			type = BoxType::BIDB;
			break;
		case 0x62666462:
			type = BoxType::BFDB;
			break;
		case 0x63626F72:
			type = BoxType::CBOR;
			break;
		case 0x66726565:
			type = BoxType::FREE;
			break;
		case 0x70726976:
			type = BoxType::PRIV;
			break;
		case 0x6A736462:
			type = BoxType::JSDB;
			break;
		case 0x696E7374:
			type = BoxType::INST;
			break;
		default:
			break;
		}
		return type;
	}

	int db_write_jumbf_buf_to_jpg_buf(unsigned char* jumbf_buf, uint64_t jumbf_size, unsigned char* input_jpg, uint64_t jpg_size, unsigned char** output_buf, uint64_t* output_buf_size)
	{
		unsigned short previous_jumb_en = 0;
		unsigned short previous_jumb_z = 1;
		unsigned short this_jumb_z = 1;
		if (input_jpg == nullptr || jumbf_buf == nullptr)
		{
			std::cout << "Error: Empty JPEG bufer or JUMBF buffer detected while embedding JUMBF Buffer." << std::endl;
			return false;
		}


		uint64_t jumb_header_size{ 8 };
		uint32_t JumbLbox = db_get_4byte(&jumbf_buf);
		uint32_t Tbox = db_get_4byte(&jumbf_buf);
		uint64_t jumb_xl_box{ 0 };
		if (JumbLbox == 1) {
			jumb_xl_box = db_get_8byte(&jumbf_buf);
			jumb_header_size += 8;
		}

		uint32_t size_per_marker = 65535;
		uint32_t app11_header_size = 10+jumb_header_size; //Le(2) + CI(2) + En(2) + Z(4) 
		uint32_t jumb_data_size_per_marker = size_per_marker - app11_header_size;
		uint32_t no_of_app11_required = static_cast<uint32_t>((jumbf_size / jumb_data_size_per_marker) + 1);
		*output_buf_size = jpg_size + jumbf_size + ((static_cast<uint64_t>(app11_header_size) + 2) * no_of_app11_required) - 8; // -8 Tbox and Lbox of Jumb already covered in header size;
		*output_buf = new unsigned char[*output_buf_size];

		unsigned char* dst_buf_position = *output_buf;

		bool meet_SOS = false;
		uint64_t output_buf_remaining_size = *output_buf_size;
		uint64_t jumb_buf_remaining_size = jumbf_size;

		jumb_buf_remaining_size -= jumb_header_size;
		unsigned char* jumb_payload = jumbf_buf;

		uint32_t length = 0;
		int expected_FF = 0, marker = 0;
		unsigned char* buf = input_jpg;
		uint32_t header_buf_size = 0;
		//int marker_count = 0;
		do {
			expected_FF = db_get_byte(&buf);
			header_buf_size++;
			if (expected_FF == 0xFF)
			{
				marker = db_get_byte(&buf);
				//cout << ++marker_count << "  : Marker : 0xFF" << hex << marker << endl;
				header_buf_size++;
				if (unsigned char(marker) == unsigned char(JpegMarker::M_SOI)) {
					continue;
				}
				else if (unsigned char(marker) == unsigned char(JpegMarker::M_EOI)) {
					std::cout << "Error: Pre-mature EOI." << std::endl;
					return -1;
				}
				else if (unsigned char(marker) == unsigned char(JpegMarker::M_APP11)) {
					// looks for already present APP11 markers and JUMB boxes
					length = db_get_2byte(&buf);
					unsigned short JP = db_get_2byte(&buf);
					unsigned short En = db_get_2byte(&buf);
					uint32_t Z = db_get_4byte(&buf);
					uint32_t Lbox = db_get_4byte(&buf);
					uint32_t Tbox = db_get_4byte(&buf);
					if (Tbox == uint32_t(0x6a756d62) && En == previous_jumb_en && Z == previous_jumb_z + 1) {
						// it is same jumb
						previous_jumb_z = Z;
					}
					else {
						//it is new jumbf
						previous_jumb_en = En;
					}
					header_buf_size += length;
					length -= 18;
					buf += length;
				}
				else if (unsigned char(marker) == unsigned char(JpegMarker::M_DQT)) { // write before Quantization tables
					buf -= 2;
					header_buf_size -= 2;
					memcpy_s(dst_buf_position, *output_buf_size, input_jpg, header_buf_size);
					dst_buf_position += header_buf_size;
					output_buf_remaining_size -= header_buf_size;
					uint32_t box_instance_num = previous_jumb_en + 1;

					for (uint32_t Z = 1; Z <= no_of_app11_required; Z++) {
						uint32_t this_marker_payload_size = jumb_data_size_per_marker;
						if (Z == no_of_app11_required)
							this_marker_payload_size = static_cast<uint32_t>(jumb_buf_remaining_size);

						int APP11_marker = 0xffeb; //APP11
						int common_identifier = 0x4A50; //'JP
						db_put_2byte(&dst_buf_position, APP11_marker);
						db_put_2byte(&dst_buf_position, this_marker_payload_size + app11_header_size);
						db_put_2byte(&dst_buf_position, common_identifier);
						db_put_2byte(&dst_buf_position, box_instance_num);
						db_put_4byte(&dst_buf_position, Z);
						db_put_4byte(&dst_buf_position, JumbLbox);
						db_put_4byte(&dst_buf_position, Tbox);
						if (JumbLbox == 1) {
							db_put_8byte(&dst_buf_position, jumb_xl_box);
						}

						memcpy_s(dst_buf_position, output_buf_remaining_size, jumb_payload, this_marker_payload_size);
						dst_buf_position += this_marker_payload_size; // advance position pointer to end of output buf.
						jumb_payload += this_marker_payload_size; // advance position for next marker data
						output_buf_remaining_size -= (static_cast<unsigned long long>(this_marker_payload_size) + app11_header_size + 2);
						jumb_buf_remaining_size -= this_marker_payload_size;
					}
					memcpy_s(dst_buf_position, output_buf_remaining_size, buf, (jpg_size - header_buf_size));
					meet_SOS = true;
				}
				else {
					length = db_get_2byte(&buf);
					header_buf_size += length;
					length -= 2;
					buf += length;
				}
			}
		} while (meet_SOS == false);
		jumbf_buf -= 8; // repositioning of pointer to start of buffer

		//delete[] jumbf_buf;
		return 0;
	}


	int db_extract_jumbf_bitstream(unsigned char* in_jpg_buf, uint64_t in_jpg_size, JumbfContentType type, unsigned char** jumb_buf, uint32_t* jumb_buf_size)
	{
		if (in_jpg_buf == nullptr) {
			return -1;
		}
		std::vector<unsigned char> codestream_data; ///concatenated
		unsigned char* data = in_jpg_buf;
		unsigned char last = db_get_byte(&data);
		unsigned char current = db_get_byte(&data);
		if (last != 0xFF || current != unsigned char(JpegMarker::M_SOI)) {
			std::cout << "Image is not JPEG" << std::endl;
			return -1;
		}
		last = db_get_byte(&data);
		current = db_get_byte(&data);
		uint32_t previous_En = 1;
		uint32_t previous_Z = 0;
		unsigned Lbox = 0;
		bool is_requested_jumbf = false;
		//reading markers;
		while (1)
		{
			if (last != 0xFF)
			{
				std::cout << "Error - Expected a marker\n";
				break;
			}
			else if (current == unsigned char(JpegMarker::M_SOS)) {
				break;
			}
			else if (current == unsigned char(JpegMarker::M_APP11))
			{
				uint32_t len = db_get_2byte(&data);
				uint32_t CI = db_get_2byte(&data);
				uint32_t this_En = db_get_2byte(&data);
				uint32_t this_Z = db_get_4byte(&data);
				Lbox = db_get_4byte(&data);
				uint32_t Tbox = db_get_4byte(&data);
				if (Tbox == uint32_t(BoxType::JUMB) && this_Z == 1)
				{
					JumbfContentType this_type = db_identify_jumbf_content_type(data + 8);
					if (this_type == type) {
						is_requested_jumbf = true;
					}
				}
				if (is_requested_jumbf) {
					int this_marker_data_size = 0;
					if (this_En == previous_En && this_Z == (previous_Z + 1)) { // these checks are enough for this jumb box 
						if (this_Z == 1) {
							unsigned char* LboxTbox_ptr = new unsigned char[8];
							db_put_4byte(&LboxTbox_ptr, Lbox);
							db_put_4byte(&LboxTbox_ptr, Tbox);
							LboxTbox_ptr -= 8;
							codestream_data.insert(codestream_data.end(), &LboxTbox_ptr[0], &LboxTbox_ptr[8]);
						}
						// we have to concatenate the data.
						this_marker_data_size = len - 18;
						codestream_data.insert(codestream_data.end(), &data[0], &data[this_marker_data_size]);
						previous_Z++;
					}
					data += this_marker_data_size; //(len - 18);

				}
				else {
					data += (len - 18);
				}
			}
			else if (current == unsigned char(JpegMarker::M_SOI)) {
				break;
			}
			else if (current == unsigned char(JpegMarker::M_EOI)) {
				break;
			}
			else {
				int len = db_get_2byte(&data);
				data += (len - 2);
			}
			last = db_get_byte(&data);
			current = db_get_byte(&data);
		}
		if (!is_requested_jumbf) {
			*jumb_buf = nullptr;
			*jumb_buf_size = 0;
			return 0;
		}
		// Now codestream_data has all the concatenated data.
		if (Lbox != codestream_data.size()) {
			std::cout << "Concatenation failed to get all data" << std::endl;
			return -1;
		}
		*jumb_buf_size = uint32_t(codestream_data.size());
		*jumb_buf = new unsigned char[codestream_data.size()];
		memcpy_s(*jumb_buf, size_t(*jumb_buf_size), codestream_data.data(), rsize_t(codestream_data.size()));
		codestream_data.clear();
		return 0;
	}

	int db_extract_jumbfs_from_jpg1(unsigned char* jpg_buf, uint64_t jpg_buf_size, std::vector<unsigned char*>& jumbfs_vec, std::vector<uint64_t>& sizes)
	{
		if (jpg_buf == nullptr) {
			return -1;
		}
		unsigned char* jumb_buf = nullptr;
		unsigned char* data = jpg_buf;
		unsigned char last = db_get_byte(&data);
		unsigned char current = db_get_byte(&data);
		if (last != 0xFF || current != unsigned char(JpegMarker::M_SOI)) {
			std::cout << "Image is not JPEG" << std::endl;
			return -1;
		}
		last = db_get_byte(&data);
		current = db_get_byte(&data);
		uint32_t previous_En = 0;
		uint32_t previous_Z = 0;
		unsigned Lbox = 0;
		//reading markers;
		while (1)
		{
			if (last != 0xFF)
			{
				std::cout << "Error - Expected a marker\n";
				break;
			}
			else if (current == unsigned char(JpegMarker::M_SOS)) {
				break;
			}
			else if (current == unsigned char(JpegMarker::M_APP11))
			{
				uint32_t this_app11_header_size{ 10 };
				uint32_t len = db_get_2byte(&data);
				uint32_t CI = db_get_2byte(&data);
				uint32_t this_En = db_get_2byte(&data);
				uint32_t this_Z = db_get_4byte(&data);
				uint32_t this_box_header_size{ 8 };
				uint32_t this_app11_paylaod_size{ 0 };
				uint32_t next_marker{ 0 };
				Lbox = db_get_4byte(&data);
				bool xl_box_present = false;
				if (Lbox == 1)
					xl_box_present = true;
				uint32_t Tbox = db_get_4byte(&data);
				uint64_t box_length = 0;
				if (xl_box_present) {
					uint64_t xl_size = db_get_4byte(&data);
					xl_size = xl_size << 32;
					uint64_t xl_size2 = db_get_4byte(&data);
					box_length = xl_size + xl_size2;
					this_box_header_size += 8;
				}
				else
					box_length = Lbox;
				this_app11_paylaod_size = len - this_app11_header_size - this_box_header_size;
				next_marker = len - this_app11_header_size;
				if (this_En != previous_En && Tbox == uint32_t(BoxType::JUMB)) { // New JUMBF
					//cout << "New JUMBF Detected. => Lbox : " << box_length << endl;
					jumb_buf = new unsigned char[box_length];
					jumbfs_vec.push_back(jumb_buf);
					sizes.push_back(box_length);
					data -= this_box_header_size;
					memcpy_s(jumb_buf, box_length, data, static_cast<rsize_t>(this_app11_paylaod_size) + this_box_header_size);
					jumb_buf += (this_app11_paylaod_size + this_box_header_size);
					data += (this_app11_paylaod_size + this_box_header_size);
				}
				else if (this_En == previous_En && Tbox == uint32_t(BoxType::JUMB) && this_Z == (previous_Z + 1))
				{
					memcpy_s(jumb_buf, box_length, data, this_app11_paylaod_size);
					jumb_buf += this_app11_paylaod_size;
					data += this_app11_paylaod_size;
				}
				else {
					std::cout << "Unrecognized En, and Z value detected in APP11 Marker" << std::endl;
					return -1;
				}
				//data += (len - this_app11_header_size );
				previous_En = this_En;
				previous_Z = this_Z;
			}
			else if (current == unsigned char(JpegMarker::M_SOI)) {
				break;
			}
			else if (current == unsigned char(JpegMarker::M_EOI)) {
				break;
			}
			else {
				int len = db_get_2byte(&data);
				data += (len - 2);
			}
			last = db_get_byte(&data);
			current = db_get_byte(&data);
		}
		// Now codestream_data has all the concatenated data.
		return 0;
	}




	void db_read_file_bitstream(std::string InputFile, unsigned char** pBuffer, uint64_t* file_size) {
		std::ifstream in_file(InputFile, std::ifstream::binary);
		if (in_file) {
			in_file.seekg(0, in_file.end);
			uint64_t length = uint64_t(in_file.tellg());
			in_file.seekg(0, in_file.beg);
			char* buffer = new char[length];
			in_file.read(buffer, length);
			if (in_file) {
				*pBuffer = (unsigned char*)buffer;
				*file_size = length;
			}
			else
				std::cout << "error: only " << in_file.gcount() << " could be read from input file";
			in_file.close();
		}
	}
	void db_write_file_bitstream(std::string OutputFile, const unsigned char* const data, const uint64_t data_size) {
		FILE* Outfp;
		errno_t err;
		err = fopen_s(&Outfp, OutputFile.c_str(), "wb");
		if (err == 0)
		{
			size_t bytes_written = fwrite(data, 1, data_size, Outfp);
			if (bytes_written == data_size)
			{
				std::cout << "Output file \"" << OutputFile << "\" created Successfully.\n" << std::endl;
			}
			else
			{
				std::cout << "Problem in writing to file\n" << std::endl;
			}
			fclose(Outfp);
		}
		else
		{
			std::cout << "Error: Failed to open output File : " << OutputFile << std::endl;
			exit(EXIT_FAILURE);
		}

	}


}