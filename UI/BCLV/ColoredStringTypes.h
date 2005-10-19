#ifndef _COLOREDSTRING_TYPES_H_
#define _COLOREDSTRING_TYPES_H_

#include "../3rd/BCLV/ColumnTypes.h"

//=====================================================================
// Field and column classes for colored strings.

class BColoredStringField : public BStringField
{
	public:
							BColoredStringField(const char* string,
												const rgb_color& color);
		virtual				~BColoredStringField (){};
				
		const rgb_color&	GetColor() const;
		void 				SetColor(const rgb_color& color);

	private:
		rgb_color			m_Color;
};

//--------------------------------------------------------------------

class BColoredStringColumn : public BStringColumn
{
public:
							BColoredStringColumn(const char *title,
												 float width,
												 float maxWidth,
												 float minWidth,
												 uint32 truncate,
												 alignment align = B_ALIGN_LEFT);
	    virtual				~BColoredStringColumn(){};
		virtual void		DrawField			(BField* field,
												 BRect rect,
												 BView* parent);

protected:

};

#endif //_COLOREDSTRING_TYPES_H_
