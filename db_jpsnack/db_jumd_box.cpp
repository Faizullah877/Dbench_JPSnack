
#include "db_jumd_box.h"

namespace dbench {
	DbJumbDescBox::DbJumbDescBox()
	{
		set_box_type(BoxType::JUMD);
	}

	DbJumbDescBox::~DbJumbDescBox()
	{
	}

	void DbJumbDescBox::set_box_size()
	{
		box_size_ = 25; // 1byte toggles + 16 byte UUID
		if (this->label_present_)
			box_size_ += static_cast<uint64_t>(this->lable_size_); 

		if (this->id_present_)
			box_size_ += 4;

		if (this->hash_present_)
			box_size_ += 32;

		if (this->private_present_)
			box_size_ += (this->private_box_->get_box_size());

		if (box_size_ > MAX_32BIT_UINT_VALUE)
			box_size_ += (static_cast<uint64_t>(8)); // 8 xl_box


		if (box_size_ > MAX_32BIT_UINT_VALUE)
		{
			lbox_ = 1;
			xl_box_ = box_size_;
			xl_box_present_ = true;
		}
		else {
			lbox_ = static_cast<uint32_t>(box_size_);
			xl_box_present_ = false;
		}
	}

	JumbfContentType DbJumbDescBox::get_jumb_content_type()
	{
		return content_type_;
	}

	void DbJumbDescBox::set_requestable_bit_ON()
	{
		toggles_ = toggles_ | 1;
	}
	void DbJumbDescBox::set_label_toggle_bit_ON()
	{
		toggles_ = toggles_ | 2; // OR with 0000 0010
	}
	void DbJumbDescBox::set_id_toggle_bit_ON()
	{
		toggles_ = toggles_ | 4; // OR with 0000 0100
	}
	void DbJumbDescBox::set_hash_toggle_bit_ON()
	{
		toggles_ = toggles_ | 8; // OR with 0000 1000
	}
	void DbJumbDescBox::set_private_toggle_bit_ON()
	{
		toggles_ = toggles_ | 16; // OR with 0001 0000
	}

	DbJumbDescBox::DbJumbDescBox(JumbfContentType content_type_in)
	{
		set_box(content_type_in, false, "", false, 0, nullptr, nullptr);
	}

	DbJumbDescBox::DbJumbDescBox(JumbfContentType content_type_in, std::string label)
	{
		set_box(content_type_in, false, label, false, 0, nullptr, nullptr);
	}

	DbJumbDescBox::DbJumbDescBox(JumbfContentType content_type_in, std::string label, uint32_t ID)
	{
		set_box(content_type_in, false, label, true, ID, nullptr, nullptr);
	}

	DbJumbDescBox::DbJumbDescBox(JumbfContentType content_type_in, std::string label, uint32_t ID, unsigned char* hash)
	{
		set_box(content_type_in, false, label, true, ID, hash, nullptr);
	}

	DbJumbDescBox::DbJumbDescBox(JumbfContentType content_type_in, std::string label, uint32_t ID, unsigned char* hash, DbBox *priv_box)
	{
		set_box(content_type_in, false, label, true, ID, hash, priv_box);
	}

	void DbJumbDescBox::set_box(JumbfContentType content_type_in, bool requestable, std::string label, bool id_present, uint32_t ID, unsigned char* hash, DbBox* priv_box)
	{
		unsigned char* type_id = db_get_jumbf_content_type_uuid(content_type_in);
		set_content_type(content_type_in);
		set_box(type_id, requestable, label, id_present, ID, hash, priv_box);

	}

	void DbJumbDescBox::set_box(unsigned char* typein, bool requestable, std::string label, bool id_present, uint32_t ID, unsigned char* hash, DbBox* priv_box)
	{
		set_type_16bytes(typein);
		set_requestable(requestable);
		set_label(label);
		if (id_present)
			set_id(ID);
		set_hash(hash);
		set_private_box(priv_box);
		set_box_size();
	}

	void DbJumbDescBox::set_content_type(JumbfContentType type)
	{
		unsigned char* content_type_uuid = db_get_jumbf_content_type_uuid(type);
		this->set_type_16bytes(content_type_uuid);
		this->content_type_ = type;
	}

	void DbJumbDescBox::set_type_16bytes(unsigned char* type_ptr)
	{
		if (type_ptr == nullptr)
		{
			return;
		}
		for (auto i = 0; i < 16; i++)
			this->type_uuid_[i] = type_ptr[i];
	}
	unsigned char* DbJumbDescBox::get_type_16bytes()
	{
		unsigned char* buf = new unsigned char[16];
		for (auto i = 0; i < 16; i++)
			buf[i] = type_uuid_[i];
		return buf;
	}

	void DbJumbDescBox::set_toggles_byte(unsigned char x)
	{
		this->toggles_ = x;
	}
	unsigned char DbJumbDescBox::get_toggles_byte()
	{
		return this->toggles_;
	}

	bool DbJumbDescBox::is_requestable()
	{
		requestable_ = isNthBitSet_1(toggles_, 1);
		return this->requestable_;
	}
	void DbJumbDescBox::set_requestable(bool on_off)
	{
		if (on_off) {
			toggles_ = toggles_ | 1; // OR with 0000 0001
		}
		else {
			toggles_ = toggles_ & 254; // AND with 1111 1110
		}

		this->requestable_ = on_off;
	}

	bool DbJumbDescBox::is_label_present()
	{
		this->label_present_ = isNthBitSet_1(toggles_, 2);
		return this->label_present_;
	}
	void DbJumbDescBox::set_label(std::string label)
	{
		this->label_ = label;
		if (label.empty())
			return;
		this->label_present_ = true;
		this->set_label_toggle_bit_ON();
		this->lable_size_ = static_cast<uint32_t>(label.length()) + 1; // 1 for null character.
		this->box_size_ += this->lable_size_;
		this->set_box_size();

	}
	std::string DbJumbDescBox::get_label()
	{
		return this->label_;
	}

	bool DbJumbDescBox::is_id_present()
	{
		this->id_present_ = isNthBitSet_1(toggles_, 3);
		return this->id_present_;
	}
	void DbJumbDescBox::set_id(uint32_t id_in)
	{
		this->id_ = id_in;
		this->id_present_ = true;
		this->set_id_toggle_bit_ON();
		this->set_box_size();
	}
	uint32_t DbJumbDescBox::get_id()
	{
		return this->id_;
	}

	bool DbJumbDescBox::is_hash_present()
	{
		this->hash_present_ = isNthBitSet_1(toggles_, 4);
		return this->hash_present_;
	}
	void DbJumbDescBox::set_hash(unsigned char* hs)
	{
		if (hs == nullptr) {
			hash_present_ = false;
			return;
		}
		this->hash_ = new unsigned char[32];
		for (auto i = 0; i < 32; i++)
			this->hash_[i] = hs[i];

		this->hash_present_ = true;
		this->set_hash_toggle_bit_ON();
		this->set_box_size();
	}
	unsigned char* DbJumbDescBox::get_hash()
	{
		return this->hash_;
	}


	bool DbJumbDescBox::is_private_box_present()
	{
		this->private_present_ = isNthBitSet_1(toggles_, 5);
		return this->private_present_;
	}
	void DbJumbDescBox::set_private_box(DbBox* priv_box)
	{
		if (priv_box == nullptr)
			return;
		this->private_box_ = priv_box;
		this->private_present_ = true;
		this->set_private_toggle_bit_ON();
		this->box_size_ += priv_box->get_box_size();
		this->set_box_size();
	}
	DbBox* DbJumbDescBox::get_private_box()
	{
		return this->private_box_;
	}

	void DbJumbDescBox::serialize(unsigned char** out_buf, uint64_t* out_buf_size)
	{
		set_box_size();
		uint64_t buf_size_t = get_box_size();

		*out_buf = new unsigned char[buf_size_t];

		unsigned char* buf = *out_buf;
		uint32_t bytes_done = 0;
		db_put_4byte(&buf, lbox_);
		db_put_4byte(&buf, tbox_);
		bytes_done += 8;

		// putting xl_box field
		if (xl_box_present_) {
			db_put_8byte(&buf, xl_box_);
		}

		// put 16 byte type uuid
		for (auto i = 0; i < 16; i++)
			db_put_byte(&buf, type_uuid_[i]);
		bytes_done += 16;

		// put 1 byte toggle
		db_put_byte(&buf, toggles_);
		bytes_done += 1;

		//label;
		if (label_present_)
		{
			for (int i = 0; i < int(lable_size_); i++) {
				db_put_byte(&buf, label_[i]);
				bytes_done += 1;
			}
		}
		//id
		if (id_present_)
		{
			db_put_4byte(&buf, id_);
			bytes_done += 4;
		}
		//hash
		if (hash_present_)
		{
			if (hash_ == nullptr) {
				throw std::runtime_error("Error: Serializing JUMD, Signature is not available.");
			}
			for (int i = 0; i < 32; i++) {
				db_put_byte(&buf, hash_[i]);
			}
			bytes_done += 32;
		}
		if (private_present_) {
			uint64_t header_size = 8;
			db_put_4byte(&buf, private_box_->get_lbox());
			db_put_4byte(&buf, private_box_->get_tbox());
			bytes_done += 8;
			if (private_box_->is_xl_box_present()) {
				db_put_8byte(&buf, private_box_->get_xl_box());
				bytes_done += 8;
				header_size += 8;
			}

			memcpy_s(buf, buf_size_t, private_box_->get_payload(), static_cast<rsize_t>(private_box_->get_box_size()) - header_size);
		}
		*out_buf_size = buf_size_t;
	}

	void DbJumbDescBox::deserialize(unsigned char* in_jumd_buf, uint64_t in_buf_size)
	{
		uint64_t header_size{ 8 };
		uint64_t bytes_remaining = in_buf_size;

		unsigned char* buf = in_jumd_buf;
		
		lbox_ = db_get_4byte(&buf);
		tbox_ = db_get_4byte(&buf);
		box_type_ = db_identify_box_type(tbox_);
		if (box_type_ != BoxType::JUMD) {
			throw std::runtime_error("Error: De-Serializing JUMD, input buffer is not JUMD buffer.");
			return;
		}
		bytes_remaining -= 8;
		if (lbox_ == 1) {
			xl_box_ = db_get_8byte(&buf);
			xl_box_present_ = true;
			header_size += 8;
			box_size_ = xl_box_;
			bytes_remaining -= 8;
		}
		else if (lbox_ == 0) {
			box_size_ = in_buf_size;
		}
		else
			box_size_ = lbox_;

		for (auto i = 0; i < 16; i++) {
			type_uuid_[i] = db_get_byte(&buf);
		}

		content_type_ = db_identify_jumbf_content_type(type_uuid_);

		bytes_remaining -= 16;
		toggles_ = db_get_byte(&buf);
		bytes_remaining -= 1;
		requestable_ = is_requestable();
		label_present_ = is_label_present();
		id_present_ = is_id_present();
		hash_present_ = is_hash_present();
		private_present_ = is_private_box_present();

		if (label_present_) {
			std::vector<unsigned char> label_1;
			for (uint32_t k = 0; ; ++k) { // will go to null character
				unsigned char a = db_get_byte(&buf);
				bytes_remaining -= 1;
				label_1.push_back(a);
				if (a == 0x00)
					break;
			}
			std::string s(label_1.begin(), label_1.end() - 1); // -1 for removing null character. as it is attached again by set_lable function
			label_ = s;		
			lable_size_ = static_cast<uint32_t>(s.size() + 1);
		}
		if (id_present_) {
			id_ = db_get_4byte(&buf);
			bytes_remaining -= 4;
		}
		if (hash_present_) {
			hash_ = new unsigned char[256];
			for (uint32_t k = 0; k < 256; ++k) {
				hash_[k] = db_get_byte(&buf);
				bytes_remaining -= 1;
			}
		}
		if (private_present_) {
			DbBox* priv_box = new DbBox;
			priv_box->deserialize(buf, bytes_remaining);
			private_box_ = priv_box;
		}
	}

}