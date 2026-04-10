# 🚀 Mini Embedded Shell in C

A custom Linux shell implementation built using **C and System Programming concepts**, designed to mimic core functionalities of a Unix shell with additional modular design and command handling.

---

## 📌 Features

* ✅ Custom command execution (`ls`, `cd`, etc.)
* ✅ Path display (like real Linux shell)
* ✅ Support for system calls (`fork`, `exec`, `wait`)
* ✅ Pipe handling between processes
* ✅ Modular project structure (`src/`, `include/`, `lib/`)
* ✅ Makefile-based build system
* ✅ Custom utilities like `my_ls`, `my_pipe`

---

## 🏗️ Project Structure

```
.
├── src/        # Source files
├── include/    # Header files
├── lib/        # Custom libraries
├── bin/        # Compiled binaries (ignored in git)
├── makefile    # Build automation
└── README.md
```

---

## ⚙️ Technologies Used

* **C Programming**
* **Linux System Programming**
* **GCC Compiler**
* **Makefile**
* **POSIX APIs**

---

## 🧠 Concepts Demonstrated

* Process Management (`fork()`, `exec()`, `wait()`)
* File Descriptors & I/O Redirection
* Pipes & Inter-process Communication
* Environment Handling (`getenv`)
* Modular Code Design

---

## 🚀 How to Run

```bash
# Clone the repository
git clone https://github.com/Siddesh-GM-09/mini-embedded-shell.git

# Navigate to project
cd mini-embedded-shell

# Build the project
make

# Run the shell
./bin/shell
```

---

## 📸 Sample Output

```
user@system:~/Desktop$ my_ls
file1.txt  file2.c  folder/

user@system:~/Desktop$ cd folder
user@system:~/Desktop/folder$
```

---

## 💡 Key Highlights

* Built from scratch without using existing shell libraries
* Focus on **low-level system interaction**
* Clean and scalable architecture
* Suitable for **Embedded Systems & System Programming roles**

---

## 🎯 Future Improvements

* Add support for background processes (`&`)
* Command history feature
* Signal handling (Ctrl+C, Ctrl+Z)
* Auto-completion

---

## 👨‍💻 Author

**Siddesh G M**
📧 [siddesh.gm25@gmail.com](mailto:siddesh.gm25@gmail.com)
🔗 https://github.com/Siddesh-GM-09

---

## ⭐ If you like this project

Give it a ⭐ on GitHub — it helps a lot!

