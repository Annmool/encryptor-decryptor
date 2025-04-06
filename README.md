# Simple C++ File Encrypter/Decrypter

A command-line tool written in C++17 to encrypt or decrypt all files within a specified directory using a simple Caesar cipher based on an integer key. The key is read from a `.env` file located in the same directory as the executable. This tool utilizes multiple threads (`std::thread`) for potentially faster concurrent processing of files.

**⚠️ SECURITY WARNING ⚠️**

This program uses a **very basic Caesar cipher** (byte addition/subtraction). **It is NOT cryptographically secure** and should **NOT** be used for protecting sensitive data. It offers minimal obfuscation at best and is easily broken. Its primary purpose is educational or for non-critical, simple obfuscation tasks.

## Features

*   Recursively scans a specified directory.
*   Encrypts or decrypts all regular files found within the directory.
*   Uses a simple, reversible byte-wise Caesar cipher.
*   Reads the integer encryption/decryption key from a `.env` file.
*   Utilizes C++ standard threads (`std::thread`) to process files concurrently.
*   Simple interactive command-line interface.
*   Includes basic error handling for file access and invalid input.

## Prerequisites

*   **C++ Compiler:** A compiler supporting C++17 (e.g., GCC 9+ or Clang).
*   **Make:** The `make` build utility.
*   **(Windows)** For compiling on Windows, the [MSYS2](https://www.msys2.org/) environment with the UCRT64 toolchain (`mingw-w64-ucrt-x86_64-toolchain`) is recommended, as the provided `makefile` is configured for it. Ensure `make` is installed within MSYS2 (`pacman -S make`).

## Building

1.  **Clone or Download:** Get the source code into a local directory.
    ```bash
    # Example using git:
    # git clone <your-repo-url>
    # cd <repository-directory>
    ```
2.  **Compile using Make:** Navigate to the project's root directory (where the `makefile` is located) in your terminal or MSYS2 UCRT64 shell and run:
    ```bash
    make clean && make
    ```
    This will compile the source files and create an executable named `file_processor` (Linux/macOS) or `file_processor.exe` (Windows) in the current directory.

    *   **Note for Windows/MSYS2 Users:** The `makefile` includes the necessary `-lstdc++fs` and `-pthread` flags required for linking the filesystem and thread libraries with the MinGW g++ compiler provided by MSYS2.

## Usage

1.  **Create `.env` File:** Before running the program, create a file named exactly `.env` in the **same directory** as the `file_processor` executable. Inside this file, put **only the integer number** you want to use as the encryption/decryption key.
    *   Example `.env` content:
        ```
        12345
        ```
    *   **Important:** The file should contain *only* the digits of the key. Any other characters will cause an error.

2.  **Run the Executable:** Open your terminal or MSYS2 shell, navigate to the directory containing `file_processor` and the `.env` file, and run it:
    ```bash
    ./file_processor
    ```
    (On Windows, you might need `./file_processor.exe` or just `file_processor.exe`).

3.  **Follow Prompts:**
    *   **Enter the directory path:** Provide the full or relative path to the directory containing the files you want to process.
        *   Examples:
            *   `/home/user/documents/my_files`
            *   `./test_data`
            *   `C:/Users/YourUser/Desktop/files_to_process`
            *   `C:\Users\YourUser\Documents\Important Stuff` (Backslashes often work but forward slashes are usually safer in shells)
        *   **Do NOT include surrounding quotes (`"`)** in the path when prompted, unless you modify the code to handle them specifically.
    *   **Enter the action (encrypt/decrypt):** Type `encrypt` or `decrypt` and press Enter.

4.  **Processing:** The program will scan the directory, print the key it's using, and then dispatch tasks to threads to process the files. It will print progress/completion messages.

    **🚨 CAUTION:** The encryption/decryption happens **in-place**, modifying the original files. Ensure you have backups if the data is important, especially before running `encrypt` on a directory for the first time. **Do NOT run `encrypt` on the project's own source code directory unless you intend to and know how to recover it!**

## Project Structure
├── .env # User-created: Contains the encryption key (integer)
├── file_processor # Compiled executable (Linux/macOS)
├── file_processor.exe # Compiled executable (Windows)
├── main.cpp # Main application logic, CLI, directory scanning
├── makefile # Build instructions for make
├── README.md # This file
└── src # Source code directory
└── app
├── encryptDecrypt
│ ├── Cryption.cpp
│ ├── Cryption.hpp
│ └── CryptionMain.cpp # Optional: Standalone utility for testing Cryption.hpp
├── fileHandling
│ ├── IO.cpp
│ ├── IO.hpp
│ ├── ReadEnv.cpp
│ └── ReadEnv.hpp
└── processes
├── ProcessManagement.cpp
├── ProcessManagement.hpp
└── Task.hpp



## Limitations

*   **Weak Security:** As stated, the Caesar cipher is trivial to break.
*   **In-Place Modification:** Files are overwritten directly. Interruption during processing could lead to corrupted files. No recovery mechanism is built-in besides manually decrypting.
*   **Error Handling:** Basic error handling is present, but edge cases might not be fully covered.
*   **Large Files/Directories:** Performance with extremely large files or a huge number of files hasn't been extensively tested and might be limited by memory or thread management overhead.
*   **Key Management:** Reading the key from a plain text `.env` file is not secure practice for real applications.

## License

This project is licensed under the MIT License - see the `LICENSE` file (you would need to create this file) for details.
