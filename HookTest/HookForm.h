//---------------------------------------------------------------------------

#ifndef HookFormH
#define HookFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

//---------------------------------------------------------------------------
class TFormWinHook : public TForm
{
__published:	// IDE-managed Components
    TMemo *MemoShowKeyDown;
    TButton *BtnStartHook;
    TButton *BtnStopHook;
    void __fastcall BtnStartHookClick(TObject *Sender);
    void __fastcall BtnStopHookClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
    __fastcall TFormWinHook(TComponent* Owner);
    void _fastcall WndProc(Messages::TMessage &Message);

    void __fastcall OnKeyHook(TMessage &Msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormWinHook *FormWinHook;
//---------------------------------------------------------------------------
#endif
