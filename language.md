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
| `INLINE`    | `inline`    |             |
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

| Token          | Regex    | Description                                                  |
| -------------- | -------- | ------------------------------------------------------------ |
| `IDENTIFIER`   |          | Name of a type/constant/variable/... declared in the same unit or in a dependency. |
| `NEW`          | `new`    | Allocate a data type and optionally invoke the constructor.  |
| `DELETE`       | `delete` | Free a pointer and invoke the destructor.                    |
| `ROUND_OB`     | `\(`     |                                                              |
| `ROUND_CB`     | `\)`     |                                                              |
| `CURLY_OB`     | `\{`     |                                                              |
| `CURLY_CB`     | `\}`     |                                                              |
| `SQUARE_OB`    | `\[`     |                                                              |
| `SQUARE_CB`    | `\]`     |                                                              |
| `PERIOD`       | `\.`     |                                                              |
| `SEMICOLON`    | `;`      |                                                              |
| `COLON`        | `:`      |                                                              |
| `COMMA`        | `\,`     |                                                              |
| `PLUS`         | `\+`     |                                                              |
| `MINUS`        | `\-`     |                                                              |
| `STAR`         | `\*`     |                                                              |
| `SLASH`        | `/`      |                                                              |
| `AND`          | `&`      |                                                              |
| `OR`           | `|`      |                                                              |
| `NOT`          | `!`      |                                                              |
| `QUESTIONMARK` | `\?`     | exports                                                      |
| `EQUALS`       | `=`      |                                                              |
| `LESS`         | `<`      |                                                              |
| `GREATER`      | `>`      |                                                              |

## Language concepts

The grammer of the language is described using the following syntax:

- `{TOKEN1 TOKEN2}`: A group of tokens or language constructs that are mandatory.
-  `[TOKEN1 TOKEN2]`: A group of tokens or language constructs that are optional.
- `TOKEN1|TOKEN2`: A arbitrary combination of the declared tokens or language constructs. (or)
- `TOKEN1||TOKEN2`: Only one of the declared tokens or language constructs. (xor)
- `...`: Can occur multiple times.
- `IDENTIFIER:`: Declare a language component.

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

A unit is a translation unit that can contains a class, singleton, error or type. A unit also has a list of dependencies defines by `USING` statements:

```c++
Using:
USING {IDENTIFIER [PERIOD]}... SEMICOLON
// using Strict.Memory.Shared;
```



#### Classes

A data type that can have a set of member variables and methods. A class is declared the following way:

```c++
Class:
DeclarationFlag... CLASS IDENTIFIER [Template] [COLON {IDENTIFIER [COMMA]}...] CURLY_OB [Method|Field|Constructor]... [Destructor] CURLY_CB
// public mut class Array<type ElementType> : Collection<ElementType> { ... }
```

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
DeclarationFlag:
{PUBLIC|PRIVATE|PROTECTED|INTERNAL|MUT|IMPURE|{VIRTUAL||EXTERNAL}}
Template:
LESS {{IDENTIFIER||Type||DataType||TYPE} IDENTIFIER}... GREATER
// <type ElementType, UInt64 length>
```

A template is a comma separated list of type name - name pairs. The type name can be a real data type which would allow you to pass data of the type as a template parameter. The type can also be a generic type like `TYPE`  or a type declaration which would allow you to declare variables of that type, ... The template parameters get inlined at compile time.

##### Fields

A class member that can store data. A field can be declared `INLINE` which would mean, that it is an interface to access thcapacity e class through getters and setters without storing any data. Fields are declared like this:

```c++
Field:
DeclarationFlag... DataType IDENTIFIER [CURLY_OB [Getter|Setter]... CURLY_CB] [EQUALS Expression] SEMICOLON
// public Int32 number { /* getters and setters */ } = 0;
```

A field can also specify a set of getter ans setters that are used to control read and write access to a field or implement the functionality of inline fields.

Getter:

- Can't be declared as `MUT` and inherits the visibility flags of the field declaration.

```c++
DeclarationFlag... DataType GET Body
// public Int32 get { /* return data */ }
```

Setter:

- Automatically has the `MUT` flag set and inherits the visibility flags of the field declaration.

```c++
DeclarationFlag... DataType SET ROUND_OB DataType IDENTIFIER ROUND_CB Body
// public Int32 set(Int32 newNumber) { /* set data */ }
```

##### Methods

A subroutine the is run in the context of a class. Declaration:

```c++
Method:
DeclarationFlag... DataType IDENTIFIER [Template] ROUND_OB [Parameters] ROUND_CB Body
// public Int32 Sum<UInt64 count>(Int32[] array) { /* function body */ }
Parameters:
{DataType IDENTIFIER [COMMA]}...
```

Classes can also implement their own operators. There are four types of operator:

1. Non mutating binary operators:

   ```c++
   DeclarationFlag... DataType OPERATOR {STAR|PLUS|MINUS|SLASH|AND|OR|GREATER|LESS|EQUAL|{NOT EQUAL}|{GREATER EQUAL}|{LESS EQUAL}} ROUND_OB DataType IDENTIFIER ROUND_CB Body
   // public Float16 operator+(Float16 other) { /* compute and return result */ }
   ```
   
   Non mutating binary operators must not be `MUT` since that would be unexpected behavior.
   
2. Mutating binary operators:

   ```c++
   DeclarationFlag... DataType OPERATOR {STAR|PLUS|MINUS|SLASH|AND|OR} EQUAL ROUND_OB DataType IDENTIFIER ROUND_CB Body
   // public void operator+=(Float16 other) { /* mutate data */ }
   ```

   Mutating binary operators are `MUT` by default. Note that calls to mutating binary operators get replaced either by `set()` or a call to the copy constructor and the corresponding non mutating binary operator if the operator has not been implemented or is inaccessible (either visibility or mutability). An example for this case is when a field implements a getter that returns an immutable copy or reference:

   ```c++
   public UInt64 number { public void set(UInt64 newNumber) { /* ... */ } public UInt64 get() { /* ... */ } }
   
   number += 1;
   // Calls to operator+= get converted to = operator+
   number = number + 1;
   ```

3. Non mutating unary operators:

   ```c++
   DeclarationFlag... DataType OPERATOR {MINUS|NOT|TILDE} ROUND_OB ROUND_CB Body
   // public Float16 operator-() { /* compute and return result */ }
   ```

   Non mutating unary operators must not be `MUT` since that would be unexpected behavior.

   The explicit and implicit cast operators also are non mutating unary operators:

   ```c++
   DeclarationFlag... OPERATOR [LESS] DataType [GREATER] ROUND_OB ROUND_CB Body
   // public operator<Int16>() { /* compute and return result */ } // explicit
   // public operator Float64() { /* compute and return result */ } // implicit
   // public operator<FloatType Type>() { /* compute and return result */ } // templated explicit
   ```

   The cast operators don't need a return type since the return type can be inferred from the cast type. Explicit casts can be templated because the syntax allows it.

4. Mutating unary operators:

   ```c++
   DeclarationFlag... DataType OPERATOR {{PLUS PLUS}|{MINUS MINUS}} ROUND_OB ROUND_CB Body
   // public Float16 operator++() { /* increment and return result */ }
   ```

   Mutating unary operators are `MUT` by default. Note that calls to mutating unary operators get replaced by calls to mutating binary operators if the operator has not been implemented or is inaccessible (either visibility or mutability). An example for this case is when a field implements a getter that returns an immutable copy or reference:
   
   ```c++
   public UInt64 number { public void set(UInt64 newNumber) { /* ... */ } public UInt64 get() { /* ... */ } }
   
   number++;
   // Calls to operator++ first get converted to operator+=
   number += 1;
   // Calls to operator+= get converted to = operator+
   number = number + 1;
   ```
   


##### Constructors

A constructor is a method that is used to initialize an object. The constructor is `MUT` by default and can be invoked in the declaration of immutable variables. Invoking a constructor outside of the variable declaration requires the variable to be mutable. There are two special types of constructor:

- Default constructors are declared by default but can be overridden. When not overridden, a default constructor initializes every member to its default value:

  | Types         | Default value                |
  | ------------- | ---------------------------- |
  | Integer types | 0                            |
  | Float types   | 0.0                          |
  | `BOOL`        | `false` (0)                  |
  | Pointer types | `null`                       |
  | Class types   | Invokes default constructor. |

- Copy constructors are also declared by default and can be overridden. The default implementation copies every class member (using the copy constructor for class types).

Constructor declaration:

```c++
Constructor:
DeclarationFlag... IDENTIFIER ROUND_OB Arguments ROUND_CB [COLON {IDENTIFIER ROUND_OB Expression ROUND_CB [COMMA]}...] Body
// public String(UInt16[] characters)
//     : data(characters), length(StringHelper.length<UInt16>(characters)) { /* function body */ } // normal constructor
// public String<IntegerType CharacterType>(CharacterType[] characters)
//     : data(StringHelper.convertToUTF16<CharacterType>(characters),
//       length(StringHelper.length<CharacterType>(characters) { /* function body */ } // templated constructor
// public String() 
//     : data(""), length(0) { /* function body */ } // default constructor
// public String(String& string)
//     : data(string.data), length(string.length) { /* function body */ } // copy constructor
```

##### Destructors

Destructors are run at the end of the lifetime of a class, usually when exiting a scope or deleting a heap allocated object.

Destructor declaration:

```c++
Destructor:
DeclarationFlag... TILDE IDENTIFIER ROUND_OB ROUND_CB Body
// public ~String() { /* function body */ }
```

##### Singletons

A singleton is a class with the exception that it can only have a default constructor. The singleton is instantiated on program start and can not be instantiated manually. Accessing other singletons in the constructor is defined.

#### Errors

Errors are declared the following way:

```c++
Error:
ERROR IDENTIFIER [EQUALS INT_LITERAL] SEMICOLON
// error MyError;
// error MyError = 1;
```

Errors can be thrown using `throw`, caught using `try` and `catch` cast to different integer types and therefore passed as a argument to `Strict.Core.System.Exit(Int32)`.

There also is a list of predefined errors that are thrown by code generated by the compiler:

- `OutOfMemoryError = 1`: Thrown by `new`.

#### Types

A type specifies the properties an object of the type must have. Types are mainly used when declaring templates since templates with a generic `TYPE` argument are almost useless. The properties of a type must not be declared with an implementation (Function declarations end with `SEMICOLON` instead of a block).

```c++
Type:
DeclarationFlag... TYPE [IDENTIFIER] [Template] [COLON {IDENTIFIER [COMMA]}...] CURLY_OB [Method|Field|Constructor]... CURLY_CB
// type CopyType { public CopyType(CopyType& source); }
```

Note that the `IDENTIFIER` is optional to allow inline type declarations.

Data types are used to specify the type of a variable, return type or a template argument that is not a type itself:

```c++
DataType:
[MUT] DataType [STAR||AND||{CURLY_OB [Expression] CURLY_CB}]
ROUND_OB DataType ROUND_OB
IDENTIFIER [Template]
// mut Vector<Float32, 3>[]
```

### Expressions

### Statements

