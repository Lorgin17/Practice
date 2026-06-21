object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 358
  ClientWidth = 822
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object PaintBox1: TPaintBox
    Left = 0
    Top = 29
    Width = 400
    Height = 300
    OnPaint = PaintBox1Paint
  end
  object Label3: TLabel
    Left = 0
    Top = 8
    Width = 79
    Height = 15
    Caption = #1050#1072#1088#1090#1072' '#1075#1086#1088#1086#1076#1086#1074
  end
  object Label4: TLabel
    Left = 414
    Top = 8
    Width = 129
    Height = 15
    Caption = #1042#1086#1079#1084#1086#1078#1085#1099#1077' '#1084#1072#1088#1096#1088#1091#1090#1099
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 339
    Width = 822
    Height = 19
    Panels = <>
    SimplePanel = True
    ExplicitLeft = -2
    ExplicitTop = 422
    ExplicitWidth = 626
  end
  object StringGrid1: TStringGrid
    Left = 414
    Top = 29
    Width = 402
    Height = 300
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect, goFixedRowDefAlign]
    PopupMenu = PopupMenu1
    TabOrder = 1
    OnClick = StringGrid1Click
    ColWidths = (
      64
      64
      64
      64
      64)
  end
  object PopupMenu1: TPopupMenu
    Left = 736
    object N1: TMenuItem
      Caption = #1051#1077#1074#1086#1077' '#1087#1086#1076#1084#1085#1086#1078#1077#1089#1090#1074#1086
      OnClick = MenuLeftClick
    end
    object N2: TMenuItem
      Caption = #1055#1088#1072#1074#1086#1077' '#1087#1086#1076#1084#1085#1086#1078#1077#1089#1090#1074#1086
      OnClick = MenuRightClick
    end
  end
end
