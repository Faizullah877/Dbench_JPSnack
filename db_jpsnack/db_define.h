#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>

namespace dbench {

	constexpr auto MAX_32BIT_UINT_VALUE = 4294967295;;
	enum class JpegMarker {                  /* JPEG marker codes */
		M_SOF0 = 0xc0,
		M_SOF1 = 0xc1,
		M_SOF2 = 0xc2,
		M_SOF3 = 0xc3,

		M_SOF5 = 0xc5,
		M_SOF6 = 0xc6,
		M_SOF7 = 0xc7,

		M_JPG = 0xc8,
		M_SOF9 = 0xc9,
		M_SOF10 = 0xca,
		M_SOF11 = 0xcb,

		M_SOF13 = 0xcd,
		M_SOF14 = 0xce,
		M_SOF15 = 0xcf,

		M_DHT = 0xc4,

		M_DAC = 0xcc,

		M_RST0 = 0xd0,
		M_RST1 = 0xd1,
		M_RST2 = 0xd2,
		M_RST3 = 0xd3,
		M_RST4 = 0xd4,
		M_RST5 = 0xd5,
		M_RST6 = 0xd6,
		M_RST7 = 0xd7,

		M_SOI = 0xd8,
		M_EOI = 0xd9,
		M_SOS = 0xda,
		M_DQT = 0xdb,
		M_DNL = 0xdc,
		M_DRI = 0xdd,
		M_DHP = 0xde,
		M_EXP = 0xdf,

		M_APP0 = 0xe0,
		M_APP1 = 0xe1,
		M_APP2 = 0xe2,
		M_APP3 = 0xe3,
		M_APP4 = 0xe4,
		M_APP5 = 0xe5,
		M_APP6 = 0xe6,
		M_APP7 = 0xe7,
		M_APP8 = 0xe8,
		M_APP9 = 0xe9,
		M_APP10 = 0xea,
		M_APP11 = 0xeb,
		M_APP12 = 0xec,
		M_APP13 = 0xed,
		M_APP14 = 0xee,
		M_APP15 = 0xef,

		M_JPG0 = 0xf0,
		M_JPG13 = 0xfd,
		M_COM = 0xfe,

		M_TEM = 0x01,

		M_ERROR = 0x100
	};
	enum class BoxType {
		JUMB = 0x6a756d62, // jumb = JUMBF Superbox
		JUMD = 0x6a756d64, // jumd = jumbf description Box
		JP2C = 0X6A703263, // Contiguous Codestream Box 
		XML = 0X786D6C20,  // xml box
		JSON = 0X6A736F6E, // json box
		UUID = 0X75756964,  // uuid box
		BIDB = 0x62696462, // binary data box
		BFDB = 0x62666462, // Embedded file Description box
		CBOR = 0x63626F72, // CBOR box
		FREE = 0x66726565, // free box => padding box
		PRIV = 0x70726976, // Private box
		INST = 0x696E7374, // jpeg snack "inst" instruction set box
		JSDB = 0x6A736462, // jpeg snack description box
		UNDEF = 0x00000000  // undefined
	};
	enum class Rotation
	{
		NOT_SPECIFIED = 0x0000,
		CLOCKWISE_0D = 0x0001,
		CLOCKWISE_0D_AND_FLIP = 0x0011,
		CLOCKWISE_90D = 0x0002,
		CLOCKWISE_90D_AND_FLIP = 0x0012,
		CLOCKWISE_180D = 0x0003,
		CLOCKWISE_180D_AND_FLIP = 0x0013,
		CLOCKWISE_270D = 0x0004,
		CLOCKWISE_270D_AND_FLIP = 0x0014
	};

	enum class JumbfContentType {
		CODESTREAM,      // 0x6579D6FB-DBA2-446B-B2AC-1B82FEEB89D1
		XML,             // 0x786D6C20-0011-0010-8000-00AA00389B71
		JSON,            // 0x6A736F6E-0011-0010-8000-00AA00389B71
		UUID,			 // 0x75756964-0011-0010-8000-00AA00389B71
		EMBEDDED_File,   // 0x40CB0C32-BB8A-489D-A70B-2AD6F47F4369
		CBOR,			 // 0x63626F72-0011-0010-8000-00AA00389B71
		JPEG360,
		UNDEF
	};
	bool isNthBitSet_1(unsigned char byte, int n);
	bool db_put_byte(unsigned char** dst_buf, char data);
	bool db_put_2byte(unsigned char** dst_buf, uint32_t data);
	bool db_put_4byte(unsigned char** dst_buf, uint32_t data);
	bool db_put_8byte(unsigned char** dst_buf, uint64_t value);
	unsigned char db_get_byte(unsigned char** buf);
	uint16_t db_get_2byte(unsigned char** buf);
	uint32_t db_get_4byte(unsigned char** buf);
	uint64_t db_get_8byte(unsigned char** buf);
	unsigned char* db_get_jumbf_content_type_uuid(JumbfContentType type);
	JumbfContentType db_identify_jumbf_content_type(unsigned char* type_16b);
	BoxType db_identify_box_type(uint32_t tbox);

	int db_write_jumbf_buf_to_jpg_buf(unsigned char* jumbf_buf, uint64_t jumbf_size, unsigned char* jpg_buf, uint64_t jpg_size, unsigned char** out_buf, uint64_t* out_buf_siz);

	// db_extract_jumbf_bitstream extract JUMBF bitstream "jumb_buf" of size "jumb_buf_size" of requested content "type" from "in_jpg_buf" of size "in_jpg_size"
	int db_extract_jumbf_bitstream(unsigned char* in_jpg_buf, uint64_t in_jpg_size, JumbfContentType type, unsigned char** jumb_buf, uint32_t* jumb_buf_size);

	// db_extract_jumbfs_from_jpg1 extract all JUMBFs bitstreams from jpg_buf of size jpg_buf_size and put pointers to each buff in jumbfs_vec
	int db_extract_jumbfs_from_jpg1(unsigned char* jpg_buf, uint64_t jpg_buf_size, std::vector<unsigned char*>& jumbfs_vec, std::vector<uint64_t>& sizes);

	void db_read_file_bitstream(std::string InputFile, unsigned char** pBuffer, uint64_t* file_size);
	void db_write_file_bitstream(std::string OutputFile, const unsigned char* const data, const uint64_t data_size);
}