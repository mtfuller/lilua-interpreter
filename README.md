# LiLua Interpreter
A small interpreter written in C/C++ and Java that can translate a minimal version of Lua (called "LiLua" for "Light Lua") into an intermediate form to then be interpreted by an interpretive engine.

## Overview
Blah blah blah...

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
count = 8```

#### Only One Supported Data Type: Integer
```Lua
-- Supported...
a = 5
b = 6
c = 2

-- Unsupported...
a = 5.6
b = false
c = "hello"```

#### Reverse Polish Notation for Arithmetic/Boolean Operations
```Lua
-- Correct notation...
x = * / a c b
z = - + - * 2 a / 30 c b 17
> c 0

-- Incorrect notation...
x = a / c * b
z = 2 * a - 30 / c + b - 17
c > 0```

## LiLua Compiler
Blah blah blah...

```
your-directory
|-- my-program.lua```

```shell
liluac -c "<PATH>/your-directory/my-program.lua"
```

```
your-directory
|-- my-program.lil
|-- my-program.lua```

## LiLua Interpreter
Blah blah blah...

```
your-directory
|-- my-program.lil
|-- my-program.lua```

```shell
java -jar lilua.jar "<PATH>/your-directory/my-program.lil"
```
