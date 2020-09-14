# algo3-tp1
TP1 de Algoritmos y Estructuras de datos 3

Problema

- $M$ es el límite de contagio
- $n = \# \text{locales}$

Algoritmos

- recursivo FB $O(n \times 2^n)$

  clasico de generar subconjuntos mediante backtracking, sol de
  $(a_1, ..., a_n)$ donde $a_i$ es verdadero si se incluye ese elemento. Y al
  final se chequea si el subconj obtenido cumple con las reestricciones.

- recursivo BT $O(n^2 \times 2^n)$ con poda por factibilidad y optimalidad
  p :: [(elegido, beneficio, contagio)], p_i

  - Podas
    - Factibilidad: facil.
    - Optimalidad: Ver en cada nodo si la suma de lo que queda es menor al maxim
    o encontrado y podar.

- top-down de PD $O(n \times M)$

    que carajo es la M

    Si vas decrementando M con cada llamado recursivo, entonces podes guardar en
    la tabla M x n donde n es el indice de comercio y M es el contagio hasta ese
    momento.

    f(n, M, )

    maxBeneficio(i, T, ...) \in O(n M)
        = 0                                 i = 0 || T < 0
        = max {
            maxBeneficio(i - 1, T)          // no agregarlo
            maxBeneficio(i - 1, T - b[i])   // agregarlo
        }

    10
    10 9

    8
    1 3 6 b80 t20  |  2 5 b60 t20

Dudas

- Superposicion en PD? Que onda la complejidad? Por que M