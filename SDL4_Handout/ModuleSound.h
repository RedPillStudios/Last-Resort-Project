#ifndef __ModuleSound_H__
#define __ModuleSound_H__

#include "Module.h"
#include "Globals.h"

struct Mix_Music;
struct Mix_Chunk;

class ModuleSound :public Module
{
public:
	ModuleSound();
	~ModuleSound();


	bool Init();
	bool CleanUp();

	Mix_Music*const LoadMusic(const char*path);
	Mix_Chunk*const LoadChunk(const char*path);



};








#endif // _ModuleSound_H__