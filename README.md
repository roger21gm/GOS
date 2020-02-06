# Especificació del llenguatge

## Típus de dades

### Tipus bàsics

**`int`** Representa un tipus enter. 

**`bool`**  Representa un booleà. Pot prendre per valor **true** o **false**

`_`  Representa un valor buit o nul.



### Tipus definits

- **Classes** Estructura que serà composada d'atributs (variables `var`, `aux` i constants `const`) i `constraint`s.

- **Arrays** Es podran definir arrays d'una o dos dimensions de qualsevol típus bàsic o classe. Es podrà limitar el domini de les variables de l'array a partir d'un rang.

  

## Estructura general d'un programa

Un programa s'escriurà en un mínim de dos fitxers que definiran un model per un problema concret.

- **Fitxer del model:** Descriurà l'estructura del problema.

  ```pseudocode
  <definició de constants d'entrada>*
  <definició de classes>*
  <bloc de sortida>?
  ```

- **Fitxer de les dades:** Contindrà les constants usades i requerides pel model.

  ```pseudocode
  <bloc d'assignació de constants>
  ```




## Identificadors

Els **identificadors** són una paraula sense espais que només pot contenir caràcters de l'abecedari gregorià, números i barres baixes: 

```pseudocode
[A-Z|a-z|_][A-Z|a-z|0-9|_]*
```



## Comentaris

**Comentaris** d'una sola línia iniciats amb un coixinet,  **#**.

```pseudocode
#.*
```



## Expressions

Una **expressió** pot ser:

- Un **valor constant** de típus bàsic

- Una **constant**

- Una **variable**

- Una **operació** sobre una o vàries expressions

- Una estructura `if-then-else` que s'expressa com:

  ```pseudocode
  condició ? exprCert : exprFals
  ```

  - ***condició*** ha de ser una expressió de típus bool.
  - ***exprCert*** i ***exprFals*** han de ser una expressió del mateix típus.

- Una **funció definida**

- Un valor nul `_`

Els **operadors** per les expressions són:

- `+`,  `-`,  `*`:  **suma**, **resta** i **multiplicació**. El resultat és un `int`.
- `/`,  `mod`: **divisió entera** i **mòdul**. El resultat és un `int`.
- `==`, `!=`: **igualtat** i **desigualtat**. El resultat és un `bool`.
- `<`, `<=`, `>`, `>=`: **més petit**, **més petit o igual**, **més gran** o **més gran o igual**. El resultat és un `bool`.
- `!`, `&&`, `||`: **negació lògica**, ***and* lògica**, ***or* lògica**. Definits únicament per `bool` i retorna `bool`.



## Classes

Una `class` serà composada per atributs i  `constraint`s.

```java
class nom_classe {
  <definició constants>*
  <definició variables aux>*
  <definició variables de decisió>*
  <constraints>*
  <definició de funcions>*
  <implementació comparadors>?
}
```

- **Definició de funcions** Es podran generar mètodes  amb un valor de retorn que es podran cridar des d'altres classes que tinguin instàncies de la classe

  ```pseudocode
  function <tipus> 𝑛𝑜𝑚_𝑓𝑢𝑛𝑐𝑖𝑜 (<<tipus><ident> <,<tipus><ident>>*>?){
  	𝐫𝐞𝐭𝐮𝐫𝐧 <expr>
  }
  ```

- **Implementació dels operadors** Es requerirà implementar únicament els operadors comparadors de `<` i `==` per tal de poder utilitzar realitzar operacions booleanes amb les instàncies dels objetes.



### Constants

Una constant van precedides per `const` i poden ser:

- Un típus bàsic
- Un típus definit

Les constants s'hauran d'assignar des del fitxer de dades.

```pseudocode
𝐜𝐨𝐧𝐬𝐭 <tipus> 𝑛𝑜𝑚_𝑐𝑜𝑛𝑠𝑡𝑎𝑛𝑡 <definicio_array>? <rang>?; 
```



### Variables

Existiran dos típus de variables `var` i `aux`. Les `var` seran les variables de decisió del model i les `aux` seran variables pre-calculades per simplificar les restriccions. Es podrà limitar el domini de les variables a partir d'un rang.

Una variable pot ser de típus bàsic o definit.

- **Definició de variables:**

  ```pseudocode
  𝐯𝐚𝐫 <tipus> 𝑛𝑜𝑚_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒 <rang>?;
  ```

  Les variables auxiliars `aux` s'hauran d'assignar al moment de definirles:

  ```pseudocode
  𝐚𝐮𝐱 <tipus> 𝑛𝑜𝑚_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒 = <expr>;
  ```

- **Assignació de variables**:

  - De típus bàsic 

    ```
    𝑛𝑜𝑚_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒 = <expr>;
    ```

  - Objectes:

    ```pseudocode
    𝑛𝑜𝑚_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒.nom_atribut = <expr>;
    ```

  - Arrays:

    ```pseudocode
    𝑛𝑜𝑚_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒 = [<<expr><,<expr>>*>?]
    ```

    

### Constraints

Només es podran definir constraints dins una class. Es definiran `constraint`s sobre les variables de la classe:

`constraint constraint_name { <restricció>* };`

Es podran usar els següents típus de **<restricció>**:

- `forall` loops

  ```pseudocode
  𝐟𝐨𝐫𝐚𝐥𝐥(𝑣𝑎𝑟_𝑛𝑎𝑚𝑒 in <rang|array>) {
  	<restricció>*
  }
  ```

- `if-then-else` 

  ```pseudocode
  <𝐢𝐟 ( <exrp_booleana> ){	<restricció>* }>
  <𝐞𝐥𝐬𝐞 𝐢𝐟 (<expr_booleana>){ <restricció>* }>*
  <𝐞𝐥𝐬𝐞 { <restricció>* }>?
  ```

- operació relacional

  ```pseudocode
  <expr_int> <op_relacional> <expr_int>
  ```

- crida a funció

  ```pseudocode
  𝑛𝑜𝑚_𝑓𝑢𝑛𝑐𝑖𝑜(<<expr><,<expr>>*>?)
  ```

  - `𝐚𝐥𝐥_𝐝𝐢𝐟𝐟𝐞𝐫𝐞𝐧𝐭(<list|array>)`



## Arrays

Es podran definir arrays d'una o dos dimensions de qualsevol típus bàsic o classe. Es podrà limitar el domini de les variables de l'array a partir d'un rang.

- **Definició d'un array** Per definir un array ho farem de la mateixa manera que una variable però afegint el número de dimensions i la mida de cada dimensió. 

  ```pseudocode
  <aux|var|const> nom_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒[<expr_int>] <[<expr_int>]>? <rang>?
  ```

- **Accés a un array** Per accedir a una posició d'un array es farà:

  ```pseudocode
  𝑖𝑑_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒[<expr_int>]<[<expr_int>]>?
  ```

  

## Objectes

Un objecte és una instància concreta d'una `class`. 

- Accés a atributs d'un objecte

  ```pseudocode
  𝑛𝑜𝑚_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒.nom_atribut
  ```

- Accés a funcions d'un objecte

  ```pseudocode
  𝑛𝑜𝑚_𝑣𝑎𝑟𝑖𝑎𝑏𝑙𝑒.nom_funcio(<<expr><,<expr>>*>?)
  ```

  



## Estructures generadores

### Rangs

Podrem definir rangs de valors per tal de limitar el domini d'una variable de decisió:

```javascript
in <expr_int>..<expr_int>
```



### Llistes per comprensió

Una llista per comprensió definirà una array anònima. Es podran generar de diverses maneres:

- A partir de variables temporals `[ a * b | b, a in 1..10 where b < 3 and a != 4]`:

  ```pseudocode
  [<expr_int> | <nom_var><,<nom_var>>? <rang> <<nom_var><,<nom_var>>? <rang>>? <where <expr_bool>>?]
  ```

- A partir d'un array definit d'una sola dimensió `[ point.x * 2 | point in points where point.y > 4]`

  ```pseudocode
  [ <expr_int> | <nom_var> in <array> <where <expr_bool>>?]
  ```

- També es permetrà també generar llistes per comprensió a partir d'arrays de dos dimensions prèviament definides de la següent manera:

  ```pseudocode
  array[i][_] equival a [ sudoku[i][j] | j in 1..n]
  array[_][j] equival a [ sudoku[i][j] | i in 1..n]
  ```



## Exemples

### Problema de les _n_-reines

Amb input:

```pseudocode
nQueens.n = 7;
```

I el model:

```pseudocode
# Definició de les constants d'entrada.
const Queens nQueens;

# Definició de classes amb variables i restriccions.
class Queens {
		const int n;
    var int q[n] in 1..n;
    
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

```pseudocode
iniSudoku.n = 9
iniSudoku.initial = [
    1, _, _, 5, _, _, _, _, 1,
    _, _, _, _, _, _, _, _, _,
    _, _, _, _, _, _, _, 8, _,
    _, 8, _, _, _, 5, _, _, _,
    _, _, _, _, _, _, _, _, _,
    _, _, _, _, _, _, _, _, _,
    _, _, _, 9, _, _, _, _, _,
    _, _, _, _, _, _, _, _, _,
    _, _, 7, _, _, _, _, _, 2,
]
```

I el model:

```pseudocode
# Definició de les constants d'entrada.
const Sudoku iniSudoku;

class Sudoku {
    //Input (constructor)
    const int n;
    const int initial[n][n] in 0..n;
    
    //Variables auxiliars
    aux int ssSize = sqrt(n); //subSquareSize
    
    //Variables a calcular
    var int sudoku[n][n] in 1..n;
    
    constraint fillInitial {
        forall (i in 1..n) {
            forall (j in 1..n) {
                if( initial[i][j] != _ )
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



## Packing squares problem

Amb input:

```pseudocode
bigSquare.sideSize = 5
bigSquare.nSquares = 8

bigSquare.s[0].size = 3
bigSquare.s[1].size = 2
bigSquare.s[2].size = 2
bigSquare.s[3].size = 2
bigSquare.s[4].size = 1
bigSquare.s[5].size = 1
bigSquare.s[6].size = 1
bigSquare.s[7].size = 1
```

I el model:

```pseudocode
const PackSquare bigSquare;

class PackSquare {
	const int sideSize;
	const int nSquares;
	const Square s[nSquares];
	
	constraint inside {
		forall(i in 1..nSquares){
			s[i].x <= sideSize - s[i].size + 1;
			s[i].y <= sideSize - s[i].size + 1;
		}
	}
	
	constraint noOverlap {
		forall (i in 1..nSquares){
			forall (j in i+1..nSquares){
				   s[i].x + s[i].size <= s[j].x 
				|| s[j].x + s[j].size <= s[i].x 
				|| s[i].y + s[i].size <= s[i].y 
				|| s[j].y + s[j].size <= s[i].y 
			}
		}
	}
	
	constraint fitArea {
		sum (i in 1..nSquares)(s[i].size * s[i].size) = sideSize * sideSize;
	}
}

class Square {
	var int x;
  var int y;
  const int size;
}
```

