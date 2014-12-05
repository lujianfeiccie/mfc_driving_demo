#pragma once
#include "icontrol.h"
#include "ControlTips.h"
#include "Util.h"
class IControlSpace :
	public IControl
{

public:
	IControlSpace(void);
	virtual ~IControlSpace(void);
	ControlTips *m_tips;
};

