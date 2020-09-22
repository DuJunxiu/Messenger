
#ifndef __EVENTLOOP_HPP__
#define __EVENTLOOP_HPP__

#include "Utility.hpp"

using namespace MyMessenger;

class CEventLoop
{
public:
	CEventLoop() {}
	~CEventLoop() {}

public:
	int initialize();
	
	int release();
	
	int routine();
	
	void OnTick();

private:
	static int m_iCommand;

};

#endif