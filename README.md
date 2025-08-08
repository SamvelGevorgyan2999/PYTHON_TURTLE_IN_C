# 🐢 Turtle Graphics in C (SDL2)

## 📖 Description
This project is a **Turtle Graphics library** written in **C** using the **SDL2** library.  
It is inspired by Python's `turtle` module and provides a simple way to create drawings by moving a "turtle" cursor around the screen.

The turtle moves according to commands such as `forward()`, `left()`, or `penup()`, drawing lines when the pen is down.  
This implementation supports animated step-by-step drawing, color changes, adjustable drawing speeds, and the ability to quit in the middle of execution.  

It’s great for:
- Learning basic computer graphics
- Understanding event loops and rendering in C
- Building fun, interactive drawing demos

---

## ✨ Features

- Basic movement: `forward()`, `backward()`, `left()`, `right()`
- Pen control: `penup()`, `pendown()`
- Set pen color: `setcolor(r, g, b)`
- Change background color: `bgcolor(r, g, b)`
- Change drawing speed: `setspeed(1–10)`
- Clear and reset functions
- Quit anytime during drawing:
  - Press **Esc** or **Q**
  - Close the window
- Step-by-step animated drawing (like Python's turtle)
- Written in **pure C** with **SDL2**

---

## 📦 Requirements

- **SDL2 development library**
- GCC or any C compiler
- CMake (optional, for building)

### Install SDL2 on Linux (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install libsdl2-dev
