#ifndef IDS_H
#define IDS_H

public class IdsRibbonItems
{		
public:
	static const int DUMMY = 10;

	static const int SYSTEM_EXIT = 20;

	static const int HOME_FILE_NEW = 100;
	static const int HOME_FILE_SAVE = 101;
	static const int HOME_FILE_SAVEAS = 102;
	static const int HOME_FILE_OPEN = 103;
	static const int HOME_PARAMETERS_TITLE = 104;
	static const int SCRIPTING_FILE_NEW = 200;
	static const int SCRIPTING_FILE_SAVE = 201;
	static const int SCRIPTING_FILE_SAVEAS = 202;
	static const int SCRIPTING_FILE_OPEN = 203;
	static const int SCRIPTING_EXECUTE_RUN = 204;
	static const int SCRIPTING_EXECUTE_TYPE = 205;
	static const int SCRIPTING_EXECUTE_STOP = 206;
	static const int SCRIPTING_REAL_TIME_PREVIEW = 207;
	static const int SCRIPTING_REAL_TIME_EXPORT = 208;
	static const int SCRIPTING_REAL_TIME_START = 209;
	static const int SCRIPTING_REAL_TIME_STOP = 210;

	static const int VIEW_PRESETS_XZ = 300;
	static const int VIEW_PRESETS_XY = 301;
	static const int VIEW_PRESETS_YZ = 302;
	static const int VIEW_PRESETS_DEFAULT = 303;
	static const int VIEW_ITEMS_LATTICE = 304;
	static const int VIEW_ITEMS_BASE = 305;
	static const int VIEW_ITEMS_AXIS = 306;
	static const int VIEW_LATTICE_SIZE = 307;
	static const int VIEW_LATTICE_SPACING = 308;
	static const int VIEW_LATTICE_BLACK_AS = 309;
	static const int VIEW_SETTINGS_QUALITY = 310;

	static const int SETTINGS_PANES_FRAMES = 400;
	static const int SETTINGS_PANES_SCRIPT_SOURCE = 401;
	static const int SETTINGS_PANES_SCRIPT_OUTPUT = 402;

	static const int PREVIEW_PLAYBACK_PLAY = 500;
	static const int PREVIEW_PLAYBACK_STOP = 501;
	static const int PREVIEW_PLAYBACK_SELECTION = 502;
	static const int PREVIEW_PLAYBACK_REPEAT = 503;

	static const int PREVIEW_EIGHTCUBED_CONNECT = 504;
	static const int PREVIEW_EIGHTCUBED_DISCONNECT = 505;
	static const int PREVIEW_EIGHTCUBED_STREAM = 506;



};

public class IdsDockingPanel
{		
public:
	static const int PANEL_FRAMES = 101;
	static const int PANEL_SCRIPT_SOURCE = 102;
	static const int PANEL_SCRIPT_OUTPUT = 103;


};

public class IdsStatusBarItems
{		
public:
	static const int ITEM_DUMYY = 100;
	static const int ITEM_MAIN_STATUS = 101;
	static const int ITEM_FPS_OPENGL = 102;
	static const int ITEM_PROGRESS = 103;
	static const int ITEM_ACTIVE_FRAME = 104;
	static const int ITEM_LATTICE_SIZE = 105;
	static const int ITEM_USB_STATUS=106;

};

#endif
