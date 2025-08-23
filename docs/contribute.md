# Contribution Guidelines

> This document outlines the rules and best practices to follow when contributing to the codebase.

---

## 📛 Naming Conventions

- **Variables and Function Names**: Use `snake_case`.
- **Macros and Constants**: Use `UPPER_CASE_WITH_UNDERSCORE`.
- **Files**: Should be named in `lowercase`.
- **Folders**: Should be named in `UPPERCASE`.

---

## ➕ Adding a New PIT Command

To add a new PIT command:

1. **Location**: Add the program file in the `src/` directory.
2. **Language**: Use only **C** for programming.
3. **Function Naming**: The main function should be named in the format: `cmd_{name}.`

---

## ✅ Commit Message Format

Use the following standardized format for commit messages:

| Type         | Format                                 | Example                                    |
|--------------|----------------------------------------|--------------------------------------------|
| Bug Fix      | `FIXED: {problem statement}`           | `FIXED: Segfault when executing 'cmd_run'` |
| Feature Add  | `ADD: {added feature}`                 | `ADD: Support for --help flag`             |
| New Header   | `HEADER: {header name}`                | `HEADER: pit_config.h`                     |
| Other        | `MISC: {small sensible statement}`     | `MISC: Updated README formatting`          |

---

## 🐞 Fixing a Bug

When fixing a bug:

1. **Doxygen Comment**: Include a detailed explanation in the code using Doxygen-style comments:
- What the bug was
- How it occurred
- How you fixed it
2. **Documentation**: If the fix is complex or affects multiple components, create a `.md` file in the documentation directory that explains the bug and resolution in more detail.

---

## Note

After each update increase the version number at the top of the file.