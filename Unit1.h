//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>






//---------------------------------------------------------------------------
// —труктура города
struct City {
	int index;   // индекс в массиве
	double x;    // координата X
	double y;    // координата Y
	int index;
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


	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);


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
	TButton *Button3;
	TLabel *Label3;
	TLabel *Label4;
	TStringGrid *StringGrid1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall ButtonDeleteClick(TObject *Sender);
	void __fastcall EditXKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EditYKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ButtonAddKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:	// User declarations
	void FindAndShowRoutes();
    void ShowRoutesInGrid(const std::vector<Route> &routes);
	void UpdateStatus(const std::vector<Route> &routes);

	std::vector<Route> validRoutes;
	std::vector<City> cities;   // список всех городов
    std::vector<Route> routes;  // список найденных маршрутов

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
