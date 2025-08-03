# BUILTIN header file
> **This is Documentation for the custom built header file.**

## Functions

### PIT finder 
This is a function that will **find the pathway to .pit directory**. It's main use case it to access the content of the PIT_DIR even if you are nested inside the folder/subfolder.

`function name`: pit_finder()

`output`: **GIT_DIR**, The exact pathway from home directory as a **String**.

> ***PATH_MAX***
> - in linux/limits.h
> - Used to represent the maximum length of a file path.

> *** char *getcwd(char *buf, size_t size) ***
> - declared in unistd.h and is part of POSIX standard..
> - used to retrive the current working directory of a process.
> - take 2 input (buffer, sizeof(buffer)).
> - return **String** of the **pathway**. OR **NULL** if size is not large enough.
 
> ***S_ISDIR(mode)***
> - Common macro in C (POSIX standard) to check a file is directory or not
> - take input **mode**. Typically *st.st_mode*.
> - return non-zero if true and zero for false.

> *** char *strrchr(const char *s, int c) ***
> - searches a C-string for the last occurence of the specified character and returns pointer to it.
> - take input String to search and character to find.
> - if the character is not found return NULL.

## Constant

* GIT_DIR = The exact pathway from home to directory as a **String**.

## Other Headers
