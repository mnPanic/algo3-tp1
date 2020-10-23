# algo3-tp1

TP1 de Algoritmos y Estructuras de datos 3

## Integrantes

| Nombre                 | LU     | Mail                    |
| ---------------------- | ------ | ----------------------- |
| Cerdeira, Elías Nahuel | 692/12 | eliascerdeira@gmail.com |
| Panichelli, Manuel     | 72/18  | panicmanu@gmail.com     |

## Implementación

En `src/main.cpp` se encuentra toda la implementación en c++ del TP, siguendo la
especificación de IO del enunciado (resultado por stdout y tiempo de ejecución
por stderr). Para compilar basta con hacer `make`, y para correr los tests
(en `tests/tests.py`), `make test`.

```bash
$ ./build/npm
Uso:
        $ ./tp1 <algorithm>
```

Ejemplo:

```bash
$ ./build/npm DP < tests/files/test-0.in
0.00769
70
```

## Experimentación

La experimentación se realizó con python, usando las bibliotecas `pandas` y
`seaborn`. Los notebooks hay que correrlos en orden:

1. `jupyter/instancias.ipynb`: Genera las instancias para luego correr los
   algoritmos.
2. `jupyter/experimentation.ipynb`: Corre los experimentos y guarda los
   resultados en `jupyter/resultados.csv`
3. `jupyter/analisis.ipynb`: Analiza los resultados obtenidos, genera las
   imagenes luego usadas en el informe.

Para correrlos se recomienda instalar primero los *requirements* (`pip3 install
-r requirements.txt`) dentro de un virtual env.

## Informe

El pdf se encuentra en [`informe/informe.pdf`](informe/informe.pdf), junto con
sus sources.

## Changelog

Cambios con respecto a la primer entrega.

- pd: Se simplifica la implementación.
- Informe:
  - Introducción: Se aclaran ejemplos y definición formal.
  - Metodología:
    - Se corrigen todos los pseudocodigos.
    - Se corrige la seccion de PD para que refleje la nueva implementación.
  - Experimentación
    - Se corrigen complejidades
    - Se explica con más detalle cómo se arman las instancias de control, low m y grupos.
    - Se aclara la justificación de por qué `BT-O` performa mejor que `BT-O-C`.
    - Se agrega conclusiones extra sobre comparativas con complejidada teórica.
  - Conclusión
    - Se aclara cuando las matrices resultan ralas
    - Se agrega que tipos de instancias son consideradas.
