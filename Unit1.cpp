//---------------------------------------------------------------------------
#include <cmath>
#include <vector>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;




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
	int need = ((int)cities.size() - 2) / 2;
	int left = 0, right = 0;
	for (int k = 0; k < (int)cities.size(); k++) {
		if (k == A || k == B) continue;
		float c = Side(cities[A], cities[B], cities[k]); //1
		if      (c > 0) left++;
		else if (c < 0) right++;
		// c == 0 — на прямой, не считаем
	}
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
void TForm1::ShowRoutesInGrid(const std::vector<Route> &routes)
{
    // +1 потому что строка 0 — это заголовок
    StringGrid1->RowCount = (int)routes.size() + 1;

    for (int r = 0; r < (int)routes.size(); r++) {
        const Route &rt = routes[r];

        // Колонка 0 — номер маршрута
		StringGrid1->Cells[0][r + 1] = IntToStr(r + 1);

        // Колонка 1 — названия двух городов
        StringGrid1->Cells[1][r + 1] =
            cities[rt.i].name + " — " + cities[rt.j].name;

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


//Функция. Итоговая FindAndShowRoutes — просто склейка
void TForm1::FindAndShowRoutes()
{
    int n = (int)cities.size();

    if (n < 2) {
        ShowMessage("Нужно минимум 2 города");
        return;
    }
    if (n % 2 != 0) {
        ShowMessage("Количество городов должно быть чётным");
        return;
    }

	routes = CollectRoutes(cities);   // 4
	SortRoutes(routes);               // 5
	ShowRoutesInGrid(routes);         // 6
	UpdateStatus(routes);             // 7
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	FindAndShowRoutes();
}
//---------------------------------------------------------------------------

