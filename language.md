# The Strict programming language

[TOC]

## Tokens

### Data types 

| Token     | Regex | Description |
| --------- | ----- | ----------- |
| `BOOL`    | `Bool` | Logical data type |
| `INT8`    | `Int8` | 8 bit signed integer |
| `UINT8`   | `UInt8` | 8 bit unsigned integer |
| `INT16`   | `Int16` | 16 bit signed integer |
| `UINT16`  | `UInt16` | 16 bit unsigned integer |
| `INT32`   | `Int32` | 32 bit signed integer |
| `UINT32`  | `Uint32` | 32 bit unsigned integer |
| `INT64`   | `Int64` | 64 bit signed integer |
| `UINT64`  | `UInt64` | 64 bit unsigned integer |
| `FLOAT32` | `Float32` | 32 bit IEEE-754 floating point number |
| `FLOAT64` | `Float64` | 64 bit IEEE-754 floating point number |
| `VOID` | `void` | no type |

### Control flow

| Token      | Regex      | Description |
| ---------- | ---------- | ----------- |
| `IF`       | `if`       |             |
| `ELSE`     | `else`     |             |
| `FOR`      | `for`      |             |
| `WHILE`    | `while`    |             |
| `DO`       | `do`       |             |
| `BREAK`    | `break`    |             |
| `CONTINUE` | `continue` |             |
| `TRY`      | `try`      |             |
| `CATCH`    | `catch`    |             |
| `THROW`    | `throw`    |             |
| `RETURN`   | `return`   |             |

### Structure

| Token       | Regex       | Description |
| ----------- | ----------- | ----------- |
| `PUBLIC`    | `public`    |             |
| `PRIVATE`   | `private`   |             |
| `PROTECTED` | `protected` |             |
| `INTERNAL`  | `internal`  |             |
| `EXTERNAL`  | `external`  |             |
| `MUT`       | `mut`       |             |
| `IMPURE`    | `impure`    |             |
| `VIRTUAL`   | `virtual`   |             |
| `CLASS`     | `class`     |             |
| `SINGLETON` | `singleton` |             |
| `TYPE`      | `type`      |             |
| `ERROR`     | `error`     |             |
| `USING`     | `using`     |             |
| `GET`       | `get`       |             |
| `SET`       | `set`       |             |
| `OPERATOR`  | `operator`  |             |

### Literals

| Token            | Regex | Description               |
| ---------------- | ----- | ------------------------- |
| `INT_LITERAL`    |       | Literal of type `Int64`   |
| `UINT_LITERAL`   |       | Literal of type `UInt64`  |
| `FLOAT_LITERAL`  |       | Literal of type `Float64` |
| `STRING_LITERAL` |       | Literal of type `UInt8[]` |

### Other symbols

| Token          | Regex | Description                                                  |
| -------------- | ----- | ------------------------------------------------------------ |
| `IDENTIFIER`   |       | Name of a type/constant/variable/... declared in the same unit or in a dependency. |
| `ROUND_OB`     | `\(`  |                                                              |
| `ROUND_CB`     | `\)`  |                                                              |
| `CURLY_OB`     | `\{`  |                                                              |
| `CURLY_CB`     | `\}`  |                                                              |
| `SQUARE_OB`    | `\[`  |                                                              |
| `SQUARE_CB`    | `\]`  |                                                              |
| `PERIOD`       | `\.`  |                                                              |
| `SEMICOLON`    | `;`   |                                                              |
| `COLON`        | `:`   |                                                              |
| `COMMA`        | `\,`  |                                                              |
| `PLUS`         | `\+`  |                                                              |
| `MINUS`        | `\-`  |                                                              |
| `STAR`         | `\*`  |                                                              |
| `SLASH`        | `/`   |                                                              |
| `AND`          | `&`   |                                                              |
| `OR`           | `|`   |                                                              |
| `NOT`          | `!`   |                                                              |
| `QUESTIONMARK` | `\?`  | exports                                                      |
| `EQUALS`       | `=`   |                                                              |
| `LESS`         | `<`   |                                                              |
| `GREATER`      | `>`   |                                                              |

## Language concepts

### Language structure

#### Modules

A module is a translation unit that can:

- Export a set of units (the exported units get build in their declared order must therefore be declared in the order of dependencies)
- Have other modules as dependencies
- Can have dependencies to external C libraries

The module information is stored in a `module.json` file located at the root of the module directory (example: `Strict/Memory/module.json`). Example:

```json
{
	"type": "INLINE", // Module is linked inline
	"units": // List of units that are part of this module
	[
		"OutOfMemoryError",
		"Allocator",
		"SystemAllocator"
	],
	"targets": // Platform dependent information
	[
		{
			"flags": // Targets are active if their flags are a sub set of the build target flags
			[
				"BIT32",
				"X86",
				"LINUX"
			],
			"externals": // External libraries
			[
				"x86_32/linux/externals.o"
			]
		},
		{
			"flags":
			[
				"BIT64",
				"X86",
				"LINUX"
			],
			"externals":
			[
				"x86_64/linux/externals.o"
			]
		}
	]
}
```

#### Units

A unit is a translation unit that can contains a class, singleton or error.

#### Classes

A data type that can have a set of member variables and methods.

##### Declarations

A class or class member is declared by using set of flags, a name and other declaration type specific data.

Possible visibility modifiers:

| Flag token  | Description                                                  |
| ----------- | ------------------------------------------------------------ |
| `PUBLIC`    | Visibility flag, declaration can be accessed from everywhere. |
| `PRIVATE`   | Visibility flag, declaration can be accessed in the scope of this unit. |
| `PROTECTED` | Visibility flag, declaration can be accessed in the scope of this unit and by sub classes. |
| `INTERNAL`  | Visibility flag, declaration can be accessed by every unit in the module. |
| `MUT`       | For methods: Method can mutate this class. For fields: Field is mutable. For classes: Class is mutable. Needs to be set in order to declare methods and fields with the `MUT` flag. |
| `IMPURE`    | Method flag, method can have different output (return value and mutations of the current class) with the same input (parameters and fields of the current class). This flag has to be set to access singleton methods of singletons declared with the `MUT` flag, singleton fields declared with the `MUT` flag and methods declared with the `IMPURE` flag. |
| `VIRTUAL`   | Method flag, method can be overridden by sub classes.        |
| `EXTERNAL`  | Method flag, method is declared in an external library.      |

Declarations can also have template parameters that are declared the following way:

```c++
/* declaration data */ IDENTIFIER LESS {Type IDENTIFIER [,]} GREATER /* definition */
// public Type Add<NumericType Type>(Type[] a, Type[] b, UInt64 count)
```

A template is a comma separated list of type name - name pairs. The type name can be a real data type which would allow you to pass data of the type as a template parameter. The type can also be a generic type like `TYPE`  or a type declaration which would allow you to declare variables of that type, ... The template parameters get inlined at compile time.

##### Fields

##### Methods

##### Singletons

A singleton is a class with the exception that it can only have a default constructor. The singleton is instantiated on program start and can not be instantiated manually. Accessing other singletons in the constructor is defined.

#### Errors

Errors are declared the following way:

```c++
ERROR IDENTIFIER SEMICOLON // error MyError;
ERROR IDENTIFIER EQUALS INT_LITERAL SEMICOLON // error MyError = 1;
```

Errors can be thrown using `throw`, caught using `try` and `catch` cast to different integer types and therefore passed as a argument to `Strict.System.System.Exit(Int32)`.

### Expressions

### Statements

