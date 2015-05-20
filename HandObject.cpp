#include "stdafx.h"
#include "HandObject.hpp"
#include "LeapVisualizer.hpp"

void HandObject::atRefresh()
{
	if(vis) vis->update();
}