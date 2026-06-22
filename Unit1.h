//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Dialogs.hpp>
#include <vector>
//---------------------------------------------------------------------------
// —труктура города
struct City {
	int index;   // индекс в массиве
	float x;    // координата X
	float y;    // координата Y
    String name; // название, например "G1"
};

// —труктура маршрута
struct Route {
    int i;          // индекс первого города в массиве cities
    int j;          // индекс второго города в массиве cities
	float length;  // длина маршрута
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPaintBox *PaintBox1;
	TLabel *TitleAddCity;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *EditX;
	TEdit *EditY;
	TButton *ButtonAdd;
	TButton *ButtonDelete;
	TLabel *TitleListCity;
	TPanel *Panel2;
	TListView *ListView1;
	TStatusBar *StatusBar1;
	TButton *Button1;
	TLabel *Label3;
	TLabel *Label4;
	TStringGrid *StringGrid1;
	TPopupMenu *PopupMenu1;
	TMenuItem *N1;
	TMenuItem *N2;
	TButton *Button2;
	TOpenDialog *OpenDialog1;

	void __fastcall StringGrid1MouseUp(TObject *Sender, TMouseButton Button,
		TShiftState Shift, int X, int Y);
	void __fastcall MenuLeftClick(TObject *Sender);
	void __fastcall MenuRightClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall EditXKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditYKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonAddKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PaintBox1Paint(TObject *Sender);
	void __fastcall StringGrid1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	bool __fastcall AddCityFromCoords(float lat, float lng);

private:	// User declarations
	void FindAndShowRoutes();
	void ShowRoutesInGrid(const std::vector<City> &checkedCities, const std::vector<Route> &routes);
	void UpdateStatus(const std::vector<Route> &routes);


	int selectedRoute = -1;          // индекс выбранного маршрута
	std::vector<City> lastCheckedCities; // запоминаем те же города что были при расчЄте
	std::vector<City> GetCheckedCities();
	std::vector<Route> validRoutes;
	std::vector<City> cities;   // список всех городов
	std::vector<Route> routes;  // список найденных маршрутов
    int popupRowMain = -1;

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
