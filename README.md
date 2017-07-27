# jx3pass
过剑网3保护
其实原理就是在游戏启动之前HOOK  ZwSetInformationThread这个函数，PASS掉ThreadHideFromDebugger来让调试器能够正常接收异常 
 
EXE部分 jx3 文件夹
DLL部分 jx3dll 文件夹

解压到游戏“zhcn”目录下，运行“Jx3EXE.exe”启动游戏之后，OD和CE能够正常下断点调试了 

项目 VC6.0
