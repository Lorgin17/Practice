//---------------------------------------------------------------------------
#include <cmath>
#include <vector>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

//===========================БЛОК РАССЧЕТОВ ДОРОГ============================

//Функция 1. Векторное произведение, знак определяет сьторону города относительно прямой
// > 0 — точка P слева от прямой A->B
// < 0 — справа
// = 0 — на прямой
float Side(const City &A, const City &B, const City &P){
return (B.x - A.x) * (P.y -A.y) - (B.y - A.y) * (P.x - A.x);
}
//Функция 2. расстояние между двумя городами
float Distance(const City &A, const City &B)
{
	float dx = B.x - A.x;
	float dy = B.y - A.y;
    return sqrt(dx*dx + dy*dy);
}
//Функция 3. Возвращает true, если прямая через города A и B
// делит остальные города ровно пополам
// (коллинеарные не считаются)
bool ValidCity(const std::vector<City> &cities, int A, int B)
{
	int left = 0, right = 0;
	for (int k = 0; k < (int)cities.size(); k++) {
		if (k == A || k == B) continue;
		float c = Side(cities[A], cities[B], cities[k]); //1
		if      (c > 0) left++;
        else if (c < 0) right++;
		// c == 0 — коллинеарный, не считаем вообще
	}
    int nonCollinear = left + right;
    if (nonCollinear % 2 != 0) return false;
	int need = nonCollinear / 2;
	return (left == need && right == need);
}


//Функция 4. Перебирает все пары городов и возвращает только подходящие
std::vector<Route> CollectRoutes(const std::vector<City> &cities)
{
    std::vector<Route> result;
    int n = (int)cities.size();

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
			if (ValidCity(cities, i, j)) {        //3
				Route r;
                r.i = i;
				r.j = j;
				r.length = Distance(cities[i], cities[j]); //2
				result.push_back(r);
			}
		}
	}

    return result;
}

// Функция 5. Сортировка маршрутов по длине
void SortRoutes(std::vector<Route> &routes)
{
	int n = (int)routes.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (routes[j].length > routes[j + 1].length) {
                // меняем местами
                Route temp   = routes[j];
                routes[j]     = routes[j + 1];
                routes[j + 1] = temp;
            }
        }
    }
}


//Функция 6. Вывод маршрутов
void TForm1::ShowRoutesInGrid(const std::vector<City> &checkedCities, const std::vector<Route> &routes)
{
    // +1 потому что строка 0 — это заголовок
    StringGrid1->RowCount = (int)routes.size() + 1;

    for (int r = 0; r < (int)routes.size(); r++) {
        const Route &rt = routes[r];

        // Колонка 0 — номер маршрута
		StringGrid1->Cells[0][r + 1] = IntToStr(r + 1);
        // Колонка 1 — названия двух городов
		StringGrid1->Cells[1][r + 1] = checkedCities[rt.i].name + " — " + checkedCities[rt.j].name;
        // Колонка 2 — длина, 2 знака после запятой
		StringGrid1->Cells[2][r + 1] = FloatToStrF(rt.length, ffFixed, 6, 2);
    }
}


//Функция 7. Обновить статусбар
void TForm1::UpdateStatus(const std::vector<Route> &routes)
{
    if (routes.empty())
        StatusBar1->SimpleText = "Подходящих маршрутов не найдено";
    else
        StatusBar1->SimpleText =
            "Найдено маршрутов: " + IntToStr((int)routes.size());
}


//Функция 8. Проверить видимость
 std::vector<City> TForm1::GetCheckedCities()
{
    std::vector<City> checked;
    for (int i = 0; i < ListView1->Items->Count; i++) {
        if (ListView1->Items->Item[i]->Checked) {
            checked.push_back(cities[i]);
        }
    }
    return checked;
}
//Функция. Итоговая FindAndShowRoutes — просто склейка
void TForm1::FindAndShowRoutes()
{
     // Очистить предыдущие результаты
    routes.clear();
    StringGrid1->RowCount = 2;
    StringGrid1->Cells[0][1] = "";
    StringGrid1->Cells[1][1] = "";
    StringGrid1->Cells[2][1] = "";
    selectedRoute = -1;
    PaintBox1->Invalidate();
    std::vector<City> checkedCities = GetCheckedCities();
    int n = (int)checkedCities.size();

    if (n < 2) {
        ShowMessage("Нужно минимум 2 отмеченных города");
        return;
    }
    if (n % 2 != 0) {
        ShowMessage("Количество отмеченных городов должно быть чётным");
        return;
    }

    routes = CollectRoutes(checkedCities);
    SortRoutes(routes);
    lastCheckedCities = checkedCities;   // сохранить для PaintBox
    selectedRoute = -1;                  // сбросить выбор
    ShowRoutesInGrid(checkedCities, routes);
    UpdateStatus(routes);
	PaintBox1->Invalidate();
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// Настройка StringGrid
    StringGrid1->ColCount = 3;
	StringGrid1->RowCount = 2;
    StringGrid1->FixedRows = 1;
	StringGrid1->FixedCols = 0;

	StringGrid1->Cells[0][0] = "№";
	StringGrid1->Cells[1][0] = "Маршрут";
	StringGrid1->Cells[2][0] = "Длина";
	StringGrid1->Width = 486;
	StringGrid1->ColWidths[0] = 30;
	StringGrid1->ColWidths[1] = 250;
	StringGrid1->ColWidths[2] = 200;

    // Настройка PaintBox — белый фон
    PaintBox1->Canvas->Brush->Color = clWhite;
    PaintBox1->Canvas->FillRect(
	Rect(0, 0, PaintBox1->Width, PaintBox1->Height));

	//Настройка ListView1
    StatusBar1->SimplePanel = True;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	FindAndShowRoutes();
}
// Функция добавления города в список ListView (работает)
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

    City c;     // Структура для города
    c.x = x;
	c.y = y;
	c.index = (int)cities.size();
	c.name = "G" + IntToStr((int)cities.size() + 1);
    // Проверка на дублирование координат
	for (int i = 0; i < (int)cities.size(); i++) {
		if (cities[i].x == x && cities[i].y == y) {
			StatusBar1->SimpleText = "Ошибка: город с такими координатами уже существует!";
			return;
		}
	}

	cities.push_back(c);

	TListItem *item = ListView1->Items->Add();
	item->Caption = "G" + IntToStr((int)cities.size());
	item->Checked = true;
	item->SubItems->Add("X: " + FloatToStr(x));
	item->SubItems->Add("Y: " + FloatToStr(y));

    EditX->Text = "";
    EditY->Text = "";
    StatusBar1->SimpleText = "Городов: " + IntToStr(int(cities.size()));

    EditX->SetFocus();
	PaintBox1->Invalidate(); // перерисовать карту
}
//---------------------------------------------------------------------------
// Функция удаления города из списка (работает)
void __fastcall TForm1::ButtonDeleteClick(TObject *Sender)
{
	if (ListView1->Selected == nullptr) return;    // Если не выбрана строка
	int idx = ListView1->Selected->Index;          // Индекс выбранной строки
	cities.erase(cities.begin() + idx);            // Удаление из vector
	ListView1->Items->Delete(idx);                 // Удаление из ListView

	// Перенумерация элементов
	for (int i = 0; i < (int)cities.size(); i++) {
        cities[i].index = i;
        cities[i].name = "G" + IntToStr(i + 1);
        ListView1->Items->Item[i]->Caption = "G" + IntToStr(i + 1);
    }

    // Очистка путей и PaintBox
    routes.clear();
	PaintBox1->Invalidate();
	StatusBar1->SimpleText = "Городов: " + IntToStr((int)cities.size());
}
//---------------------------------------------------------------------------
// Нажатие на Enter/стрелки при вводе в EditX
void __fastcall TForm1::EditXKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_RETURN || Key == VK_DOWN) {
        EditY->SetFocus();
        Key = 0; // подавить стандартное поведение
	}
	if (Key == VK_UP) {
        ButtonDelete->SetFocus();
	}
}
//---------------------------------------------------------------------------
// Нажатие на Enter/стрелки при вводе в EditY
void __fastcall TForm1::EditYKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_RETURN || Key == VK_DOWN) {
        ButtonAdd->SetFocus();
        Key = 0;
    }
    if (Key == VK_UP) {
        EditX->SetFocus();
        Key = 0;
    }
}
//---------------------------------------------------------------------------
// Нажатие на Enter/стрелки на кнопке "Добавить"
void __fastcall TForm1::ButtonAddKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_UP) {
		EditY->SetFocus();
		Key = 0;
	}
	if (Key == VK_DOWN) {
		ButtonDelete->SetFocus();
		Key = 0;
	}
}

// Функция отрисовки на PaintBox
void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{
	TCanvas *cv = PaintBox1->Canvas;
    int W = PaintBox1->Width;
    int H = PaintBox1->Height;

    cv->Brush->Color = clWhite;
    cv->Pen->Style = psSolid;
    cv->FillRect(Rect(0, 0, W, H));

    if (cities.empty()) return;


    // Границы координат только отмеченных городов
	std::vector<City> checked = GetCheckedCities();
	if (checked.empty()) return;

	float minX = checked[0].x, maxX = checked[0].x;
	float minY = checked[0].y, maxY = checked[0].y;
	for (auto &c : checked) {
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


    int activeIdxA = -1, activeIdxB = -1; // индексы в cities (по имени)
	if (selectedRoute >= 0 && selectedRoute < (int)routes.size()) {
        const Route &rt = routes[selectedRoute];
        const City &cA = lastCheckedCities[rt.i];
        const City &cB = lastCheckedCities[rt.j];

        // Найти эти же города в общем списке cities (по имени, т.к. индексы разные)
        for (int k = 0; k < (int)cities.size(); k++) {
            if (cities[k].name == cA.name) activeIdxA = k;
            if (cities[k].name == cB.name) activeIdxB = k;
        }

        if (activeIdxA >= 0 && activeIdxB >= 0) {
            int x1 = toSX(cities[activeIdxA].x), y1 = toSY(cities[activeIdxA].y);
            int x2 = toSX(cities[activeIdxB].x), y2 = toSY(cities[activeIdxB].y);

            cv->Pen->Color = clRed;
            cv->Pen->Width = 2;
            cv->Pen->Style = psDash;
            cv->MoveTo(x1, y1);
            cv->LineTo(x2, y2);
            cv->Pen->Style = psSolid;
            cv->Pen->Width = 1;
		}
	}
	// --- Города ---
int r = 5;
for (int k = 0; k < (int)cities.size(); k++) {
    const City &c = cities[k];
    bool isChecked = ListView1->Items->Item[k]->Checked;
    int sx = toSX(c.x);
    int sy = toSY(c.y);
    bool isActive = (k == activeIdxA || k == activeIdxB);

    if (!isChecked) {
        // Рисуем серым только если попадает в видимую область
        if (sx >= margin && sx <= W - margin &&
            sy >= margin && sy <= H - margin) {
            cv->Pen->Color   = clGray;
            cv->Pen->Width   = 1;
            cv->Brush->Color = clSilver;
            cv->Ellipse(sx - 3, sy - 3, sx + 3, sy + 3);
            cv->Brush->Style = bsClear;
            cv->Font->Color  = clGray;
            cv->TextOut(sx + 5, sy - 5, c.name);
            cv->Brush->Style = bsSolid;
        }
        continue;
    }

    if (isActive) {
        cv->Pen->Color   = clRed;
        cv->Pen->Width   = 3;
        cv->Brush->Color = clYellow;
	}
	else {
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
//---------------------------------------------------------------------------
// Отрисовка маршрутов
    void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
    int row = StringGrid1->Row;
    if (row > 0 && row - 1 < (int)routes.size()) {
        selectedRoute = row - 1;
        PaintBox1->Invalidate();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1MouseUp(TObject *Sender, TMouseButton Button,
    TShiftState Shift, int X, int Y)
{
    if (Button == mbRight) {
        int col, row;
        StringGrid1->MouseToCell(X, Y, col, row);
        if (row > 0 && row - 1 < (int)routes.size()) {
            popupRowMain = row - 1;
            selectedRoute = popupRowMain;
            PaintBox1->Invalidate();
        } else {
            popupRowMain = -1;
        }
    }
}

void __fastcall TForm1::MenuLeftClick(TObject *Sender)
{
    if (popupRowMain < 0) return;
    const Route &rt = routes[popupRowMain];
    const City &A = lastCheckedCities[rt.i];
    const City &B = lastCheckedCities[rt.j];

    std::vector<City> subset;
    for (auto &c : lastCheckedCities) {
        if (c.name == A.name || c.name == B.name) continue;
        float s = Side(A, B, c); // используем существующую функцию Side из Unit1
        if (s > 0) subset.push_back(c);
    }
    if (subset.empty()) { ShowMessage("Нет городов слева"); return; }

    TForm2 *child = new TForm2(Application, subset);
    child->Caption = "Левое подмножество";
    child->Show();
}

void __fastcall TForm1::MenuRightClick(TObject *Sender)
{
    if (popupRowMain < 0) return;
    const Route &rt = routes[popupRowMain];
    const City &A = lastCheckedCities[rt.i];
    const City &B = lastCheckedCities[rt.j];

    std::vector<City> subset;
    for (auto &c : lastCheckedCities) {
        if (c.name == A.name || c.name == B.name) continue;
        float s = Side(A, B, c);
        if (s < 0) subset.push_back(c);
    }
    if (subset.empty()) { ShowMessage("Нет городов справа"); return; }

    TForm2 *child = new TForm2(Application, subset);
    child->Caption = "Правое подмножество";
    child->Show();
}
