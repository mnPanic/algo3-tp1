# TODO corrección

## Introduccion

- [] Aclarar definicion formal de problema
- [] Aclarar ejemplo

## Meotodlogia

### Fuerza Bruta

- [] Corregir justificacion de complejidad
- [] Hacer que el pseudocodigo sea mas codigo y menos coloquial
- [] Ejemplo: Agregar armado de casos, corregir solución optima

### BT

- [] Corregir pseudocodigo
- [] Corregir "la solucion optima": puede haber mas de una

### PD

- [] Agregar chequeo de vecindad a la formulación recursiva y a la parte de correctitud.
- [] Corregir el pseudocodigo

## Experimentación

### Metodos

- [] Corregir complejidades, tal vez estaría bueno explicar la variante cacheada en metodología.

### Control

- [] Explicar mejor como se arman las instancias aleatorias y por qué son "justas" para todas las técnicas.

### Podas

[] Buscar forma de que BT se vea en los graficos

#### Low M

[] Explicar como se generan las instancias
[] Buscar forma de que se vea BT en los graficos.

[] "Hay que mencionar que la magnitud del eje Y cambio con respecto al anterior"

#### Optimalidad - one to rule

- **pregunta si sera comun la variacion de la posicion para locales aleatorios**

- "por que un acceso a memoria es O(30)? al hacer cacheB[i] no hacen una pasada lineal, se accede directamente a esa posicion de memoria"
  Creo que no nos explicamos bien, y que habria que explicar mejor que la penalidada de ir a memoria termina siendo mas cara que O(30), ya que a pesar de que ir a memoria es "O(1)" es muy lento si no está en la cache lvl 1 y hay que ir a buscarlo a RAM. queremos ver que costo RAM <<< O(n) a partir de cierto n, y decimos que para n=30 no se cumple, sino que costo RAM > O(n).

Un buen punto: hacer crecer n de manera mas rapida, de 1 a 20 son todos iguales.
De esa forma correrian mas rapido los exp y sacariamos los n que no nos sirven del medio.

### Grupos

[] Explicar mejor grupos.
[] Aclarar que control es el dataset y no FB.
[] Explicar mas en detalle como se arman las instancias de grupos, para asi poder responder a la pregunta "el resto de los inputs se preserva? contagios y beneficio y cantidad de locales?"

### Complejidad

[] Aclarar que control es el dataset y no FB.
[] Hablar mas sobre los resultados de complejidad, quedan medio colgados. "Que tal pearson? dio bien? dio mal? que es un pearson alto, bajo, etc."

## Conclusion

[] Explicar cuando las matrices resultan ralas
[] Agregar que se evaluaron distintos tipos de instancias, aleatorias, one-to-rule, grupos, etc.