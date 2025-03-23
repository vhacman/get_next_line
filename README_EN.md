
# 📄 Get Next Line (GNL)

![42 Roma Luiss](https://img.shields.io/badge/42-Roma_Luiss-green)
![Score](https://img.shields.io/badge/Score-125/100-brightgreen)
![Created](https://img.shields.io/badge/Created-February_2025-blue)
![Status](https://img.shields.io/badge/Status-Completed-violet)

## 📖 Description

**Get Next Line** (`get_next_line`) is a C function developed during the 42 cursus to read from a file descriptor **line by line**, handling memory efficiently and supporting **multiple file descriptors** in the bonus version.

## 💡 Features

- Reads from a file descriptor **one line at a time**
- Supports files, standard input, and pipes
- Uses a configurable buffer size (`BUFFER_SIZE`)
- **Bonus**: Simultaneous reads from multiple file descriptors (`OPEN_MAX`)

## 🛠️ Technical Skills

- Dynamic memory management without leaks
- Static variables for persistent state
- Efficient buffer handling
- Recursive string management
- Bonus: Managing multiple file descriptors in parallel

## 📁 File Structure

```
gnl/
├── includes/
│   └── get_next_line.h
├── includes_bonus/
│   └── get_next_line_bonus.h
├── src/
│   ├── get_next_line.c
│   └── get_next_line_utils.c
├── src_bonus/
│   ├── get_next_line_bonus.c
│   └── get_next_line_utils_bonus.c
├── README.md
└── README_EN.md
```

## 🔄 Function Logic

### Standard Version

1. **Validates** input parameters (fd and buffer).
2. **Reads chunks** from fd into a dynamic buffer.
3. **Stores leftover** data between calls (using static variable).
4. **Extracts a full line**, and saves the rest for next time.
5. **Returns** the line as a `char *`, or `NULL` at EOF.

### Bonus Version

- Uses an **array of static buffers**, one per file descriptor.
- Indexes buffers using the file descriptor (up to `OPEN_MAX`).
- Ensures **independent states** per fd.
- Ideal for handling **multiple files/pipes** in the same program.

---

## 🧪 Testing

### ✅ Standard Tests

- Small and large files
- No newline at EOF
- Empty files
- Single-line and multi-line files
- Pipes and stdin

### ✅ Bonus Tests

- Simultaneous reads from multiple files
- Interleaved reads: alternating between FDs
- Files with different line sizes
- FDs opened/closed in mixed order
- Confirm memory separation per FD

---

## 📋 Example Usage

### 🧾 Basic Read

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd = open("example.txt", O_RDONLY);
    char    *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
