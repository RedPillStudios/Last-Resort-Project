#ifndef __ModuleSound_H__
#define __ModuleSound_H__

#include "Module.h"
#include "Globals.h"

#define MAX_MUSIC 2
#define MAX_CHUNKS 50

typedef struct _Mix_Music Mix_Music;

struct Mix_Chunk;

class ModuleSound :public Module
{
public:
	ModuleSound();
	~ModuleSound();


	bool Init();
	bool CleanUp();
	update_status Update();

	Mix_Music*const LoadMusic(const char*path);
	Mix_Chunk*const LoadChunk(const char*path);

public:

	//Mix_Music*music[MAX_MUSIC];
	//Mix_Chunk*chunks[MAX_CHUNKS];
	Mix_Music*music[MAX_MUSIC];
	Mix_Chunk*chunks;

};








#endif // _ModuleSound_H__