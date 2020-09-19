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
