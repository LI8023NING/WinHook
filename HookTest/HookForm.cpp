//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HookForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define WM_KEY_HOOK    WM_USER+200  //自定义消息

TFormWinHook *FormWinHook = NULL;

extern "C" {
 BOOL APIENTRY StartKeyHook(); //安装鼠标钩子
 BOOL APIENTRY EndHook();   //删除钩子
}

//---------------------------------------------------------------------------
__fastcall TFormWinHook::TFormWinHook(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormWinHook::BtnStartHookClick(TObject *Sender)
{
    StartKeyHook();
}
//---------------------------------------------------------------------------


void __fastcall TFormWinHook::BtnStopHookClick(TObject *Sender)
{
    EndHook();
}
//---------------------------------------------------------------------------

void _fastcall TFormWinHook::WndProc(Messages::TMessage &Message)
{
    unsigned int ulMsgId;
    unsigned int ulMsgLen;
    AnsiString msg;

    switch (Message.Msg)
    {
        case WM_KEY_HOOK:
        {
            OnKeyHook(Message);
        }
        break;
        default:
        {
            TForm::WndProc(Message);
            break;
        }
    }
}

void __fastcall TFormWinHook::OnKeyHook(TMessage &Msg)
{
    AnsiString str =  "键盘事件:[" ;
    char key[20]={0};
    GetKeyNameText(Msg.WParam, key, 20);
    str += key;

    str += "]";

    MemoShowKeyDown->Lines->Add(str);
}

void __fastcall TFormWinHook::FormClose(TObject *Sender, TCloseAction &Action)
{
    EndHook();
}
//---------------------------------------------------------------------------
