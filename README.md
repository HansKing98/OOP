# OOP

🛸面向对象程序设计

## 配置文件说明

### tasks.json

这个文件的作用是编译C/C++源码。首先快捷键shift+command+p 打开Tasks: Configure Tasks，选择 Create tasks.json file from templates，此时会蹦出一个下拉列表，在下拉列表中选择Others，这个时候tasks.json文件就会自动生成啦。这个配置文件是长这个样子的：

```json
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [{
        "label": "echo", // 任务名称，与launch.json的preLaunchTask相对应
        "type": "shell", // process是vsc把预定义变量和转义解析后直接全部传给command；shell相当于先打开shell再输入命令，所以args还会经过shell再解析一遍
        "command": "g++", // 要使用的编译器，C++用g++
        "args": [
            "-g", // 生成和调试有关的信息
            "${file}", // 当前活动的文档名
            // "${fileDirname}/compute/add.cpp", // 指定路径下的待编译文档
            "-o", // 指定输出文件名，不加该参数则默认输出 xxx.exe，Linux / Mac下默认 xxx.out
            "${fileDirname}/${fileBasenameNoExtension}.out",
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
        }
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

### launch.json

该文件的作用是为了可以让我们愉快地调试代码的啦。首先找到虫子的图标，然后点击设置的按钮，在蹦出来的选项中选择C++ (GDB/LLDB)，就像图片中这个样子：

```json
{
    // 使用 IntelliSense 了解相关属性。
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(lldb) 启动",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}.out",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "lldb"
        }
    ]
}
```

参数的简单说明

* “name”：配置名称，将会在启动配置的下拉菜单中显示

* “type”：配置类型

* “request”：请求配置类型，可以为launch（启动）或attach（附加）

* “program”：进行调试的程序的路径

* “stopAtEntry”：若设置为true时程序将暂停在程序入口处

* “cwd”：当前调试所在目录

* “externalConsole”：调试时是否显示控制台窗口，设置为true即是显示控制台

更加详细的解释见Github中关于launch.json文件的说明

上面的步骤全部完成之后，首先切换到two_sum.cpp，快捷键command+shift+b对源文件进行编译，编译成功之后，按下F5，我们便可以愉快地调试啦。成功调试的图如下：
