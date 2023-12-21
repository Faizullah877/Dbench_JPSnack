#include "db_jpsnk_instruction.h"

DbJPSnackInstruction::DbJPSnackInstruction()
{
}

DbJPSnackInstruction::~DbJPSnackInstruction()
{
}

void DbJPSnackInstruction::set_xo(uint32_t xo)
{
	xo_ = xo;
}

uint32_t DbJPSnackInstruction::get_xo()
{
	return xo_;
}

void DbJPSnackInstruction::set_yo(uint32_t yo)
{
	yo_ = yo;
}

uint32_t DbJPSnackInstruction::get_yo()
{
	return yo_;
}

void DbJPSnackInstruction::set_width(uint32_t w)
{
	width_ = w;
}

uint32_t DbJPSnackInstruction::get_width()
{
	return width_;
}

void DbJPSnackInstruction::set_height(uint32_t h)
{
	height_ = h;
}

uint32_t DbJPSnackInstruction::get_height()
{
	return height_;
}

void DbJPSnackInstruction::set_persistance(bool p)
{
	persist_ = p;
}

bool DbJPSnackInstruction::is_persitant()
{
	return persist_;
}

void DbJPSnackInstruction::set_life(uint32_t life)
{
	life_ = life;
}

uint32_t DbJPSnackInstruction::get_life()
{
	return life_;
}

void DbJPSnackInstruction::set_next_use(uint32_t n_u)
{
	next_use_ = n_u;
}

uint32_t DbJPSnackInstruction::get_next_use()
{
	return next_use_;
}

void DbJPSnackInstruction::set_xc(uint32_t xc)
{
	xc_ = xc;
}

uint32_t DbJPSnackInstruction::get_xc()
{
	return xc_;
}

void DbJPSnackInstruction::set_yc(uint32_t yc)
{
	yc_ = yc;
}

uint32_t DbJPSnackInstruction::get_yc()
{
	return yc_;
}

void DbJPSnackInstruction::set_wc(uint32_t wc)
{
	wc_ = wc;
}

uint32_t DbJPSnackInstruction::get_wc()
{
	return wc_;
}

void DbJPSnackInstruction::set_hc(uint32_t hc)
{
	hc_ = hc;
}

uint32_t DbJPSnackInstruction::get_hc()
{
	return hc_;
}

void DbJPSnackInstruction::set_rot(Rotation rot)
{
	switch (rot)
	{
	case dbench::Rotation::NOT_SPECIFIED:
		rot_ = 0;
		break;
	case dbench::Rotation::CLOCKWISE_0D:
		rot_ = 0x0001;
		break;
	case dbench::Rotation::CLOCKWISE_0D_AND_FLIP:
		rot_ = 0x0011;
		break;
	case dbench::Rotation::CLOCKWISE_90D:
		rot_ = 0x0002;
		break;
	case dbench::Rotation::CLOCKWISE_90D_AND_FLIP:
		rot_ = 0x0012;
		break;
	case dbench::Rotation::CLOCKWISE_180D:
		rot_ = 0x0003;
		break;
	case dbench::Rotation::CLOCKWISE_180D_AND_FLIP:
		rot_ = 0x0013;
		break;
	case dbench::Rotation::CLOCKWISE_270D:
		rot_ = 0x0004;
		break;
	case dbench::Rotation::CLOCKWISE_270D_AND_FLIP:
		rot_ = 0x0014;
		break;
	default:
		rot_ = 0x0000;
		break;
	}
}

Rotation DbJPSnackInstruction::get_rot()
{
	switch (rot_)
	{
	case 0:
		return Rotation::NOT_SPECIFIED;
		break;
	case 1:
		return Rotation::CLOCKWISE_0D;
		break;
	case 0x0011:
		return Rotation::CLOCKWISE_0D_AND_FLIP;
		break;
	case 0x0002:
		return Rotation::CLOCKWISE_90D;
		break;
	case 0x0012:
		return Rotation::CLOCKWISE_90D_AND_FLIP;
		break;
	case 0x0003:
		return Rotation::CLOCKWISE_180D;
		break;
	case 0x0013:
		return Rotation::CLOCKWISE_180D_AND_FLIP;
		break;
	case 0x0004:
		return Rotation::CLOCKWISE_270D;
		break;
	case 0x0014:
		return Rotation::CLOCKWISE_270D_AND_FLIP;
		break;
	default:
		return Rotation::NOT_SPECIFIED;
		break;
	}
}







