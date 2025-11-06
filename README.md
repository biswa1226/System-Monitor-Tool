# 🖥️ System Monitor Tool (Linux)

### 📘 Objective
A simple Linux-based system monitor built in **C++**, which displays real-time CPU usage, memory usage, and running process count by reading data from the `/proc` file system.  
This project was developed as part of the **Wipro Capstone Project (Linux System Programming)**.

---

### ⚙️ Features
- Displays live CPU utilization percentage  
- Shows current memory usage  
- Counts and displays the total number of running processes  
- Refreshes every 3 seconds  

---

### 🧠 Technologies Used
- **C++**
- **Linux (WSL 2 on Windows)**
- **/proc filesystem**

---

### 🚀 How to Run
```bash
g++ main.cpp -o monitor
./monitor
