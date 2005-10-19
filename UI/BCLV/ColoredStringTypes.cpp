
#include "../Config.h"
#include "ColoredStringTypes.h"

//=====================================================================

BColoredStringField::BColoredStringField(const char* string,
										 const rgb_color& color)
:BStringField(string),
 m_Color(color)
{

}

//--------------------------------------------------------------------
const rgb_color& BColoredStringField::GetColor() const
{
	return m_Color;
}

//--------------------------------------------------------------------
void BColoredStringField::SetColor(const rgb_color& color)
{
	m_Color = color;
}

//--------------------------------------------------------------------
BColoredStringColumn::BColoredStringColumn(	const char *title,
										 	float width,
											float maxWidth,
											float minWidth,
											uint32 truncate,
											alignment align)
:BStringColumn(title, width, maxWidth, minWidth, truncate, align)
{

}


//--------------------------------------------------------------------
void BColoredStringColumn::DrawField(BField* field,
									 BRect rect,
									 BView* parent)
{
	BColoredStringField* pField = (BColoredStringField*)field;
	parent->SetHighColor(pField->GetColor());
	BStringColumn::DrawField(field, rect, parent);
}

