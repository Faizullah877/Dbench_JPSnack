#include "db_jpsnack_jumbf.h"
namespace dbench {

DbJPSnack::DbJPSnack()
{
	desc_box_.set_content_type(JumbfContentType::JPSNACK);
}

DbJPSnack::~DbJPSnack()
{
}
}