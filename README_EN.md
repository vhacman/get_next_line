***Aggiornato il 11/06/2025***

## 🤝 Contribute Respectfully

If you find this project useful, please avoid cloning the repository directly.

### ✨ Why Fork?

Forking the repository:

* lets you create your own personal copy to work on freely;
* makes your interest in the project transparent;
* helps me build a more professional and trackable GitHub, showing how many people have truly interacted with my work.

> 🚀 This helps me grow my profile and improve as a developer.

### ✅ How to Proceed

1. Click on **Fork** in the top-right corner
2. Clone your copy with:

```bash
git clone https://github.com/<your-username>/<repo-name>.git
```

---

# Get Next Line

[![GNL](https://github.com/vhacman/get_next_line/actions/workflows/main.yml/badge.svg)](https://github.com/vhacman/get_next_line/actions/workflows/main.yml)
![42 Roma Luiss](https://img.shields.io/badge/42-Roma_Luiss-green)
![Score](https://img.shields.io/badge/Score-125/100-brightgreen)
![Created](https://img.shields.io/badge/Created-February_2025-blue)
![Status](https://img.shields.io/badge/Status-Completed-violet)

---

## 📖 Description

**Get Next Line** (`get_next_line`) is a C function developed during the 42 curriculum to read from a file descriptor **line by line**, managing memory efficiently and supporting **multiple file descriptors** in the bonus version.

---

## 💡 Features

* Reads from a file descriptor **one line at a time**
* Supports files, standard input, and pipes
* Uses a configurable buffer size (`BUFFER_SIZE`)
* **Bonus**: Simultaneous reading from multiple file descriptors (`OPEN_MAX`)

---

## 🛠️ Technical Skills

* Dynamic memory management with no leaks
* Use of static variables to preserve state across calls
* Efficient buffer management
* Recursive string handling
* Bonus: Parallel handling of multiple file descriptors

---

## 📁 File Structure

```
gnl/
├── file_test/
│   └── file1.txt
│   └── file2.txt
│   └── file3.txt
│   └── test.txt
├── includes/
│   └── get_next_line.h
├── includes_bonus/
│   └── get_next_line_bonus.h
├── src/
│   ├── get_next_line.c           ← contains a commented-out main() for testing
│   └── get_next_line_utils.c
├── src_bonus/
│   ├── get_next_line_bonus.c     ← contains a commented-out main() for testing
│   └── get_next_line_utils_bonus.c
├── README.md
└── README_EN.md
```

> Both `get_next_line.c` and `get_next_line_bonus.c` include a **commented test main()** that can be activated for local testing.

---

## 🔄 Function Logic

### Standard Version

1. **Validates** the input parameters (`fd` and `BUFFER_SIZE`)
2. **Reads chunks** of data from the `fd` into a dynamic buffer
3. **Stores leftover data** between calls using a static variable
4. **Extracts a complete line**, keeping the rest for the next call
5. **Returns** the line as `char *`, or `NULL` at end of file

### Bonus Version

* Uses an **array of static buffers**, one for each file descriptor
* Indexes buffers using the file descriptor (up to `OPEN_MAX`)
* Ensures **independent states** for each `fd`
* Ideal for handling **multiple files or pipes** in the same program

---

## 🧪 Testing

### ✅ Standard Tests

* Small and large files
* No trailing newline
* Empty files
* Files with one or more lines
* Input from pipe or `stdin`

### ✅ Bonus Tests

* Simultaneous reading from multiple files
* Alternating reading across different `fd`s
* Files with lines of varying lengths
* File descriptors opened/closed in random order
* Verifying independent buffer memory for each `fd`

---

## ⚙️ Compilation

### Mandatory

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    -Iincludes \
    src/get_next_line.c src/get_next_line_utils.c \
    -o gnl
```

### Bonus

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
    -Iincludes_bonus \
    src_bonus/get_next_line_bonus.c src_bonus/get_next_line_utils_bonus.c \
    -o gnl_bonus
```

Run with:

```bash
./gnl          # To test the standard version
./gnl_bonus    # To test the bonus version
```
