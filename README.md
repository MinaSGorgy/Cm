# Cm

C minor(Cm) is a mini version of the C programming language using Flex and Bison compiler generating package.

## AST

```markdown
                                            Node
                ┌────────────────────────────┼─────────────────────────────┐
            NStatement                    NBlock                      NExpression
    ┌────────────────┼─────┐                           ┌─────┬───┬───────┼─────────┬──────────┐
NExpressionStatement │ NVarDeclStatement            NInteger │ NDouble   NVariable │    NAssignment
          NControlFlowStatement                        NUnaryOperation      NBinaryOperation
        ┌────────────┼─────────────────┐
NWhileStatement   NForStatement   NIfStatement
```

## Symbol Table

|Member       |Data Type|Description                                  |
|:-----------:|:-------:|---------------------------------------------|
|`type`       |`int`    |Used for raising TypeMismatch exception      |
|`constant`   |`bool`   |Used for raising ReadOnly exception          |
|`initialized`|`bool`   |Used for raising Uninitialized exception     |
|`used`       |`bool`   |Used for raising not used warnings           |
|`reference`  |`string` |Used for referencing the symbol in quadruples|

## Data Types

|Type    |Description                                                                           |
|:------:|--------------------------------------------------------------------------------------|
|`int`   |An integer type ranging from -2,147,483,648 to 2,147,483,647                          |
|`double`|A floating-point type of 15 decimal places precision ranging from 2.3E-308 to 1.7E+308|
|`void`  |Valueless                                                                             |

## Operators

### Mathematical

|Operator|Description                                                |
|:------:|-----------------------------------------------------------|
|`+`     |Adds two operands                                          |
|`-`     |Subtracts second operand from the first                    |
|`*`     |Multiplies both operands                                   |
|`/`     |Divides numerator by de-numerator                          |

### Relational

|Operator|Description                                                                            |
|:------:|---------------------------------------------------------------------------------------|
|`==`    |Checks if the values of two operands are equal                                         |
|`!=`    |Checks if the values of two operands are not equal                                     |
|`>`     |Checks if the value of left operand is greater than the value of right operand         |
|`<`     |Checks if the value of left operand is less than the value of right operand            |
|`>=`    |Checks if the value of left operand is greater than or equal the value of right operand|
|`<=`    |Checks if the value of left operand is less than or equal the value of right operand   |

### Logical

|Operator|Description         |
|:------:|--------------------|
|`!`     |Logical NOT operator|

### Assignment

|Operator|Description                                                 |
|:------:|------------------------------------------------------------|
|`=`     |Assigns values from right side operands to left side operand|

## Operators Precedence

|Operator   |Associativity|
|:---------:|-------------|
|`!`        |Right to left|
|`* /`      |Left to right|
|`+ -`      |Left to right|
|`< <= > >=`|Left to right|
|`== !=`    |Left to right|
|`=`        |Right to left|

## Assembly Quadruples

|Quadruple          |Description                                      |
|-------------------|-------------------------------------------------|
|`LOADi $1`         |Reserve memory for integer variable $1           |
|`LOADd $1`         |Reserve memory for double variable $1            |
|`NOT $1, $2`       |$1 = !$2                                         |
|`MOV $1, $2`       |$1 = $2                                          |
|`ADD $1, $2, $3`   |$1 = $2 + $3                                     |
|`SUB $1, $2, $3`   |$1 = $2 - $3                                     |
|`MUL $1, $2, $3`   |$1 = $2 * $3                                     |
|`DIV $1, $2, $3`   |$1 = $2 / $3                                     |
|`CLT $1, $2, $3`   |$1 = 1 if $2 < $3 else 0                         |
|`CGT $1, $2, $3`   |$1 = 1 if $2 > $3 else 0                         |
|`CGE $1, $2, $3`   |$1 = 1 if $2 >= $3 else 0                        |
|`CLE $1, $2, $3`   |$1 = 1 if $2 <= $3 else 0                        |
|`CEQ $1, $2, $3`   |$1 = 1 if $2 == $3 else 0                        |
|`CNE $1, $2, $3`   |$1 = 1 if $2 != $3 else 0                        |
|`JZ  $1, label`    |Jump to label if $1 = 0                          |
|`JNZ $1, label`    |Jump to label if $1=  1                          |
|`JMP label`        |Unconditional jump to label                      |
