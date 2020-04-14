# Mac OS Catalina, VS Code 搭建c/c++基本开发环境

## 1) 安装 vscode 和 c++对应插件

**安装以下两个插件**

​	1.c++
​	2.CodeLLDB 最关键的是CodeLLDB，解决了Catalina对系统lldb的不兼容问题。

![image-20200414105448768](https://image.hansking.cn/uPic/202004/cLrsEf.png)

![image-20200414105510618](https://image.hansking.cn/uPic/202004/wKX0Vr.png)

## 2) 安装 xcode

不装会报错 `missing xcrun at: /Library/Developer/CommandLineTools/usr/bin/xcrun `

```bash
xcode-select --install
```

解决方法，重装xcode command line：

```csharp
xcode-select --install
```

如果没有解决问题，执行以下命令

```csharp
sudo xcode-select -switch
```

## 3) 配置环境

### c_cpp_properties.json

打开一个保护.cpp文件的文件夹（没有就自己创建）
“command+shift+p”打开命令行工具窗口，输入或者选择**Edit Configurations**命令。

![image-20200414105830031](https://image.hansking.cn/uPic/202004/oDgETB.png)

此时会在当前工作空间目录生成.vscode配置目录，同时在配置目录会生成一个c_cpp_properties.json文件。

配置include目录：

```json
{
    "configurations": [{
        "name": "Mac",
        "includePath": [
            "${workspaceFolder}/**",
            "/Library/Developer/CommandLineTools/usr/include/c++/v1",
            "/usr/local/include",
            "/Library/Developer/CommandLineTools/usr/lib/clang/11.0.3/include", //这行提示不存在请填写自己安装对应的版本 ：打开访达（Finder），按键盘快捷键“Command+Shift+G”, 打开对话框,输入到版本号之前目录
            "/Library/Developer/CommandLineTools/usr/include",
            "/usr/include"
        ],
        "defines": [],
        "macFrameworkPath": [
            "/System/Library/Frameworks",
            "/Library/Frameworks"
        ],
        "compilerPath": "/usr/bin/clang",
        "cStandard": "c11",
        "cppStandard": "c++17",
        "intelliSenseMode": "clang-x64"
    }],
    "version": 4
}
```

### task.json 编译环境

这个文件的作用是编译C/C++源码。


“command+shift+p”打开命令行工具窗口，输入或者选择**Tasks: Configure Task**

![image-20200414110500575](https://image.hansking.cn/uPic/202004/RDR8Md.png)

此时会在.vscode配置目录，会生成一个task.json文件。

task.json 配置如下：

```json
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [{
        "label": "Build with Clang", // 任务名称，与launch.json的preLaunchTask相对应
        "type": "shell", // process是vsc把预定义变量和转义解析后直接全部传给command；shell相当于先打开shell再输入命令，所以args还会经过shell再解析一遍
        "command": "clang++", // 要使用的编译器：clang++
        "args": [
            "-g", // 生成和调试有关的信息
            "-std=c++17",
            "-stdlib=libc++",
            "${fileDirname}/${fileBasenameNoExtension}.cpp", // cpp源文件路径【文件夹路径/文件名】
            // "${fileDirname}/compute/add.cpp", // 指定路径下的待编译文档
            "-o", // 指定输出文件名，不加该参数则默认输出 xxx.exe，Linux / Mac下默认 xxx.out
            "${fileDirname}/${fileBasenameNoExtension}.out", // 编译出文件路径【文件夹路径/执行文件】
            "--debug",
            "-Wall", // 开启额外警告
        ],
        "group": {
            "kind": "build",
            "isDefault": true // 不为true时ctrl shift B就要手动选择了
        },
        "presentation": {
            "echo": true,
            "reveal": "always", // 执行任务时是否跳转到终端面板，可以为always，silent，never。具体参见VSC的文档
            "focus": false, // 设为true后可以使执行task时焦点聚集在终端，但对编译C/C++来说，设为true没有意义
            "panel": "shared" // 不同的文件的编译信息共享一个终端面板
        },
    }]
}
```

参数的简单说明

* “label”：任务的名称

* “type”：任务的类型，有两种（shell/process），shell的意思相当于先打开shell再输入命令，process是直接运行命令

* “command”：实际执行的命令

* “args”：在这里可以设置一些需要的参数，比如说这里我设置的四个参数中，

* “-o”，表示指定输出文件名，如果不加该参数则默认Windows下输出a.exe，Linux/MAC下默认a.out，紧接着的一行即为指定的输出文件名

* “-g”，C/C++调试必备参数

更加详细的解释见[VS Code官方文档关于tasks.json][1]的说明

官方文档中还给出了[GitHub中的tasks.json模版][2]

[1]: https://code.visualstudio.com/docs/editor/tasks "tasks.json"
[2]: https://github.com/Microsoft/vscode-docs/blob/a54d7741bd661d5f284c8f090a2a00f3e6b46c28/docs/editor/tasks-appendix.md

### launch.json 编译环境

该文件的作用是为了可以让我们愉快地调试代码的啦。首先找到虫子的图标，然后点击设置的按钮，在蹦出来的选项中选择C++ (GDB/LLDB)，就像图片中这个样子：

“command+shift+p”打开命令行工具窗口，输入或者选择**Debug: Open launch.json**命令。

![image-20200414112031974](https://image.hansking.cn/uPic/202004/esfx1e.png)

此时会在.vscode配置目录，会生成一个launch.json文件。

launch.json 配置如下：

```json
{
    // 使用 IntelliSense 了解相关属性。
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [{
        "name": "(lldb) 启动",
        "type": "lldb",
        "request": "launch",
        "program": "${fileDirname}/${fileBasenameNoExtension}.out",
        "args": [],
        "cwd": "${workspaceFolder}",
        "preLaunchTask": "Build with Clang"
    }]
}
```

参数的简单说明

- “name”：配置名称，将会在启动配置的下拉菜单中显示
- “type”：配置类型
- “request”：请求配置类型，可以为launch（启动）或attach（附加）
- “program”：进行调试的程序的路径
- “stopAtEntry”：若设置为true时程序将暂停在程序入口处
- “cwd”：当前调试所在目录
- “externalConsole”：调试时是否显示控制台窗口，设置为true即是显示控制台

更加详细的解释见Github中关于launch.json文件的说明

## 4) 开始调试

上面的步骤全部完成之后，首先切换到main.cpp（自己创建），快捷键command+shift+b对源文件进行编译**（如果这步报错请检查task.json和c_cpp_properties.json）**

### 成功编译的图如下：

### ![image-20200414112930710](https://image.hansking.cn/uPic/202004/Tjz7Sm.png)

编译成功之后，按下F5或者下图的启动按钮，我们便可以愉快地调试啦（中途可能会提醒控制终端，需要赋予权限，允许即可）。

![image-20200414113021244](https://image.hansking.cn/uPic/202004/oNpyGO.png)

### 成功调试的图如下：

F5 之后弹出空白的终端控制台 

第一行输入 10 （空格/回车）11 （回车）

第二行为输出语句

![image-20200414113114624](https://image.hansking.cn/uPic/202004/FgrlSH.png)

### 测试代码： main.cpp

```c++
#include <iostream>
using namespace std;

int main()
{
    int a, b;
    cin >> a >> b;
    cout << a << " + " << b << " = " << a + b << endl;

    return 0;
}
```

最后如果终端有类似的提示，输入回车结束终端调用。

**可能遇到的问题**：
可能遇到

“xcrun: error: invalid active developer path (/Library/Developer/CommandLineTools), missing xcrun at: /Library/Developer/CommandLineTools/usr/bin/xcrun”

这样的报错，

终端输入命令：
```sudo xcode-select --switch /Applications/Xcode.app```

setting.json

```json
{
    "files.associations": {
        "ostream": "cpp",
        "algorithm": "cpp",
        "iostream": "cpp",
        "system_error": "cpp",
        "bitset": "cpp",
        "typeinfo": "cpp",
        "ratio": "cpp"
    }
}
```


