//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonAddClick(TObject *Sender)
{
	// Валидация ввода
	float x, y;
    try {
        x = StrToFloat(EditX->Text);
		y = StrToFloat(EditY->Text);
    } catch (...) {
        StatusBar1->SimpleText = "Ошибка: введите числа!";
        return;
    }

    City c;
    c.x = x;
    c.y = y;
    c.index = cities.size();
    cities.push_back(c);

	// Добавить в ListView
    TListItem *item = ListView1->Items->Add();
	item->Caption = "G" + IntToStr((int)cities.size());
	item->SubItems->Add("X: " + FloatToStr(x));
	item->SubItems->Add("Y: " + FloatToStr(y));

    EditX->Text = "";
    EditY->Text = "";
    StatusBar1->SimpleText = "Городов: " + IntToStr(int(cities.size()));

	PaintBox1->Invalidate(); // перерисовать карту
}
//---------------------------------------------------------------------------

