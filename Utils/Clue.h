#ifndef CLUE_H
#define CLUE_H

#ifndef _OS_H
#include <OS.h>
#endif


#ifdef CLUE

enum ClueCategory
{
	CC_GENERAL		= 0,
	CC_APPLICATION,
	CC_INTERFACE,
	CC_MEDIA,
	CC_STORAGE,
	CC_SUPPORT,
	CC_NETWORK,
	CC_MOUSE,
	CC_KEYBOARD,
	CC_PRINTING
};

enum ClueEvent
{
	CE_OK			= 0x00000001,
	CE_INFO			= 0x00000002,
	CE_WARNING		= 0x00000004,
	CE_ERROR		= 0x00000008,
	CE_SUCCEEDED	= 0x00000010,
	CE_FAILED		= 0x00000020,
	CE_ENTER		= 0x00000040,
	CE_EXIT			= 0x00000080,
	CE_TIMER		= 0x00000100,
	CE_BIRTH		= 0x00000200,
	CE_DEATH		= 0x00000400,
	CE_OBJECT		= 0x00000800
};

//this struct contains the majority of the information being sent
#ifdef BUILD_CLUE_APPLICATION  //define only for the actual Clue application, not programs that use the Clue library!

struct FingerPrint
{
	ClueCategory	Category;
	ClueEvent		Event;
	thread_id		ThreadID;
	team_id			TeamID;
	bigtime_t		Time;
	uint32			Line;
	uint32			Sequence;
};

#endif //BUILD_CLUE_APPLICATION







//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS
//ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS ENUMS

#ifdef _APP_FILE_INFO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, info_location, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, version_kind, const char * inDescription = NULL);
#endif

#ifdef _BYTEORDER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, swap_action, const char * inDescription = NULL);
#endif

#ifdef _COLOR_CONTROL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, color_control_layout, const char * inDescription = NULL);
#endif

#ifdef _CONTROL_WEB_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_parameter_flags, const char * inDescription = NULL);
#endif

#ifdef _DIRECT_WINDOW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, direct_buffer_state, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, direct_driver_state, const char * inDescription = NULL);
#endif

#ifdef _E_MAIL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, mail_flags, const char * inDescription = NULL);
#endif

#ifdef _FILE_PANEL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, file_panel_mode, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, file_panel_button, const char * inDescription = NULL);
#endif

#ifdef _FIND_DIRECTORY_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, directory_which, const char * inDescription = NULL);
#endif

#ifdef _FONT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, font_direction, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, font_metric_mode, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, font_file_format, const char * inDescription = NULL);
#endif

#ifdef _GAME_SOUND_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, gs_attributes, const char * inDescription = NULL);
#endif

#ifdef _GRAPHICS_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, color_space, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, drawing_mode, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, buffer_orientation, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, buffer_layout, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, source_alpha, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, alpha_function, const char * inDescription = NULL);
#endif

#ifdef _IMAGE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, image_type, const char * inDescription = NULL);
#endif

#ifdef _INPUT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, input_method_op, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, input_device_type, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, input_device_notification, const char * inDescription = NULL);
#endif

#ifdef _INTERFACE_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, alignment, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, join_mode, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, border_style, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, button_width, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, cap_mode, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, orientation, const char * inDescription = NULL);
#endif

#ifdef _LIST_VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, list_view_type, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_type, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, node_kind, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, video_orientation, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_flags, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_producer_status, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_realtime_flags, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_frame_flags, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_multi_channels, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_multi_matrix, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_display_flags, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_format_flags, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_format_family, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_TRACK_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_seek_type, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_TYPES_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_file_accept_format_flags, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, mpeg_id, const char * inDescription = NULL);
#endif

#ifdef _MENU_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, menu_layout, const char * inDescription = NULL);
#endif

#ifdef _MENU_BAR_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, menu_bar_border, const char * inDescription = NULL);
#endif

#ifdef _MESSAGE_FILTER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, filter_result, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, message_delivery, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, message_source, const char * inDescription = NULL);
#endif

#ifdef _MIDI_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, synth_mode, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, midi_axe, const char * inDescription = NULL);
#endif

#ifdef _MIME_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, icon_size, const char * inDescription = NULL);
#endif

#ifdef _OS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, thread_state, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, cpu_type, const char * inDescription = NULL);
#endif

#ifdef _PROPERTY_INFO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, value_kind, const char * inDescription = NULL);
#endif

#ifdef _QUERY_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, query_op, const char * inDescription = NULL);
#endif

#ifdef _SERIAL_PORT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, data_rate, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, data_bits, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, stop_bits, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, parity_mode, const char * inDescription = NULL);
#endif

#ifdef _SLIDER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, hash_mark_location, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, thumb_style, const char * inDescription = NULL);
#endif

#ifdef _STORAGE_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, node_flavor, const char * inDescription = NULL);
#endif

#ifdef _SUPPORT_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, status_t, const char * inDescription = NULL);
#endif

#ifdef _SYNTH_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, interpolation_mode, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, reverb_mode, const char * inDescription = NULL);
#endif

#ifdef _TAB_VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, tab_position, const char * inDescription = NULL);
#endif

#ifdef _TEXTVIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, undo_state, const char * inDescription = NULL);
#endif

#ifdef _TIME_CODE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, timecode_type, const char * inDescription = NULL);
#endif

#ifdef _TRANSLATION_ERRORS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, B_TRANSLATION_ERROR, const char * inDescription = NULL);
#endif

#ifdef _WINDOW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, window_type, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, window_look, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, window_feel, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, window_alignment, const char * inDescription = NULL);
#endif































//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES
//CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES CLASSES


#ifdef _ALERT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BAlert *, const char * inDescription = NULL);
#endif

#ifdef _APP_FILE_INFO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BAppFileInfo *, const char * inDescription = NULL);
#endif

#ifdef _APPLICATION_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BApplication *, const char * inDescription = NULL);
#endif

#ifdef _ARCHIVABLE_H
	//BArchivable doesn't have any meaningful methods I can call
#endif

#ifdef _AUTOLOCK_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BAutolock *, const char * inDescription = NULL);
#endif

#ifdef _BE_LIST_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BList *, const char * inDescription = NULL);
#endif

#ifdef BGLVIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BGLView *, const char * inDescription = NULL);
#endif

#ifdef _BITMAP_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBitmap *, const char * inDescription = NULL);
#endif

#ifdef _BITMAP_STREAM_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBitmapStream *, const char * inDescription = NULL);
#endif

#ifdef __BSTRING__
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BString *, const char * inDescription = NULL);
#endif

#ifdef _BUFFER_IO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBufferIO *, const char * inDescription = NULL);
#endif

#ifdef _GAME_SOUND_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BGameSound *, const char * inDescription = NULL);
#endif

#ifdef _BOX_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBox *, const char * inDescription = NULL);
#endif

#ifdef _BUFFER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBuffer *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSmallBuffer *, const char * inDescription = NULL);
#endif

#ifdef _BUFFER_CONSUMER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBufferConsumer *, const char * inDescription = NULL);
#endif

#ifdef _BUFFER_GROUP_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBufferGroup *, const char * inDescription = NULL);
#endif

#ifdef _BUFFER_PRODUCER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BBufferProducer *, const char * inDescription = NULL);
#endif

#ifdef _BUTTON_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BButton *, const char * inDescription = NULL);
#endif

#ifdef _CHANNEL_CONTROL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BChannelControl *, const char * inDescription = NULL);
#endif

#ifdef _CHANNEL_SLIDER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BChannelSlider *, const char * inDescription = NULL);
#endif

#ifdef _CHECK_BOX_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BCheckBox *, const char * inDescription = NULL);
#endif

#ifdef _CLIPBOARD_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BClipboard *, const char * inDescription = NULL);
#endif

#ifdef _COLOR_CONTROL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BColorControl *, const char * inDescription = NULL);
#endif

#ifdef _CONTROL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BControl *, const char * inDescription = NULL);
#endif

#ifdef _CONTROL_WEB_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BParameterWeb *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BParameterGroup *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BParameter *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BContinuousParameter *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BDiscreteParameter *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BNullParameter *, const char * inDescription = NULL);
#endif

#ifdef _CONTROLLABLE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BControllable *, const char * inDescription = NULL);
#endif

#ifdef _CONTROL_THEME_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaTheme *, const char * inDescription = NULL);
#endif

#ifdef _CURSOR_H
	//BCursor doesn't really have any available methods to call
#endif

#ifdef _DIGITAL_PORT_H
	//decided against this one: BDigitalPort 
#endif

#ifdef _DIRECTORY_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BDirectory *, const char * inDescription = NULL);
#endif

#ifdef _DIRECT_WINDOW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BDirectWindow *, const char * inDescription = NULL);
#endif

#ifdef _DRAGGER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BDragger *, const char * inDescription = NULL);
#endif

#ifdef _E_MAIL_H
	//BMailMessage has no viable public methods to call to get information on the object
#endif

#ifdef _ENTRY_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BEntry *, const char * inDescription = NULL);
#endif

#ifdef _ENTRY_LIST_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BEntryList *, const char * inDescription = NULL);
#endif

#ifdef _FLATTENABLE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BFlattenable *, const char * inDescription = NULL);
#endif

#ifdef _FILE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BFile *, const char * inDescription = NULL);
#endif

#ifdef _FILE_GAME_SOUND_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BFileGameSound *, const char * inDescription = NULL);
#endif

#ifdef _FILE_PANEL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BFilePanel *, const char * inDescription = NULL);
#endif

#ifdef _FILE_INTERFACE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BFileInterface *, const char * inDescription = NULL);
#endif

#ifdef _FONT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, unicode_block *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BFont *, const char * inDescription = NULL);
#endif

#ifdef _HANDLER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BHandler *, const char * inDescription = NULL);
#endif

#ifdef _INVOKER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BInvoker *, const char * inDescription = NULL);
#endif

#ifdef _INPUT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BInputDevice *, const char * inDescription = NULL);
#endif

#ifdef _JOYSTICK_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BJoystick *, const char * inDescription = NULL);
#endif

#ifdef _LIST_ITEM_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BListItem *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BStringItem *, const char * inDescription = NULL);
#endif

#ifdef _LIST_VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BListView *, const char * inDescription = NULL);
#endif

#ifdef _LOCKER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BLocker *, const char * inDescription = NULL);
#endif

#ifdef _LOOPER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BLooper *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_ADD_ON_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaAddOn *, const char * inDescription = NULL);
#endif

#ifdef MEDIADECODER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaDecoder *, const char * inDescription = NULL);
	//BMediaBufferDecoder doesn't really do enough to warrant tracing
#endif

#ifdef MEDIAENCODER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaEncoder *, const char * inDescription = NULL);
	//BMediaBufferEncoder doesn't do anything really
#endif

#ifdef _MEDIA_EVENT_LOOPER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaEventLooper *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_FILE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaFile *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_FILES_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaFiles *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_NODE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_node *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaNode *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_ROSTER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaRoster *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_TRACK_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaTrack *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_TYPES_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMediaFormats *, const char * inDescription = NULL);
#endif

#ifdef _MENU_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMenu *, const char * inDescription = NULL);
#endif

#ifdef _MENU_BAR_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMenuBar *, const char * inDescription = NULL);
#endif

#ifdef _MENU_FIELD_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMenuField *, const char * inDescription = NULL);
#endif

#ifdef _MENU_ITEM_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMenuItem *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSeparatorItem *, const char * inDescription = NULL);
#endif

#ifdef _MESSAGE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMessage *, const char * inDescription = NULL);
#endif

#ifdef _MESSAGE_FILTER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMessageFilter *, const char * inDescription = NULL);
#endif

#ifdef _MESSAGE_QUEUE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMessageQueue *, const char * inDescription = NULL);
#endif

#ifdef _MESSAGE_RUNNER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMessageRunner *, const char * inDescription = NULL);
#endif

#ifdef _MESSENGER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMessenger *, const char * inDescription = NULL);
#endif

#ifdef _MIDI_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMidi *, const char * inDescription = NULL);
#endif

#ifdef _MIDI_PORT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMidiPort *, const char * inDescription = NULL);
#endif

#ifdef _MIDI_STORE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMidiStore *, const char * inDescription = NULL);
#endif

#ifdef _MIDI_SYNTH_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMidiSynth *, const char * inDescription = NULL);
#endif

#ifdef _MIDI_SYNTH_FILE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMidiSynthFile *, const char * inDescription = NULL);
#endif

#ifdef _MIDI_TEXT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMidiText *, const char * inDescription = NULL);
#endif

#ifdef _MIME_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMimeType *, const char * inDescription = NULL);
#endif

#ifdef _MULTI_CHANNEL_CONTROL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BMultiChannelControl *, const char * inDescription = NULL);
#endif

#ifdef _NODE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BNode *, const char * inDescription = NULL);
#endif

#ifdef _NODE_INFO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BNodeInfo *, const char * inDescription = NULL);
#endif

#ifdef _OPTION_CONTROL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BOptionControl *, const char * inDescription = NULL);
#endif

#ifdef _OPTION_POP_UP_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BOptionPopUp *, const char * inDescription = NULL);
#endif

#ifdef _OUTLINE_LIST_VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BOutlineListView *, const char * inDescription = NULL);
#endif

#ifdef _PATH_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPath *, const char * inDescription = NULL);
#endif

#ifdef _PICTURE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPicture *, const char * inDescription = NULL);
#endif

#ifdef _PICTURE_BUTTON_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPictureButton *, const char * inDescription = NULL);
#endif

#ifdef _POINT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPoint *, const char * inDescription = NULL);
#endif

#ifdef _POLYGON_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPolygon *, const char * inDescription = NULL);
#endif

#ifdef _POP_UP_MENU_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPopUpMenu *, const char * inDescription = NULL);
#endif

#ifdef _PRINTSESSION_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPrintJob *, const char * inDescription = NULL);
#endif

#ifdef _PROPERTY_INFO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPropertyInfo *, const char * inDescription = NULL);
#endif

#ifdef _PUSH_GAME_SOUND_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BPushGameSound *, const char * inDescription = NULL);
#endif

#ifdef _QUERY_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BQuery *, const char * inDescription = NULL);
#endif

#ifdef _RADIO_BUTTON_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BRadioButton *, const char * inDescription = NULL);
#endif

#ifdef _RECT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BRect *, const char * inDescription = NULL);
#endif

#ifdef _REGION_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BRegion *, const char * inDescription = NULL);
#endif

#ifdef _RESOURCE_STRINGS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BResourceStrings *, const char * inDescription = NULL);
#endif

#ifdef RESOURCES_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BResources *, const char * inDescription = NULL);
#endif

#ifdef _ROSTER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BRoster *, const char * inDescription = NULL);
#endif

#ifdef _SAMPLES_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSamples *, const char * inDescription = NULL);
#endif

#ifdef _SCREEN_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BScreen *, const char * inDescription = NULL);
#endif

#ifdef _SCROLL_BAR_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BScrollBar *, const char * inDescription = NULL);
#endif

#ifdef _SCROLL_VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BScrollView *, const char * inDescription = NULL);
#endif

#ifdef _SERIAL_PORT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSerialPort *, const char * inDescription = NULL);
#endif

#ifdef _SHAPE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BShape *, const char * inDescription = NULL);
#endif

#ifdef _SHELF_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BShelf *, const char * inDescription = NULL);
#endif

#ifdef _SIMPLE_GAME_SOUND_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSimpleGameSound *, const char * inDescription = NULL);
#endif

#ifdef _SLIDER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSlider *, const char * inDescription = NULL);
#endif

#ifdef _SOUND_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSound *, const char * inDescription = NULL);
#endif

#ifdef _SOUND_FILE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSoundFile *, const char * inDescription = NULL);
#endif

#ifdef _SOUND_PLAYER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSoundPlayer *, const char * inDescription = NULL);
#endif

#ifdef _STATABLE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BStatable *, const char * inDescription = NULL);
#endif

#ifdef _STATUS_BAR_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BStatusBar *, const char * inDescription = NULL);
#endif

#ifdef _STOP_WATCH_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BStopWatch *, const char * inDescription = NULL);
#endif

#ifdef _STREAMING_GAME_SOUND_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BStreamingGameSound *, const char * inDescription = NULL);
#endif

#ifdef _STRING_VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BStringView *, const char * inDescription = NULL);
#endif

#ifdef _SYM_LINK_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSymLink *, const char * inDescription = NULL);
#endif

#ifdef _SYNTH_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BSynth *, const char * inDescription = NULL);
#endif

#ifdef _TAB_VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTab *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTabView *, const char * inDescription = NULL);
#endif

#ifdef _TEXT_CONTROL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTextControl *, const char * inDescription = NULL);
#endif

#ifdef _TEXTVIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTextView *, const char * inDescription = NULL);
#endif

#ifdef _TIME_CODE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTimeCode *, const char * inDescription = NULL);
#endif

#ifdef _TIMED_EVENT_QUEUE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTimedEventQueue *, const char * inDescription = NULL);
#endif

#ifdef _TIME_SOURCE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTimeSource *, const char * inDescription = NULL);
#endif

#ifdef _TRANSLATOR_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTranslator *, const char * inDescription = NULL);
#endif

#ifdef _TRANSLATOR_ROSTER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BTranslatorRoster *, const char * inDescription = NULL);
#endif

//#ifdef _TRANSLATION_UTILS_H
	//BTranslationUtils doesn't have any available methods that I can call that don't require information
//#endif

#ifdef _VIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BView *, const char * inDescription = NULL);
#endif

#ifdef _VOLUME_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BVolume *, const char * inDescription = NULL);
#endif

#ifdef _VOLUME_ROSTER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BVolumeRoster *, const char * inDescription = NULL);
#endif

#ifdef _WINDOW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, BWindow *, const char * inDescription = NULL);
#endif












































//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS
//STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS STRUCTS

#ifdef _ALERT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, alert_type *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, button_spacing *, const char * inDescription = NULL);
#endif

#ifdef _APP_FILE_INFO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, version_info *, const char * inDescription = NULL);
#endif

#ifdef _BUFFER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, buffer_clone_info *, const char * inDescription = NULL);
#endif

#ifdef _DIRECT_WINDOW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, direct_buffer_info *, const char * inDescription = NULL);
#endif

#ifdef _E_MAIL_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, mail_pop_account *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, mail_notification *, const char * inDescription = NULL);
#endif

#ifdef _ENTRY_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, entry_ref *, const char * inDescription = NULL);
#endif

#ifdef _FONT_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, edge_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, font_height *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, escapement_delta *, const char * inDescription = NULL);
	//font_cache_info is only used internally by BFont
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, tuned_font_info *, const char * inDescription = NULL);
#endif

#ifdef _GAME_SOUND_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, gs_audio_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, gs_attribute *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, gs_attribute_info *, const char * inDescription = NULL);
#endif

#ifdef _GRAPHICS_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, pattern *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, rgb_color *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, color_map *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, overlay_rect_limits *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, overlay_restrictions *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, screen_id *, const char * inDescription = NULL);
#endif

#ifdef _IMAGE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, image_info *, const char * inDescription = NULL);
#endif

#ifdef _INTERFACE_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, key_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, key_map *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, mouse_map *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, scroll_bar_info *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_ADD_ON_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, dormant_node_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, flavor_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, dormant_flavor_info *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_DEFS_H
#if defined(__cplusplus)
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_destination *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_source *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_raw_audio_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_audio_header *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_multi_audio_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_encoded_audio_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_encoded_audio_header *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_video_display_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_raw_video_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_video_header *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_encoded_video_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_encoded_video_header *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_multistream_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_multistream_header *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_seek_tag *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_header_time_code *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_header *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_file_format_id *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_file_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_encode_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, encode_parameters *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_decode_info *, const char * inDescription = NULL);
#endif	//	__cplusplus
#endif

#ifdef _MEDIA_NODE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_input *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_output *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, live_node_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_request_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_node_attribute *, const char * inDescription = NULL);
#endif

#ifdef _MEDIA_TYPES_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_codec_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, GUID *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_beos_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_quicktime_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_avi_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_avr_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_asf_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_mpeg_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_wav_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_aiff_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_misc_description *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_format_description *, const char * inDescription = NULL);
#endif

#ifdef _NODE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, node_ref *, const char * inDescription = NULL);
#endif

#ifdef _MENU_H
	//menu_info is only used internall by the BMenu class
#endif

#ifdef _PROPERTY_INFO_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, compound_type *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, property_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, value_info *, const char * inDescription = NULL);
#endif

#ifdef _OS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, area_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, port_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, sem_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, thread_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, team_usage_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, team_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, platform_type *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, cpu_info *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, system_info *, const char * inDescription = NULL);
#endif

#ifdef _PRINTSESSION_H
	//print_file_header is only used by private members of BPrintJob
#endif

#ifdef _TIMED_EVENT_QUEUE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, media_timed_event *, const char * inDescription = NULL);
#endif

#ifdef _TRANSLATOR_FORMATS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, TranslatorBitmap *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, TranslatorSound *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, TranslatorStyledTextRecordHeader *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, TranslatorStyledTextStreamHeader *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, TranslatorStyledTextTextHeader *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, TranslatorStyledTextStyleHeader *, const char * inDescription = NULL);
#endif

#ifdef _REGION_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, clipping_rect *, const char * inDescription = NULL);
#endif

#ifdef _ROSTER_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, app_info *, const char * inDescription = NULL);
#endif

#ifdef _TEXTVIEW_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, text_run *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, text_run_array *, const char * inDescription = NULL);
#endif

#ifdef _TIME_CODE_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, timecode_info *, const char * inDescription = NULL);
#endif

//#ifdef _WINDOW_SCREEN_H
	//_direct_screen_info_ is only used in private section of BWindowScreen
//#endif

#ifdef _TRANSLATION_DEFS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, translation_format *, const char * inDescription = NULL);
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, translator_info *, const char * inDescription = NULL);
#endif

#ifdef _TRANSLATOR_FORMATS_H
	void TraceObject (ClueCategory, ClueEvent, uint32, const char *, const char *, TranslatorGroups *, const char * inDescription = NULL);
#endif


















	//non-object related functions
	void TraceSimple (ClueCategory, ClueEvent, uint32, const char *, const char *, const char * inDescription = 0, ...);
	void TraceClass (ClueCategory, ClueEvent, uint32, const char *, const char *);

	class TraceMethod
	{
		public:
			TraceMethod (ClueCategory, uint32, const char *, const char *, const char * format = 0, ...);
			~TraceMethod (void);
		private:
			TraceMethod (const TraceMethod &);
			TraceMethod & operator= (TraceMethod &);
		private:
			bigtime_t			m_StartTime;
			const ClueCategory	m_CAT;
			const uint32		m_Line;
			const char *		m_CMDefinition;
			const char *		m_File;
	};

	//These are here for compatibility with older versions, or for easier access, your pick
	#define REPORT_ERROR	CC_GENERAL, CE_ERROR,	__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define REPORT_WARNING	CC_GENERAL, CE_WARNING,	__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define REPORT_INFO		CC_GENERAL, CE_INFO,	__LINE__, __FILE__, __PRETTY_FUNCTION__
	
	//these are the new definitions one should use
	#define CR_OK			CE_OK,			__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_INFO			CE_INFO,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_WARNING		CE_WARNING,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_ERROR		CE_ERROR,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_SUCCEEDED	CE_SUCCEEDED,	__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_FAILED		CE_FAILED,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_ENTER		CE_ENTER,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_EXIT			CE_EXIT,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_TIMER		CE_TIMER,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_BIRTH		CE_BIRTH,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_DEATH		CE_DEATH,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define CR_OBJECT		CE_OBJECT,		__LINE__, __FILE__, __PRETTY_FUNCTION__
	#define REPORT_METHOD	__LINE__,		__FILE__, __PRETTY_FUNCTION__

	#define TRACE_OBJECT(ARGS)	TraceObject	ARGS
	#define TRACE_SIMPLE(ARGS)	TraceSimple	ARGS
	#define TRACE_METHOD(ARGS)	TraceMethod	gsp ARGS
	#define TRACE_CLASS(ARG) \
		class __Trace_Class \
		{ \
			public: \
				__Trace_Class (void) \
				{ \
					TraceClass (ARG, CE_BIRTH, __LINE__, __FILE__, __PRETTY_FUNCTION__); \
				} \
				~__Trace_Class (void) \
				{ \
					TraceClass (ARG, CE_DEATH, __LINE__, __FILE__, __PRETTY_FUNCTION__); \
				} \
		} m_TraceClass

#else //CLUE

	#define TRACE_OBJECT(ARGS) void(0)
	#define TRACE_SIMPLE(ARGS) void(0)
	#define TRACE_METHOD(ARGS) void(0)
	#define TRACE_CLASS(ARG) char ClueNotUsed

#endif //CLUE

#endif // CLUE_H
