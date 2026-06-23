#include <vcl.h>
#pragma hdrstop
#include "Unit3.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

__fastcall TForm3::TForm3(TComponent* Owner)
    : TForm(Owner)
{
    Caption = "Справка";
    Width = 600;
    Height = 500;

    // --- Вкладка 1: Задание ---
    RichEdit1->ReadOnly = true;
    RichEdit1->Lines->Clear();
    RichEdit1->Lines->Add("ЗАДАНИЕ");
    RichEdit1->Lines->Add("");
    RichEdit1->Lines->Add(
        "На территории страны есть K (чётное количество) городов с "
        "координатами X и Y. Необходимо найти все возможные прямые "
        "железные дороги между двумя городами такие, что слева и "
        "справа от дороги оказалось одинаковое количество городов.");
    RichEdit1->Lines->Add("");
    RichEdit1->Lines->Add(
        "Города, лежащие на самой прямой, не считаются ни левыми, "
        "ни правыми. Маршруты выводятся отсортированными по длине "
        "от меньшей к большей.");

    // --- Вкладка 2: Интерфейс ---
    RichEdit2->ReadOnly = true;
    RichEdit2->Lines->Clear();
    RichEdit2->Lines->Add("ОПИСАНИЕ ИНТЕРФЕЙСА");
    RichEdit2->Lines->Add("");
    RichEdit2->Lines->Add("Добавить город");
    RichEdit2->Lines->Add(
        "  X, Y — поля ввода координат города.");
    RichEdit2->Lines->Add(
        "  Добавить — добавляет город в список и на карту.");
    RichEdit2->Lines->Add(
        "  Удалить — удаляет выбранный в списке город.");
    RichEdit2->Lines->Add("");
    RichEdit2->Lines->Add("Список городов");
    RichEdit2->Lines->Add(
        "  Checkbox — включает/выключает город из расчёта.");
    RichEdit2->Lines->Add(
        "  Рассчитать — находит все подходящие маршруты.");
    RichEdit2->Lines->Add(
        "  Очистить — удаляет все города и маршруты.");
    RichEdit2->Lines->Add("");
    RichEdit2->Lines->Add("Карта городов");
    RichEdit2->Lines->Add(
        "  Синие точки — активные города.");
    RichEdit2->Lines->Add(
        "  Серые точки — выключенные города (рядом с активными).");
    RichEdit2->Lines->Add(
        "  Красная линия — выбранный маршрут.");
    RichEdit2->Lines->Add("");
    RichEdit2->Lines->Add("Возможные маршруты");
    RichEdit2->Lines->Add(
        "  Клик левой кнопкой — подсветить маршрут на карте.");
    RichEdit2->Lines->Add(
        "  Клик правой кнопкой — открыть подмножество городов "
        "слева или справа от маршрута.");

    // --- Вкладка 3: Как пользоваться ---
    RichEdit3->ReadOnly = true;
    RichEdit3->Lines->Clear();
    RichEdit3->Lines->Add("КАК ПОЛЬЗОВАТЬСЯ");
    RichEdit3->Lines->Add("");
    RichEdit3->Lines->Add("1. Добавление городов вручную:");
    RichEdit3->Lines->Add("   — Введите X и Y в поля ввода.");
    RichEdit3->Lines->Add("   — Нажмите кнопку Добавить.");
    RichEdit3->Lines->Add("   — Повторите для всех городов.");
    RichEdit3->Lines->Add("");
    RichEdit3->Lines->Add("2. Загрузка из файла:");
    RichEdit3->Lines->Add("   — Нажмите кнопку загрузки файла.");
    RichEdit3->Lines->Add(
        "   — Файл должен содержать по одному городу на строке: X Y");
    RichEdit3->Lines->Add("   — Пример: 10 20");
    RichEdit3->Lines->Add("");
    RichEdit3->Lines->Add("3. Расчёт маршрутов:");
    RichEdit3->Lines->Add(
        "   — Отметьте нужные города галочками в списке.");
    RichEdit3->Lines->Add(
        "   — Количество отмеченных городов должно быть чётным.");
    RichEdit3->Lines->Add("   — Нажмите кнопку Рассчитать.");
    RichEdit3->Lines->Add("");
    RichEdit3->Lines->Add("4. Просмотр маршрутов:");
    RichEdit3->Lines->Add(
        "   — Кликните по маршруту — линия подсветится на карте.");
    RichEdit3->Lines->Add(
        "   — Правый клик — откроется окно с подмножеством городов "
		"слева или справа, где можно рекурсивно найти маршруты.");

}


