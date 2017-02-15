# LiLua Interpreter
A small interpreter written in C/C++ and Java that can translate a minimal version of Lua (called "LiLua" for "Light Lua") into an intermediate form to then be interpreted by an interpretive engine.

## Overview
This README file gives a rough overview of the LiLua interpreter. A brief description of LiLua is discussed in the next section. An quick example of the usage of the LiLua compiler and interpreter is presented in later sections. Repository can be found at the [GitHub Repo](https://github.com/mtfuller/lilua-interpreter).
## What is LiLua?
LiLua, or "Light Lua," is a small subset of the Lua programming language. Here are the major differences:
#### Single-character, Non-case-sensitive Identifiers
```Lua
-- This statement...
a = 5

-- ...is the same as this statement...
A = 5

-- Incorrect Identifiers...
ab = 2
count = 8
```

#### Only One Supported Data Type: Integer
```Lua
-- Supported...
a = 5
b = 6
c = 2

-- Unsupported...
a = 5.6
b = false
c = "hello"
```

#### All Executable Code is Placed within a Function Declaration
```Lua
-- Correct...
function f()
    a = 2
    b = 3
    c = a + b
    print(c)
end

-- Incorrect...
a = 5
b = 2 * a
function f()
    c = 7
    print(c)
end
print(b)
```

## LiLua Compiler
The LiLua compiler is a small application written in C/C++ that takes in a Lua file, and produces an intermediate form. The intermediate form is then translated into a type of "byte code", which is then placed into a .lil file.

```
your-directory
|-- my-program.lua
```

```shell
liluac -c "<PATH>/your-directory/my-program.lua"
```

```
your-directory
|-- my-program.lil
|-- my-program.lua
```

## LiLua Interpreter
The LiLua Interpreter takes in a .lil file, and then the interpreter reads the input from the file and performs corresponding actions.

```
your-directory
|-- my-program.lil
|-- my-program.lua
```

```shell
java -jar lilua.jar "<PATH>/your-directory/my-program.lil"
```
