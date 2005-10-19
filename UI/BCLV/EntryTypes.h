#ifndef _ENTRY_TYPES_H_
#define _ENTRY_TYPES_H_


class SvnEntry;
#include "ColoredStringTypes.h"


//=====================================================================
// Field and column classes for checkbox string.
class BEntryField : public BColoredStringField 
{
public:

							BEntryField(const SvnEntry& entry, 
										bool bIsChecked);
		virtual				~BEntryField(){};
	
		void 				Check				(bool bIsChecked);
			// Description : set the check state of the field

		bool 				IsChecked			() const;
			// Description : return true if the field is checked, false otherwise
	
private:
		bool 				m_bIsChecked;
		BBitmap				m_Icon;
		friend class BEntryColumn;
};

class BEntryColumn : public BColoredStringColumn 
{
public:

							BEntryColumn(const char *title, 
										 float width, 
										 float maxWidth, 
										 float minWidth,
										 uint32 truncate);
		virtual 			~BEntryColumn(){};
		
		virtual void 		DrawField			 (BField *_field, 
												  BRect rect, 
												  BView *parent);

		virtual int			CompareFields		(BField* field1,
												 BField* field2);
												 
		virtual void		MouseDown(BColumnListView *parent, BRow *row, BField *field,
						              BRect field_rect, BPoint point, uint32 buttons);
		virtual	void		MouseUp(BColumnListView *parent, BRow *row, BField *field);												 
											  
private:

};


//=====================================================================
// Field and column classes for checkbox string.
class BEntryStatusField : public BColoredStringField 
{
public:

							BEntryStatusField(const SvnEntry& entry, 
										bool bIsChecked);
		virtual				~BEntryStatusField(){};
	
		void 				Check				(bool bIsChecked);
			// Description : set the check state of the field

		bool 				IsChecked			() const;
			// Description : return true if the field is checked, false otherwise
	
private:
		bool 				m_bIsChecked;
		BBitmap				m_Icon;
		friend class BEntryColumn;
};

class BEntryStatusColumn : public BColoredStringColumn 
{
public:

							BEntryStatusColumn(const char *title, 
										 float width, 
										 float maxWidth, 
										 float minWidth,
										 uint32 truncate);
		virtual 			~BEntryStatusColumn(){};
		
		virtual void 		DrawField			 (BField *_field, 
												  BRect rect, 
												  BView *parent);

		virtual int			CompareFields		(BField* field1,
												 BField* field2);
												 
		virtual void		MouseDown(BColumnListView *parent, BRow *row, BField *field,
						              BRect field_rect, BPoint point, uint32 buttons);
		virtual	void		MouseUp(BColumnListView *parent, BRow *row, BField *field);												 
											  
private:

};



#endif //_ENTRY_TYPES_H_
