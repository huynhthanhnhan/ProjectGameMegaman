#include "Global.h"

bool						Global::isGameRunning = true;

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

Global::Global()
{
}


Global::~Global()
{
}



void Global::GLPostMessage(char * msg)
{
	MessageBox(NULL, msg, "Notify", MB_OK | MB_ICONINFORMATION);
}
