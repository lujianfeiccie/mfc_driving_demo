#include "StdAfx.h"
#include "IControlSpace.h"


IControlSpace::IControlSpace(void)
{
	Util::LOG(L"IControlSpace");
	m_tips = new ControlTips;
}


IControlSpace::~IControlSpace(void)
{
	Util::LOG(L"~IControlSpace");
	delete m_tips;
}
