# 🎵 MusicPlayer

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-5%20%7C%206-green.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.16+-brightgreen.svg)](https://cmake.org/)

**MusicPlayer** 是一款基于 Qt 框架开发的轻量级本地音乐播放器，支持 MP3 和 WAV 格式，提供简洁的播放列表管理和三种播放模式，适合日常听歌使用。

---

## ✨ 功能特性

- 📂 **目录导入** – 一键选择音乐文件夹，自动扫描并列出所有 `.mp3` 和 `.wav` 文件。
- ▶️ **基本播放控制** – 播放 / 暂停、上一曲、下一曲，双击列表曲目直接播放。
- 🔁 **三种播放模式** – 顺序播放、单曲循环、随机播放，点击模式按钮循环切换。
- 🎚️ **音量调节** – 悬停音量按钮显示垂直滑块，直观调整音量（0~100%）。
- ⏱️ **进度控制** – 显示当前播放位置与总时长，拖动滑块可跳转至任意时间点。
- 🎨 **简洁 UI** – 使用 Qt 原生控件，风格简约，无多余装饰。

---

## 🖥️ 支持平台

- Windows（10/11，x64）
- Linux（Ubuntu 20.04+，或其他发行版）
- macOS（10.15+，需自行编译）

> 由于项目使用 Qt 的多媒体模块，请确保系统安装了相应的音频后端（如 Windows 的 DirectShow，Linux 的 PulseAudio 或 ALSA）。

---

## 📦 构建与安装

### 依赖项

- CMake **3.16** 或更高版本
- Qt **5.15** 或 **Qt 6**（包含 `Widgets` 和 `Multimedia` 模块）
- C++17 兼容的编译器（MSVC 2019+、GCC 9+、Clang 10+）

### 从源码编译

1. 克隆仓库
   ```bash
   git clone https://github.com/yours-kang/MusicPlayer.git
   cd MusicPlayer
   ```

2. 使用 CMake 配置并构建
   ```bash
   mkdir build && cd build
   cmake .. -DCMAKE_PREFIX_PATH=<你的Qt安装路径>   # 若Qt不在系统默认路径，需指定
   cmake --build . --config Release
   ```

3. 运行
   - Windows：在 `build/Release/` 下找到 `MusicPlayer.exe`
   - Linux/macOS：在 `build/` 下找到可执行文件 `MusicPlayer`

---

## 🚀 快速使用

1. 启动程序，点击左上角的 **文件夹图标** 选择存放音乐的目录。
2. 文件列表将显示所有 MP3/WAV 文件，双击任意曲目即可播放。
3. 底部控制栏：
   - **播放/暂停**：中央圆形按钮
   - **上一曲 / 下一曲**：左右箭头按钮
   - **播放模式**：循环切换（顺序 → 单曲循环 → 随机 → 顺序...）
   - **音量**：悬停音量图标，垂直滑块自动出现，滑动调节
4. 进度条：拖动可跳转，左侧显示当前时间，右侧显示总时长。

> 注意：若播放列表为空，播放/暂停按钮不会有响应。

---

## 🛠️ 技术栈

- **语言**：C++17
- **框架**：Qt（Widgets + Multimedia）
- **构建工具**：CMake
- **音频解码**：Qt Multimedia 后端（基于系统多媒体框架）

---

## 📸 截图

*（建议添加实际运行截图，例如在根目录创建 `screenshots` 文件夹，放入 `main.png` 后取消下面一行的注释）*

<!-- ![主界面](screenshots/main.png) -->

---

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！在贡献前请确保：

- 代码风格与现有保持一致
- 如果新增功能，请适当更新文档
- 提交前通过本地构建测试

---

## 📄 许可证

本项目采用 [MIT License](LICENSE) 开源协议，您可以自由使用、修改和分发。

---

## 📧 联系与鸣谢

- 作者：Crispy Sausage
- 项目地址：[https://github.com/yours-kang/MusicPlayer](https://github.com/yours-kang/MusicPlayer)

感谢 Qt 社区提供的强大框架，以及所有开源贡献者的支持。

---

**如果这个播放器帮到了你，请给个 ⭐ 支持一下！**