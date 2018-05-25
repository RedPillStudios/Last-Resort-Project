#ifndef __ModuleSound_H__
#define __ModuleSound_H__

#include "Module.h"
#include "Globals.h"

#define VOLUME_MUSIC 50
#define VOLUME_FX 100
#define MAX_MUSIC 5
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
	
	bool UnloadMusic(Mix_Music*music);
	bool UnloadChunks(Mix_Chunk*chunk);



	bool Playing=false;
	
	Mix_Music*music[MAX_MUSIC];
	Mix_Chunk*chunks[MAX_CHUNKS];
	
};








#endif // _ModuleSound_H__