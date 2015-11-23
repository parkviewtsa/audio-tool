#include <slice.h>

//#include "interface.h"
//#include "mixer/mixer.h"
#include "musicmap.h"
void AddMeasureAtEnd ()
{
	InsertMeasure(GetMeasureCount);
};
int main ()
{
	slInit();
	slSetCustomDrawStage_Middle(DrawGrid);
	//ui_init();
	//music_init();
	slGetKeyBind("Append Measure",SDLK_m)->onpress = AddMeasureAtEnd;
	slKeyBind* dragbind = slGetKeyBind("Drag Note",0,SDL_BUTTON(SDL_BUTTON_LEFT));
	dragbind->onpress = GrabNote;
	dragbind->onrelease = ReleaseNote;
	while (!slGetReqt())
	{
		RepositionNotes();
		UpdateGrabbedNote();
		slCycle();
	};
	slQuit();
	// return 0; is not necessary
	// because slQuit exits the program with a zero return
};
