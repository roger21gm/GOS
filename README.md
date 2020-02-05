# Especificació del llenguatge

## Típus bàsics

**`int`** Representa un típus enter

**`bool`**  Representa un booleà

`_`  Representa un valor buit o nul.

## Típus definits

- **Classes** Una `class` serà composada per atributs i  `constraint`s.

  ```java
  class nom_classe {
    <bloc definició constants>
    <bloc variables aux>
    <bloc variables de decisió>
    <bloc constraints>
    <implementació comparadors>?
  }
  ```

  - **Constraints** Es definiran constraints sobre les variables de la classe. 

    `constraint constraint_name { <restricció>* };`

    Es podran usar les següents <restricció>:

    - `forall` loops

      ```javascript
      forall(var_name in <rang|array>) {
      	<restricció>*
      }
      ```

    - `if-then-else` 

      ```
      if ( <exrp_booleana> ){	<restricció>* }
      <else if (<expr_booleana>){ <restricció>* }>*
      <else { <restricció>* }>?
      ```

    - comparadors

      ```
      <expr_int> <op_comparació> <expr_int>
      ```

    - global constraints

      - `all_different(<array>)`

  - **Implementació dels operadors** Es requerirà implementar únicament els operadors comparadors de `<` i `==` per tal de poder utilitzar realitzar operacions booleanes amb les instàncies dels objetes.

    ```
    
    ```

- **Arrays** Es podran definir arrays d'una o dos dimensions de qualsevol típus bàsic o classe. Es podrà limitar el domini de les variables de l'array a partir d'un rang de valors enters si es precedeix del token `of`.

  ```javascript
  <const|var|aux> <tipus_basic|nom_classe> <id>[<expr_int>]<[<expr_int>]>? <of rang>?;
  ```



## Variables

Existiran dos típus de variables `var` i `aux`. Les `var` seran les variables de decisió del model i les `aux` seran variables pre-calculades per simplificar les restriccions. Es podrà limitar el domini de les variables a partir d'un rang de valors enters si es precedeix del token `of`.

Una variable pot ser:

- Un típus bàsic
- Un típus definit

```javascript
<var|aux> <tipus> <of range>?;
```



## Constants

Una constant van precedides per `const` i poden ser:

- Un típus bàsic
- Un típus definit

Les constants s'hauran d'assignar des del fitxer de dades.

```javascript
const <tipus> <of range>?; 
```

## Rangs

Podrem definir rangs de valors per tal de limitar el domini d'una variable de decisió:

```javascript
<expr_int>..<expr_int>
```



## Llistes per comprensió

Una llista per comprensió definirà una array anònima:

`[ a * b | b in 1..10 where b < 3]`

```
[<expr_int> | <rang|array> <where <expr_bool>>?]
```

Es permetrà també generar llistes per comprensió a partir d'arrays de dos dimensions prèviament definides de la següent manera...

```
array[i][_] equival a [ sudoku[i][j] | j in 1..n]
array[_][j] equival a [ sudoku[i][j] | i in 1..n]
```

Servirà per convertir 

## Estructura general d'un programa

Un programa s'escriurà en un mínim de dos fitxers que definiran un model per un problema concret.

- **Fitxer del model:** Descriurà l'estructura del problema.

  ```pseudocode
  <bloc de definició de constants d'entrada>
  <bloc de definició de classes>
  <bloc de sortida>
  ```

- **Fitxer de les dades:** Contindrà les constants usades i requerides pel model.

  ```pseudocode
  <bloc d'assignació de constants>
  ```

  

## Identificadors

Els **identificadors** són una paraula sense espais que només pot contenir caràcters de l'abecedari gregorià, números i barres baixes: 

```
[A-Z|a-z|_][A-Z|a-z|0-9|_]*
```



## Comentaris

**Comentaris** d'una sola línia iniciats amb un coixinet,  **#**.

```
#.*
```



## Expressions

Una **expressió** pot ser:

- Un **valor constant** de típus bàsic

- Una **constant**

- Una **variable**

- Una **operació** sobre una o vàries expressions

- Una estructura `if-then-else` que s'expressa com:

  ```
  condició ? exprCert : exprFals
  ```

  - ***condició*** ha de ser una expressió de típus bool.
  - ***exprCert*** i ***exprFals*** han de ser una expressió del mateix típus.

- Una **funció definida**

Els **operadors** per les expressions són:

- `+`,  `-`,  `*`:  **suma**, **resta** i **multiplicació**. El resultat és un `int`.
- `/`,  `mod`: **divisió entera** i **mòdul**. El resultat és un `int`.
- `==`, `!=`: **igualtat** i **desigualtat**. El resultat és un `bool`.
- `<`, `<=`, `>`, `>=`: **més petit**, **més petit o igual**, **més gran** o **més gran o igual**. El resultat és un `bool`.
- `!`, `&&`, `||`: **negació lògica**, ***and* lògica**, ***or* lògica**. Definits únicament per `bool` i retorna `bool`.



## Exemples

### Problema de les _n_ reines

Amb input `n` equivalent al nombre de reines.

```
# Definició de les constants d'entrada.
const int n;

# Definició de classes amb variables i restriccions.
class Queens {
    var int q[n] of 1..n;
    
    constraint noAttack {
        forall (i in 1..n) {
            forall (j in i+1..n) {
                q[i] != q[j];
                q[i]+i != q[j]+j;
                q[i]-i != q[j]-j;
            }
        }
    }
}
```

### Sudoku 

Amb input:

```
iniSudoku.n = 9
iniSudoku.initial = [
    1, 0, 0, 5, 0, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 8, 0,
    0, 8, 0, 0, 0, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 7, 0, 0, 0, 0, 0, 2,
]
```

I el model:

```
# Definició de les constants d'entrada.
const Sudoku iniSudoku;

class Sudoku {
    //Input (constructor)
    const int n;
    const int initial[n][n] of 0..n;
    
    //Variables auxiliars
    aux int ssSize = sqrt(n); //subSquareSize
    
    //Variables a calcular
    var int sudoku[n][n] of 1..n;
    
    constraint fillInitial {
        forall (i in 1..n) {
            forall (j in 1..n) {
                if( initial[i][j] != 0 )
                    sudoku[i][j] = initial[i][j]
            }
        }
    }
    
    constraint uniqueRowsCols {
        forall (i in 1..n) {
            all_different(sudoku[i][_])
            all_different(sudoku[_][i])
        }
    }
    
    constraint uniqueSubSquares {
        forall (i in 1..ssSize) {
            forall (j in 1..ssSize) {
                alldifferent(
                    [ sudoku[a][b] | a, b in (i*(ssSize-1))..(i*(ssSize-1)+ssSize) ]
                );
            }
        }
    }
}
```

