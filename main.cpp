#include <slice.h>

//#include "interface.h"
//#include "mixer/mixer.h"
#include "musicmap.h"

void InsertMeasureAtEnd ()
{
	InsertMeasure(GetMeasureCount());
};
void RemoveMeasureFromEnd ()
{
	RemoveMeasure(GetMeasureCount() - 1);
};
slScalar SongTime = 0;
void Mix (float* buf, slBU samples, bool stereo, slScalar persample)
{
	for (slBU cur = 0; cur < samples; cur++)
	{
		// Get a sample from the MusicMap.
		slScalar value = GetSample(persample);
		// Copy this sample into the audio.
		*(buf + cur) = value;
		// Since we're only making mono sound,
		// the right channel in stereo sound
		// should have the same data as left.
		if (stereo) *(buf + samples + cur) = value;
	};
};
int main ()
{
	slInit();
	slSetCustomDrawStage_Middle(DrawGrid);
	slOpenAudio();
	slSetCustomMixStage(Mix);
	//ui_init();
	//music_init();
	slGetKeyBind("Append Measure to End",SDLK_m)->onpress = InsertMeasureAtEnd;
	slGetKeyBind("Chop Measure from End",SDLK_n)->onpress = RemoveMeasureFromEnd;
	slKeyBind* dragbind = slGetKeyBind("Drag Note",0,SDL_BUTTON(SDL_BUTTON_LEFT));
	dragbind->onpress = GrabNote;
	dragbind->onrelease = ReleaseNote;
	while (!slGetExitReq())
	{
		RepositionNotes();
		UpdateGrabbedNote();
		slCycle();
	};
	slQuit();
	// return 0; is not necessary
	// because slQuit exits the program with a zero return
};
