# Task01
1. **Ventoy工具下载和使用**  
按照 [【windows折腾日记】装系统教学，手把手教怎么制作U盘启动系统盘，Ventoy工具下载和使用_ventoy制作启动u盘-CSDN博客](https://blog.csdn.net/u010560236/article/details/123006741)教程完成学习，将`ubuntu-20.04.5-desktop-amd64.iso` 文件拷贝进 U 盘后，始终进不了BIOS页面。通过客服询问和电脑型号搜索的方法，成功关闭了安全启动，并进入了菜单页面。
2. **Ubuntu系统安装**  
按照第一版任务书完成Ubuntu系统的安装，因此一开始未进行系统盘格式的检测（在安装完成后才进行检测，所幸系统盘格式就是GPT，安装过程没有报错）。整个过程没有任何问题，与任务书内容一致。
3. **更换软件源与语言**  
按照任务书的流程更改软件源为清华源，并且成功更改了语言和英文路径（wins系统被中文路径折磨了很久）。但是在后续下载软件过程中，发现有很多包不适用于清华源，于是调整为中科大源（可能原因是一开始我清华源没配置好，没更新）。
4. **基础设置调整**  
按照[【安装Ubuntu22.04后要做的10件事】](https://www.bilibili.com/video/BV1Cg411X7MN/?share_source=copy_web&vd_source=8ba41477294e884c447883ac4efe6231) 进行基础页面和设置调整。基础设置调整之后发现电脑分辨率太高，导致整个界面字体，图标都很小。先是在**system setting**里的**display**调整**scale**，发现只有整百的变化，200%看起来非常大，不太实用。随后在 [有关Ubuntu系统更改字体大小的方法](https://zhuanlan.zhihu.com/p/560978054) 教程中下载了***gnome-tweaks***（发现清华源下载不了），调整scale至125%。
5. **软件安装**  
通过[【Linux QQ的安装与使用 - RWang的文章 - 知乎】]( https://zhuanlan.zhihu.com/p/643946782) 学习了Linux系统下qq的安装，微信貌似仍然没有官方版本可以下载。 在 [Ubuntu安装软件有这5种方法](https://zhuanlan.zhihu.com/p/270908077) 中总结了五种下载方式 ：  
	1. *appstore下载*  
	2. *apt指令下载*  
	3. *snap指令安装*  
	4. *dpkg指令安装deb包*  
	5. *使用源码编译安装*
---
