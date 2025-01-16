# TypingFrame
第一次学习MFC与尝试编写打字窗口
其实也是第一次使用github上传文件所以乱七八糟的

编译出现问题可能需要右键解决方案中项目，属性，设置，配置管理器中将活动解决方案平台设置为Win32
VisualStudio可以通过打开TypingMode.sln来打开项目

第一次写readme不知道要写啥就这样吧：
main.h与main.cpp：实例化窗口
类Main通过InitInstance中实例化窗口开始执行

TypingFrame.h与TypingFrame.cpp：不同构造方法创建文本与监控键盘鼠标输入与窗口绘制
类TypingFrame：整个窗口主体
无参构造（）：不建议使用，使用默认字符串文本填入打字框内
有参构造（CString）：使用传入参数字符串填入打字框内
有参构造（LPCTSTR）：使用传入地址文本字符串填入打字框内，若文本为空则不进行绘制与键盘读取，只能按下ESC退出
析构函数（）：释放计时器
initFrame（）：初始化窗口，设置数值以及窗口属性
setting（int）：设置是否可以退格删除
OnTimer（）：计时器的一部分（？）更新计时的部分
getCorrentCount（）：写的有点烂，返回正确字符个数
getErrorCount（）：一样写的挺烂的，返回错误字符个数
OnLButtonDown(UINT, CPoint)：监控左键，暂时没用到其实
OnChar(UINT, UINT, UINT)：监控键盘按键，可以输入大小写与回车，Esc可以退出
OnPaint()：绘制窗口
OnMouseWheel(UINT nFlags, short zDelta, CPoint point)：监控滑轮
OnEraseBkgnd(CDC* pDC)：怪不得之前老在闪，原来是默认开启擦除重画，重载关掉就不闪了

textBox.h与textBox.cpp：文本框管理，因为刚开始写的时候不太熟悉运行机制，现在感觉这个数据结构真的有够烂的
类Text

类TextBox
