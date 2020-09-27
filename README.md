# algo3-tp1

TP1 de Algoritmos y Estructuras de datos 3

## Problema

- $M$ es el límite de contagio
- $n = \# \text{locales}$

## Algoritmos

- recursivo FB $O(n \times 2^n)$

  clasico de generar subconjuntos mediante backtracking, sol de
  $(a_1, ..., a_n)$ donde $a_i$ es verdadero si se incluye ese elemento. Y al
  final se chequea si el subconj obtenido cumple con las reestricciones.

- recursivo BT $O(n^2 \times 2^n)$ con poda por factibilidad y optimalidad
  p :: [(elegido, beneficio, contagio)], p_i

  - Podas
    - Factibilidad: facil.
    - Optimalidad: Ver en cada nodo si la suma de lo que queda es menor al maximo encontrado y podar.

- top-down de PD $O(n \times M)$

    funcion matematica definida recursivamente

    i local
    M contagio
    devuelve el max beneficio

    npm_pd(i, M) =
        -∞          M < 0
        0           i = 0

        max {
            npm_pd(i-1, M - c_i) + b_i,
            npm_pd(i-1, M),
        }

    el problema se resuelve llamando npm_pd(n, M)

    npm_pd(int i, int M, int n, bool b):
        if M < 0:
            return -∞

        if i == 0:
            return 0
        
        // check de validez
        if b && i != n:
            return -∞

        // llamado recursivo
        if mem[i][M] = UNDEFINED:
            mem[i][M] = max(
                npm_pd(i-1, M - c_i, b && true) + b_i,
                npm_pd(i-1, M, b && false),
            )

        return mem[i][M]


    llamar como npm_pd(n, M, n, true)

## Programación Dinámica

Justificación de la complejidad:

- Sabemos que existe a lo sumo `n*M` instancias de nuestro problema. Primero porque pudimos modelar todos los casos con 
una matriz de `n*M` y además porque, se podría pensar, que a cada comercio de 1 a n vamos a evaluar (tenerlo en cuenta o 
no) a lo sumo O(M) niveles de contagio diferentes. 
- Con programación dinámica con memoización, nos aseguramos de que se recorre solamente esa cantidad de instancias.
- Mediante el uso de backtracking nos aseguramos de estar recorriendo TODOS los casos posibles, los cuales presentan 
casos de solapamiento.
- Gracias a la memoización, cada problema lo resolvemos una sola vez.
- Por lo tanto, con backtracking, en lugar de visitar `2^n` nodos, estamos visitando todas las instancias (`n*M`) ya que
en caso de ya haberlo resuelto, se obtiene el valor de la estructura de guardado y se corta la ejecución de esa rama.
- Como la resolución de cada instancia se realiza en tiempo constante (O(1)), la complejidad total del algoritmo es: 
`O(n*M)`.

## Imágenes para los diagramas

- [local1](https://www.google.com/imgres?imgurl=http%3A%2F%2Finmoibaiondo.com%2Fwp-content%2Fuploads%2F2018%2F01%2Fventa-icono-300x215.png&imgrefurl=http%3A%2F%2Finmoibaiondo.com%2Flocales-comerciales-eibar-ermua-bajo-deba%2F&tbnid=HwosIl6u18C7RM&vet=12ahUKEwja4Lb0-fPrAhURBbkGHepBDEcQMygIegUIARCyAQ..i&docid=S8pM9h_SDtwXMM&w=300&h=215&q=imagenes%20locales%20comerciales%20png&ved=2ahUKEwja4Lb0-fPrAhURBbkGHepBDEcQMygIegUIARCyAQ)
- [local2](https://www.google.com/imgres?imgurl=https%3A%2F%2Fwww.clipartmax.com%2Fpng%2Fmiddle%2F62-626816_storefront-local-comercial-vector.png&imgrefurl=https%3A%2F%2Fwww.clipartmax.com%2Fmiddle%2Fm2i8H7m2A0Z5d3H7_storefront-local-comercial-vector%2F&tbnid=wtcVBDHGyHkvbM&vet=12ahUKEwja4Lb0-fPrAhURBbkGHepBDEcQMygEegUIARCqAQ..i&docid=_6EF9HMgCKWA0M&w=840&h=880&q=imagenes%20locales%20comerciales%20png&ved=2ahUKEwja4Lb0-fPrAhURBbkGHepBDEcQMygEegUIARCqAQ)
- [local3](https://www.google.com/imgres?imgurl=https%3A%2F%2Fanfix.com%2Fblog%2Fwp-content%2Fuploads%2F2016%2F02%2Falquiler.png&imgrefurl=https%3A%2F%2Fanfix.com%2Fblog%2Fque-clausulas-debe-contener-el-arrendamiento-de-un-local-de-negocio%2F&tbnid=-A2XzbLaSFaUTM&vet=12ahUKEwja4Lb0-fPrAhURBbkGHepBDEcQMygFegUIARCsAQ..i&docid=TIUPSPKXP3SPLM&w=1920&h=1080&q=imagenes%20locales%20comerciales%20png&ved=2ahUKEwja4Lb0-fPrAhURBbkGHepBDEcQMygFegUIARCsAQ)

- [Persona con barbijo](https://www.google.com/search?q=persona+barbijo+png&tbm=isch&ved=2ahUKEwja4Lb0-fPrAhURBbkGHepBDEcQ2-cCegQIABAA&oq=persona+barbijo+png&gs_lcp=CgNpbWcQAzICCAAyBggAEAgQHjIGCAAQCBAeOgQIABBDOgUIABCxAzoHCAAQsQMQQzoECAAQHjoGCAAQBRAeUN2nCFicwAhgr8MIaABwAHgAgAG_AogBvg6SAQgxMS4yLjIuMZgBAKABAaoBC2d3cy13aXotaW1nwAEB&sclient=img&ei=Yk9lX9qnEpGK5OUP6oOxuAQ&bih=789&biw=1440#imgrc=v9BQe4bz2NCwiM)

## Punteo de ideas para la experimentación

- PD: solapamiento artificial y jugar con la relación entre 2^n y n * m.
- BT:
    - Optimalidad: generar instancias que funcionarían bien con el algoritmo goloso.
    Por ejemplo, generar intercalado entre locales de mayor ratio beneficio/contagio.
    - Factibilidad: generar instancias donde con pocos locales ya se exceda el límite de contagio.
- FB: alguna combinación donde sean INÚTILES las podas, i.e. contagios bajos, tolerancia alta (M) y mucha dependencia en la vecindad.

## Experimentación

Podríamos dividir en dos grandes categorías los experimentos, en referencia al análisis de los resultados:

- Complejidad (tiempo)
- Comparativa entre técnicas (FB, BT, PD)

### Instancias

- *Control*: generada de manera aleatoria.

- Factibilidad: las podas no tienen _contra_ porque se realizan en O(1).
    - Generar instancias donde con pocos locales ya se exceda el límite de contagio. Debido a que excederemos rápidamente el M.
    - Hipótesis: para casos donde no se excede el M, hasta no haber recorrido toda una rama, BT-F debería ser mucho mejor que FB por la poda de vecindad.
- Optimalidad:
    - *Uno para dominarlos a todos*: tener un conjunto de locales donde todos tengan un aporte similar de beneficio económico y un único local con un beneficio mayor que la suma de todos los demás. De esta manera, esperamos que el algoritmo de BT-O corte cada vez que llegue a la rama que contiene a este local especial.
    - *Uniformidad*: si contamos con todos locales _idénticos_ la poda por optimalidad no será útil, debido a que tendremos el _overhead_ del cálculo realizado (O(n)), pero nunca aprovecharemos su resultado (cortar antes de tiempo).
- PD: 
    - *Solapamiento*: se podría completar una matriz paralela a la matriz correspondiente al algoritmo de PD que permita conocer la cantidad de veces que fue utilizada una celda de la memoria. De esta manera, se podría utilizar para generar un _heatmap_ que permita conocer la densidad de accesos a cada región. Esto nos permitiría saber cuánto solapamiento tiene una instancia.
        - _Hipótesis_: existe correlación entre el porcentaje de locales que comparten el mismo grado de contagio y el nivel de solapamiento observado. Para probar esto podríamos diseñar distantas instancias que varíen de alguna manera a definir este porcentaje. Podría definirse una variable _G_ que determine el número de grupos en que se dividirán los locales de la instancia. El grado de contagio de cada grupo estará definido de la siguiente manera: _grupo i_ -> _contagio i * 10_.
    - *PD Negativo - Memoria Cache*: en una instancia de un tamaño no demasiado grande (modesto, según Manuel) tal que la tabla COMPLETA no entre en la CACHÉ, si no tiene solapamiento, se debería notar el _overhead_ de la lectura de la memoria.

### Experimentos para optimalidad

- Calcular up front el algoritmo goloso para todos los i-es.
- Hacer el naive sumando todo lo restante y diviendo por dos.
- El goloso deberia andar mejor que el naive, ya que provee estimaciones
  muchisimo mas precisas, y con un costo de O(1) al estar precalculado.
- Exp: correrlos todos contra FB para instancias de control para ver cual es
  mejor.

### TODOs

domingo:

- mejorar BT-O.
- graficos y informe.