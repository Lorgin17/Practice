//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
// Конструктор принимает уже готовое подмножество городов
__fastcall TForm2::TForm2(TComponent* Owner, const std::vector<City> &inputCities)
    : TForm(Owner)
{
	cities = inputCities;

	// Перенумероация
    for (int i = 0; i < (int)cities.size(); i++)
        cities[i].index = i;

    StringGrid1->ColCount = 3;
    StringGrid1->RowCount = 2;
    StringGrid1->FixedRows = 1;
    StringGrid1->Cells[0][0] = "№";
    StringGrid1->Cells[1][0] = "Маршрут";
    StringGrid1->Cells[2][0] = "Длина";
    StringGrid1->ColWidths[0] = 30;
    StringGrid1->ColWidths[1] = 250;
    StringGrid1->ColWidths[2] = 100;
    StringGrid1->Options = StringGrid1->Options << goRowSelect;

    StatusBar1->SimplePanel = true;

    CalculateRoutes();
}

// Логика расчётов
static float Side2(const City &A, const City &B, const City &P) {
	return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}
static float Distance2(const City &A, const City &B) {
	float dx = B.x - A.x, dy = B.y - A.y;
	return sqrt(dx*dx + dy*dy);
}
static bool ValidCity2(const std::vector<City> &c, int A, int B) {
	int need = ((int)c.size() - 2) / 2;
	int left = 0, right = 0;
	for (int k = 0; k < (int)c.size(); k++) {
		if (k == A || k == B) continue;
		float s = Side2(c[A], c[B], c[k]);
		if (s > 0) left++;
		else if (s < 0) right++;
	}
	return (left == need && right == need);
}

void TForm2::CalculateRoutes()
{
    routes.clear();
    int n = (int)cities.size();

    if (n < 2 || n % 2 != 0) {
        StatusBar1->SimpleText = "В подмножестве должно быть чётное число городов (мин. 2)";
        StringGrid1->RowCount = 2;
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ValidCity2(cities, i, j)) {
                Route r;
                r.i = i;
                r.j = j;
                r.length = Distance2(cities[i], cities[j]);
                routes.push_back(r);
            }
        }
    }

    // Сортировка
    for (int i = 0; i < (int)routes.size() - 1; i++)
        for (int j = 0; j < (int)routes.size() - i - 1; j++)
            if (routes[j].length > routes[j+1].length)
                std::swap(routes[j], routes[j+1]);

    ShowRoutesInGrid();
    StatusBar1->SimpleText = "Маршрутов в подмножестве: " + IntToStr((int)routes.size());
}

void TForm2::ShowRoutesInGrid()
{
    StringGrid1->RowCount = (int)routes.size() + 1;
    for (int r = 0; r < (int)routes.size(); r++) {
        StringGrid1->Cells[0][r+1] = IntToStr(r+1);
        StringGrid1->Cells[1][r+1] = cities[routes[r].i].name + " — " + cities[routes[r].j].name;
        StringGrid1->Cells[2][r+1] = FloatToStrF(routes[r].length, ffFixed, 6, 2);
    }
}

// Клик левой кнопкой — выбрать маршрут для подсветки
void __fastcall TForm2::StringGrid1Click(TObject *Sender)
{
    int row = StringGrid1->Row;
    if (row > 0 && row - 1 < (int)routes.size()) {
        selectedRoute = row - 1;
        PaintBox1->Invalidate();
    }
}

// Клик правой кнопкой — запомнить строку под курсором перед показом меню
void __fastcall TForm2::StringGrid1MouseUp(TObject *Sender, TMouseButton Button,
	TShiftState Shift, int X, int Y)
{
    if (Button == mbRight) {
        int col, row;
        StringGrid1->MouseToCell(X, Y, col, row);
        if (row > 0 && row - 1 < (int)routes.size()) {
            popupRow = row - 1;
            selectedRoute = popupRow;
            PaintBox1->Invalidate();
        } else {
            popupRow = -1;
        }
    }
}

void __fastcall TForm2::MenuLeftClick(TObject *Sender)
{
    OpenSubset(true);
}

void __fastcall TForm2::MenuRightClick(TObject *Sender)
{
    OpenSubset(false);
}

// Открыть новое окно TForm2 с подмножеством слева/справа от дороги
void TForm2::OpenSubset(bool leftSide)
{
        ShowMessage("popupRow = " + IntToStr(popupRow) +
                ", routes.size = " + IntToStr((int)routes.size()));
	if (popupRow < 0 || popupRow >= (int)routes.size()) return;

    const Route &rt = routes[popupRow];
    const City &A = cities[rt.i];
    const City &B = cities[rt.j];

    std::vector<City> subset;
    for (int k = 0; k < (int)cities.size(); k++) {
        if (k == rt.i || k == rt.j) continue; // сами A и B не входят
        float s = Side2(A, B, cities[k]);
        if (leftSide && s > 0) subset.push_back(cities[k]);
        if (!leftSide && s < 0) subset.push_back(cities[k]);
    }

    if (subset.empty()) {
        ShowMessage("В этом подмножестве нет городов");
        return;
    }

	TForm2 *child = new TForm2(Owner, subset);
	child->Caption = leftSide ? "Левое подмножество" : "Правое подмножество";
	child->Show();
	child->BringToFront();
}

// Отрисовка
void __fastcall TForm2::PaintBox1Paint(TObject *Sender)
{
    TCanvas *cv = PaintBox1->Canvas;
    int W = PaintBox1->Width;
    int H = PaintBox1->Height;

    cv->Brush->Color = clWhite;
    cv->FillRect(Rect(0, 0, W, H));

    if (cities.empty()) return;

    float minX = cities[0].x, maxX = cities[0].x;
    float minY = cities[0].y, maxY = cities[0].y;
    for (auto &c : cities) {
        if (c.x < minX) minX = c.x;
        if (c.x > maxX) maxX = c.x;
        if (c.y < minY) minY = c.y;
        if (c.y > maxY) maxY = c.y;
    }

    int margin = 25;
    double rangeX = (maxX - minX) > 0 ? (maxX - minX) : 1.0;
    double rangeY = (maxY - minY) > 0 ? (maxY - minY) : 1.0;

    auto toSX = [&](double x) -> int {
        return margin + (int)((x - minX) / rangeX * (W - 2 * margin));
    };
    auto toSY = [&](double y) -> int {
        return H - margin - (int)((y - minY) / rangeY * (H - 2 * margin));
    };

    int activeA = -1, activeB = -1;
    if (selectedRoute >= 0 && selectedRoute < (int)routes.size()) {
        activeA = routes[selectedRoute].i;
        activeB = routes[selectedRoute].j;

        int x1 = toSX(cities[activeA].x), y1 = toSY(cities[activeA].y);
        int x2 = toSX(cities[activeB].x), y2 = toSY(cities[activeB].y);

        cv->Pen->Color = clRed;
        cv->Pen->Width = 2;
        cv->Pen->Style = psDash;
        cv->MoveTo(x1, y1);
        cv->LineTo(x2, y2);
        cv->Pen->Style = psSolid;
        cv->Pen->Width = 1;
    }

    int r = 5;
    for (int k = 0; k < (int)cities.size(); k++) {
        const City &c = cities[k];
        int sx = toSX(c.x), sy = toSY(c.y);
        bool isActive = (k == activeA || k == activeB);

        if (isActive) {
            cv->Pen->Color   = clRed;
            cv->Pen->Width   = 3;
            cv->Brush->Color = clYellow;
        } else {
            cv->Pen->Color   = clNavy;
            cv->Pen->Width   = 1;
            cv->Brush->Color = clBlue;
        }

        cv->Ellipse(sx - r, sy - r, sx + r, sy + r);
        cv->Pen->Width = 1;

        cv->Brush->Style = bsClear;
        cv->Font->Color  = clBlack;
        cv->Font->Style  = isActive ? TFontStyles() << fsBold : TFontStyles();
        cv->TextOut(sx + r + 2, sy - r - 2, c.name);
        cv->Font->Style  = TFontStyles();
        cv->Brush->Style = bsSolid;
    }
}
