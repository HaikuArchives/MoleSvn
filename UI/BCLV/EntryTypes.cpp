
#include "EntryTypes.h"
#include "../../Config.h"
#include "../../Svn/SvnEntry.h"

#define kTEXT_MARGIN	8

//=====================================================================
BEntryField::BEntryField(const SvnEntry& entry, bool bIsChecked)
:BColoredStringField(entry.GetRelativePath().c_str(), entry.GetStatusColor()), 
 m_bIsChecked(bIsChecked),
 m_Icon(BRect(0,0,15,15), B_RGB32)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
/*
	// Retrieve the tracker icon for this file
	BNode node(entry.GetPath().c_str());
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "node ok"));
	if(node.InitCheck() == B_OK)
	{
		BNodeInfo infos(&node);
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "infos ok"));
		if(infos.GetTrackerIcon(&m_Icon, B_MINI_ICON) != B_OK)
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "GetTrackerIcon failed"));
		}
		else
		{
			TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "GetTrackerIcon ok"));
		}
	}
*/	
}
	
void BEntryField::Check(bool bIsChecked)
{
	m_bIsChecked = bIsChecked;
}

bool BEntryField::IsChecked() const
{
	return m_bIsChecked;
}

//=====================================================================
BEntryColumn::BEntryColumn(const char *title, float width, float maxWidth, float minWidth,
                                             uint32 truncate)
:BColoredStringColumn(title, width, maxWidth, minWidth, truncate)
{
	// Empty	
}

//#define CLUE	// define it for debug session with clue tool
#include "../../Utils/Clue.h"


void BEntryColumn::DrawField(BField *_field, BRect rect, BView *parent)
{
	BEntryField* pField = (BEntryField*)_field;
	BRect CheckboxFrame(rect.left + 3, rect.top + 3, 
	                    rect.left + rect.Height() - 3, rect.top + rect.Height() - 3);

	//////////////////////////////////////////
	// Draw the checkbox
	//////////////////////////////////////////
	rgb_color color;
	color.red = 0;
	color.green = 0;	
	color.blue = 0;
	color.alpha = 255;		
	BPoint p1(CheckboxFrame.left, CheckboxFrame.top);
	BPoint p2(CheckboxFrame.right, CheckboxFrame.top);
	BPoint p3(CheckboxFrame.right, CheckboxFrame.bottom);		
	BPoint p4(CheckboxFrame.left, CheckboxFrame.bottom);	
	
	// Save current pen size
	float fPenSize = parent->PenSize();
	parent->SetPenSize(2.0f);

	rgb_color black={0,0,0};
	parent->SetHighColor(black);
	parent->StrokeRect(BRect(CheckboxFrame.left-1.0f, CheckboxFrame.top-1.0f, 
							 CheckboxFrame.right-1.0f, CheckboxFrame.bottom-1.0f));

	if(pField->IsChecked())
	{
		TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Checked"));
		parent->SetPenSize(1.0f);
		parent->BeginLineArray( 6 );

			parent->AddLine(BPoint(CheckboxFrame.left+3, CheckboxFrame.top+5), BPoint(CheckboxFrame.left+6, CheckboxFrame.top+8), color);
			parent->AddLine(BPoint(CheckboxFrame.left+3, CheckboxFrame.top+6), BPoint(CheckboxFrame.left+5, CheckboxFrame.top+8), color);
			parent->AddLine(BPoint(CheckboxFrame.left+3, CheckboxFrame.top+7), BPoint(CheckboxFrame.left+5, CheckboxFrame.top+9), color);

			parent->AddLine(BPoint(CheckboxFrame.left+9, CheckboxFrame.top+3), BPoint(CheckboxFrame.left+6, CheckboxFrame.top+6), color);
			parent->AddLine(BPoint(CheckboxFrame.left+9, CheckboxFrame.top+4), BPoint(CheckboxFrame.left+6, CheckboxFrame.top+7), color);
			parent->AddLine(BPoint(CheckboxFrame.left+9, CheckboxFrame.top+5), BPoint(CheckboxFrame.left+6, CheckboxFrame.top+8), color);
		
		parent->EndLineArray();	
	}

	// Restore the old size
	parent->SetPenSize(fPenSize);
	
	//////////////////////////////////////////
	// Draw the icon
	//////////////////////////////////////////
	//parent->DrawBitmapAsync(&pField->m_Icon, BPoint(CheckboxFrame.right + 5, 1));
	
	//////////////////////////////////////////
	// Draw the string
	//////////////////////////////////////////
	BRect StringRect(CheckboxFrame.right /*+ pField->m_Icon.Bounds().Width()*/ + 1, CheckboxFrame.top, rect.right, rect.bottom);
	BColoredStringColumn::DrawField(_field, StringRect, parent);
}

int BEntryColumn::CompareFields(BField* field1,BField* field2)
{
	BEntryField* f1 = (BEntryField*)(field1);
	BEntryField* f2 = (BEntryField*)(field2);	
	
	// Look for a / in the name
	string strf1(f1->String());
	string strf2(f2->String());
	//int nf1 = count_if(strf1.begin(), strf1.end(), bind2nd(equal_to<char>(), '/'));
	//int nf2 = count_if(strf2.begin(), strf2.end(), bind2nd(equal_to<char>(), '/'));
	int nf1 = strf1.find('/');
	int nf2 = strf2.find('/');
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Str1 : %s", strf1.c_str()));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Str2 : %s", strf2.c_str()));

	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "nf1 : %d", nf1));
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "nf2 : %d", nf2));
	
	int nRes;
/*	
	if(nf1 != nf2)
	{
		if(nf1 < nf2)
			nRes = -1;
		else
			nRes = 1;
	}
*/	
	
	if(nf1 == -1 && nf2 != -1)
		nRes = -1;
	else if(nf1 != -1 && nf2 == -1)	
		nRes = 1;
	else
	{
		//to_lower(strf1);	// !! don't compile with be stl !! => stlport
		//to_lower(strf2);
		//nRes = strf1.compare(strf2);
		nRes = ICompare(strf1.c_str(), strf2.c_str());
	}

	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "Res : %d", nRes));
	
	return nRes;
}


void BEntryColumn::MouseDown( BColumnListView */*parent*/, BRow */*row*/, BField *field,
									   BRect field_rect, BPoint point, uint32 /*buttons*/)
{
	TRACE_METHOD ((CC_APPLICATION, REPORT_METHOD));
	
	BEntryField* pField = (BEntryField*)(field);
	
	TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, &field_rect, "field_rect"));
	TRACE_OBJECT ((CC_APPLICATION, CR_OBJECT, &point, "point"));
		
	BRect CheckboxFrame(field_rect.left + 2, field_rect.top + 2, 
	                    field_rect.left + field_rect.Height() - 2, field_rect.top + field_rect.Height() - 2);
	                    		
	if( (point.x > CheckboxFrame.left) && (point.x - CheckboxFrame.left < CheckboxFrame.Width()))
	{
		pField->Check(!pField->IsChecked());
	}
	
	TRACE_SIMPLE ((CC_APPLICATION, CR_INFO, "IsChecked : %d  %s", pField->IsChecked(), pField->String()));		

}

void BEntryColumn::MouseUp(BColumnListView */*parent*/, BRow */*row*/, BField */*field*/)
{

}

