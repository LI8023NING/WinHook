# 一、概述:
　　钩子(Hook)，是Windows消息处理机制的一个平台,应用程序可以在上面设置子程以监视指定窗口的某种消息，而且所监视的窗口可以是其他进程所创建的。当消息到达后，在目标窗口处理函数之前处理它。钩子机制允许应用程序截获处理window消息或特定事件。
　　钩子实际上是一个处理消息的程序段，通过系统调用，把它挂入系统。每当特定的消息发出，在没有到达目的窗口前，钩子程序就先捕获该消息，亦即钩子函数先得到控制权。这时钩子函数即可以加工处理（改变）该消息，也可以不作处理而继续传递该消息，还可以强制结束消息的传递。

# 二、原理
　　钩子的本质是一段用以处理系统消息的程序，通过系统调用，将其挂入到系统。钩子的种类有很多（比如键盘钩子，鼠标钩子等），每一种钩子负责截获并处理相应的消息。钩子机制允许应用程序截获并处理发往指定窗口的消息或特定事件。在特定消息发出，并在到达目的窗口之前，钩子程序先行截获此消息并得到对其的控制权。此时在预先设定好的钩子函数中可以对截获的消息进行各种修改处理，甚至强行终止该消息的继续传递。

　　任何一个钩子都由系统来维护一个指针列表（钩子链表），其指针指向钩子的各个处理函数，最近安装的钩子放在链表的开始，最早安装的钩子则放在最后，当钩子监视程序出现时，操作系统调用链表的最近钩子处理函数，也就是说，最后加入的钩子将获得优先控制权。另外钩子的处理函数必须是一个回调函数（callback function）,而且不能定义为类成员函数，必须为普通的C函数。

　　使用钩子时可以根据其监视范围的不同将其分为全局钩子和线程钩子，其中线程钩子只能监视某个线程，而全局钩子则可以对当前系统下运行的所有线程进行监视，显然，线程钩子可以看做是全局钩子的一个子集，全局钩子虽然功能比较强大但同时实现起来比较繁琐，比如钩子实现函数必须封装在动态链接库中才可以使用。

# 三、函数介绍
## 1. SetWindowsHookEx()

   把一个应用程序定义的钩子线程安装到钩子链表中，该函数总是在Hook链表的开头安装

      HHOOK SetWindowsHookEx(

          int idHook;

          HOOKPROC lpfn;

          HINSTANCE hMod;

          DWORD dwThreadld);
     }

参数idHook指定了钩子的类型，总共有如下13中

•	WH_C ALLWNDPROC 和WH_CALLWNDPROCRET HOOK可以监视SendMessage发送的消息。系统在向窗体过程发送消息前，将调用WH_CALLWNDPROC；在窗体过程处理完该消息后系统将调用WH_CALLWNDPROCRET。  
•	WH_CALLWNDPROCRET HOOK会向HOOK过程传送一个CWPRETSTRUCT结构的地址。该结构包含了窗体过程处理系统消息后的一些信息。  
•	WH_CALLWNDPROCRET HOOK会向HOOK过程传送一个CWPRETSTRUCT结构的地址。该结构包含了窗体过程处理系统消息后的一些信息。  
•	WH_DEBUG HOOK 系统在调用与某种HOOK类型联系的HOOK过程前，将调用WH_DEBUG ，应用程序可以使用该HOOK决定是否让系统执行某种类型的HOOK。  
•	WH_FOREGROUNDIDLE Hook系统在空闲时调用该HOOK，在后台执行优先权较低的应用程序。  
•	WH_GETMESSAGE Hook使应用程序可以拦截GetMessage 或 PeekMessage的消息。应用程序使用WH_GETMESSAGE 监视鼠标、键盘输入和发送到队列中的其它消息。  
•	WH_JOURNALRECORD Hook使应用程序可以监视输入事件。典型地，应用程序使用该HOOK记录鼠标、键盘输入事件以供以后回放。该HOOK是全局HOOK，并且不能在指定线程中使用。  
•	WH_JOURNALPLAYBACK Hook使应用程序可以向系统消息队列中插入消息。该HOOK可以回放以前由WH_JOURNALRECORD HOOK录制的鼠标、键盘输入事件。在WH_JOURNALPLAYBACK Hook安装到系统时，鼠标、键盘输入事件将被屏蔽。该HOOK同样是一个全局HOOK，不能在指定线程中使用。
WH_JOURNALPLAYBACK Hook返回一个时间暂停值，它告诉系统，在处理当前回放的消息时，系统等待百分之几秒。这使得此HOOK可以控制在回放时的时间事件。  
•	WH_KEYBOARD Hook使应用程序可以监视由GetMessage和PeekMessage返回的WM_KEYDOWN 及WM_KEYUP消息。应用程序使用该HOOK监视发送到消息队列中的键盘输入。  
•	WH_MOUSE Hook 使应用程序可以监视由GetMessage和PeekMessage返回的消息。应用程序使用该HOOK监视发送到消息队列中的鼠标输入。  
•	WH_MSGFILTER 和WH_SYSMSGFILTER Hooks使应用程序可以监视菜单、滚动条、消息框、对话框，当用户使用ALT+TAB或ALT+ESC来切换窗体时，该HOOK也可以拦截到消息。WH_MSGFILTER仅在应用程序内部监视菜单、滚动条、消息框、对话框，而WH_SYSMSGFILTER则可以在系统内监视所有应用程序的这些事件。  
•	WH_SHELL Hook
一个SHELL程序可以使用WH_SHELL Hook来接收重要的信息。当一个SHELL程序被激活前或当前窗体被创建、消毁时，系统会调用WH_SHELL Hook过程

参数lpfn指定了钩子处理函数的指针，即回调函数的首地址；

参数hMod则标识了钩子处理函数所处模块的句柄；对于线程钩子，该实参为NULL，对于全局（系统）钩子，该参数为钩子函数所在的DLL句柄，比如HHOOK glhHook=NULL; 

第四个参数dwThreadId 指定被监视的线程，如果明确指定了某个线程的ID就只监视该线程，此时的钩子即为线程钩子；如果该参数被设置为0，则表示此钩子为监视系统所有线程的全局钩子。此函数在执行完后将返回一个钩子句柄。

示例 glhHook=SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,glhInstance,0);返回值是一个已定义的HINSTANCE实例句柄。

## 2、CallNextHookEx()

     在SetWindowsHookEx()函数完成对钩子的安装后，如果被监视的事件发生，系统马上会调用位于相应钩子链表开始处的钩子处理函数进行处理，每一个钩子处理函数在进行相应的处理时都要考虑是否需要把事件传递给下一个钩子处理函数。如果要传递，就通过函数CallNestHookEx()来解决。尽管如此，在实际使用时还是强烈推荐无论是否需要事件传递而都在过程的最后调用一次CallNextHookEx( )函数，否则将会引起一些无法预知的系统行为或是系统锁定。该函数将返回位于钩子链表中的下一个钩子处理过程的地址，至于具体的返回值类型则要视所设置的钩子类型而定。该函数的原型声明如下：
LRESULT CallNextHookEx(HHOOK hhk;int nCode;WPARAM wParam;LPARAM lParam);
　　其中，参数hhk为由SetWindowsHookEx()函数返回的当前钩子句柄；参数nCode为传给钩子过程的事件代码；参数wParam和lParam 则为传给钩子处理函数的参数值，其具体含义同设置的钩子类型有关。

    示例：return CallNextHookEx( glhHook, nCode, wParam, lParam );

## 3、UnhookWindowsHookEx()

      最后，由于安装钩子对系统的性能有一定的影响，所以在钩子使用完毕后应及时将其卸载以释放其所占资源。释放钩子的函数为UnhookWindowsHookEx()，该函数比较简单只有一个参数用于指定此前由SetWindowsHookEx()函数所返回的钩子句柄，原型声明如下：
BOOL UnhookWindowsHookEx(HHOOK hhk);

最后，为更清楚展示HOOK技术在VC编程中的应用，给出一个有关鼠标钩子使用的简单示例。在钩子设置时采用的是全局钩子。下面就对鼠标钩子的安装、使用以及卸载等过程的实现进行讲述：
　　由于本例程需要使用全局钩子，因此首先构造全局钩子的载体--动态链接库。考虑到　Win32 DLL与Win16 DLL存在的差别，在Win32环境下要在多个进程间共享数据，就必须采取一些措施将待共享的数据提取到一个独立的数据段，并通过def文件将其属性设置为读写共享：
  
    #pragma data_seg("TestData")
    HWND glhPrevTarWnd=NULL; // 窗口句柄
    HWND glhHook=NULL; // 鼠标钩子句柄
    HINSTANCE glhInstance=NULL; // DLL实例句柄
    
    #pragma data_seg()
    ……
    SECTIONS // def文件中将数据段TestData设置为读写共享
    TestData READ WRITE SHARED 
　　 在安装全局鼠标钩子时使用函数SetWindowsHookEx()，并设定鼠标钩子的处理函数为MouseProc()，安装函数返回的钩子句柄保存于变量glhHook中：
	void StartHook(HWND hWnd)
	{
		……
		glhHook=(HWND)SetWindowsHookEx(WH_MOUSE,MouseProc,glhInstance,0);
	} 
　　鼠标钩子安装好后，在移动、点击鼠标时将会发出鼠标消息，这些消息均经过消息处理函数MouseProc()的拦截处理。在此，每当捕获到系统各线程发出的任何鼠标消息后首先获取当前鼠标所在位置下的窗口句柄，并进一步通过GetWindowText()函数获取到窗口标题。在处理函数完成后，通过CallNextHookEx()函数将事件传递到钩子列表中的下一个钩子处理函数：


    LRESULT WINAPI MouseProc(int nCode,WPARAM wParam,LPARAM lParam)
    {
    LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *) lParam;
    if(nCode>=0)
    {
    HWND glhTargetWnd=pMouseHook->hwnd; 
    //取目标窗口句柄 
    HWND ParentWnd=glhTargetWnd; 
    while(ParentWnd !=NULL)
    {
    glhTargetWnd=ParentWnd; 
    //取应用程序主窗口句柄 
    ParentWnd=GetParent(glhTargetWnd); 
    } 
    if(glhTargetWnd!=glhPrevTarWnd) 
    { 
    char szCaption[100]; 
    //取目标窗口标题 
    GetWindowText(glhTargetWnd,szCaption,100); 
    ……
    } 
    }
    //继续传递消息 
    return CallNextHookEx((HHOOK)glhHook,nCode,wParam,lParam); 
    } 
      最后，调用UnhookWindowsHookEx()函数完成对钩子的卸载：
    void StopHook()
    {
    ……
    UnhookWindowsHookEx((HHOOK)glhHook);
    } 
　　现在完成的是鼠标钩子的动态链接库，经过编译后需要经应用程序的调用才能实现对当前系统下各线程间鼠标消息的拦截处理。这部分同普通动态链接库的使用没有任何区别，在将其加载到进程后，首先调用动态链接库的StartHook()函数安装好钩子，此时即可对系统下的鼠标消息实施拦截处理，在动态链接库被卸载即终止鼠标钩子时通过动态链接库中的StopHook()函数卸载鼠标钩子。
　　经上述编程，在安装好鼠标钩子后，鼠标在移动到系统任意窗口上时，马上就会通过对鼠标消息的拦截处理而获取到当前窗口的标题。实验证明此鼠标钩子的安装、使用和卸载过程是正确的。
# 小结
　　钩子，尤其是系统钩子具有相当强大的功能，通过这种技术可以对几乎所有的Windows系统消息和事件进行拦截处理。这种技术广泛应用于各种自动监控系统对进程外消息的监控处理。本文只对钩子的一些基本原理和一般的使用方法做了简要的探讨，感兴趣的读者完全可以在本文所述代码基础之上用类似的方法实现对诸如键盘钩子、外壳钩子等其他类型钩子的安装与使用。本文所述代码在Windows 98下由Microsoft Visual C++ 6.0编译通过。


