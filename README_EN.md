# Get Next Line (GNL) - English

![42 Roma Luiss](https://img.shields.io/badge/42-Roma_Luiss-green)
![Score](https://img.shields.io/badge/Score-125-green)
![Created](https://img.shields.io/badge/Created-February_2025-blue)
![Status](https://img.shields.io/badge/Status-Completed-violet)

## 📖 Overview
Get Next Line is a function developed in C as part of the 42 Roma curriculum. This utility allows reading content from a file descriptor line by line, efficiently managing memory and supporting multiple descriptors.

![C](https://img.shields.io/badge/Language-C-blue)
![42](https://img.shields.io/badge/Project-42_Roma-white)

## 🛠️ Demonstrated Technical Skills
- **Advanced memory management in C** - Dynamic allocations without memory leaks
- **Efficient use of pointers and data structures**
- **Handling of files and multiple descriptors**
- **Use of static variables to preserve state between calls**
- **Development of efficient algorithms for I/O operations**

## 💡 Key Features
- Reads text from a file descriptor one line at a time
- Proper handling of newline characters
- Configurable buffer size via the `BUFFER_SIZE` macro
- Efficient memory management (no memory leaks)

### ⭐ Bonus Version Features
- Simultaneous support for multiple file descriptors
- Efficient handling of multiple files without buffer interference
- Use of a static buffer array sized with `OPEN_MAX`
- Full compatibility with the standard version

## 🧩 Technical Approach
The project is structured into three main files for the standard version:
- `get_next_line.h`: Contains function prototypes and structure definitions
- `get_next_line.c`: Implements the main `get_next_line` function
- `get_next_line_utils.c`: Contains utility functions for string manipulation

### Bonus Version
The bonus version adds:
- `get_next_line_bonus.h`: Header file with support for multiple file descriptors
- `get_next_line_bonus.c`: Implementation of the function with multi-FD support
- `get_next_line_utils_bonus.c`: Optimized utility functions for the bonus version

I implemented a solution that uses:
1. **Dynamic buffer** - To read data from the file in efficient blocks
2. **Static variable** - To retain remaining data between calls
3. **Custom data structure** - To efficiently manage line metadata
4. **Static buffer array** - In the bonus version, to handle multiple file descriptors

## 🔄 Functionality
The `get_next_line` function operates as follows:
1. Checks the validity of the file descriptor and buffer size
2. Reads from the file descriptor and accumulates data in the buffer until a newline character or EOF is found
3. Extracts the first complete line from the buffer
4. Stores the remaining data for the next call
5. Returns the extracted line as a null-terminated string

### Bonus Version Functionality
The bonus version extends the standard functionality:
1. Uses a static buffer array sized with `OPEN_MAX` to handle multiple file descriptors simultaneously
2. Associates each buffer with a specific FD using the array index
3. Maintains separate state for each file descriptor, allowing alternating reads from multiple files
4. Ensures the FD is valid (not negative and below `OPEN_MAX`)
5. Manages memory independently for each file descriptor

The bonus implementation ensures that reading from one file does not interfere with the state of other open files.

## 📋 Example Usage
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    
    fd = open("text.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening the file\n");
        return (1);
    }
    
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    
    close(fd);
    return (0);
}
```

## 🔍 Challenges and Solutions
- **Challenge**: Correctly managing the buffer between successive calls
  - **Solution**: Use of a static variable to store unprocessed data
- **Challenge**: Avoiding memory leaks when handling strings
  - **Solution**: Careful memory management with appropriate `free()` calls in all code paths
- **Challenge**: Supporting multiple file descriptors simultaneously
  - **Solution**: Implementation of a static array to track buffers for each descriptor

## 🎓 What I Learned
- Deepened understanding of pointers and dynamic memory allocation
- Improved debugging and testing techniques for programs with complex state management
- Enhanced ability to write clean, modular, and well-documented code
- Gained better insight into I/O operations in C

## 💻 Compilation and Testing

### Standard Version
```bash
# Compile with a custom buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# Execution
./gnl
```

### Bonus Version
```bash
# Compile the bonus version
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus

# Execution
./gnl_bonus
```

### Example Main for Testing the Bonus Version
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1;
    int     fd2;
    int     fd3;
    char    *line;
    
    // Open multiple files
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);
    
    if (fd1 == -1 || fd2 == -1 || fd3 == -1)
    {
        printf("Error opening files\n");
        return (1);
    }
    
    // Read alternately from three files
    line = get_next_line(fd1);
    printf("File 1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("File 2: %s", line);
    free(line);
    
    line = get_next_line(fd3);
    printf("File 3: %s", line);
    free(line);
    
    // Continue reading from the first file
    line = get_next_line(fd1);
    printf("File 1: %s", line);
    free(line);
    
    // Close the files
    close(fd1);
    close(fd2);
    close(fd3);
    
    return (0);
}
```

## 📚 Code Documentation
Each function in the code is documented with detailed comments explaining:
- The function's purpose
- Input parameters and their meanings
- Return values and their significance
- Special cases and error handling

## 🧪 Testing

### General Testing
The project was rigorously tested with:
- Files of various sizes (from a few bytes to several megabytes)
- Files with and without newline characters
- Empty files
- Edge cases with `BUFFER_SIZE` set to very small and very large values

### Specific Testing for the Bonus Version
For the bonus version, additional tests were conducted:
- Simultaneous use of multiple file descriptors (up to the `OPEN_MAX` limit)
- Alternating reads from different files to verify buffer independence
- Opening and closing file descriptors in complex sequences
- Tests with non-sequential file descriptors
- Ensuring correct memory management even with interleaved operations on different files