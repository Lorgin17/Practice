#ifndef Unit3H
#define Unit3H

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

class TForm3 : public TForm
{
__published:
    TPageControl *Задание;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TRichEdit *RichEdit1;
    TRichEdit *RichEdit2;
    TRichEdit *RichEdit3;

public:
    __fastcall TForm3(TComponent* Owner);
};

extern PACKAGE TForm3 *Form3;
#endif
