//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <vector>
#include "Unit1.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:
    TPaintBox *PaintBox1;
    TLabel *Label3;
    TLabel *Label4;
    TStringGrid *StringGrid1;
    TStatusBar *StatusBar1;
    TPopupMenu *PopupMenu1;
    TMenuItem *N1;
    TMenuItem *N2;

    void __fastcall PaintBox1Paint(TObject *Sender);
    void __fastcall StringGrid1Click(TObject *Sender);
    void __fastcall StringGrid1MouseUp(TObject *Sender, TMouseButton Button,
        TShiftState Shift, int X, int Y);
    void __fastcall MenuLeftClick(TObject *Sender);
    void __fastcall MenuRightClick(TObject *Sender);

private:
    std::vector<City> cities;
    std::vector<Route> routes;
    int selectedRoute = -1;
    int popupRow = -1;

    void CalculateRoutes();
    void ShowRoutesInGrid();
    void OpenSubset(bool leftSide);

public:
    __fastcall TForm2(TComponent* Owner, const std::vector<City> &inputCities);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
#endif
