# TODO corrección

Comentarios de juli

- Sobre el pseudocodigo: esta bien que quede igual que el codigo original, dicen
  de no hacer copy paste para que la gente no haga *literalmente* copy paste.
- Sobre PD: se puede hacer que se saltee el caso en el que no seria factible, y
  de esa forma no se memoizan cosas que no son. Probar con tests

## Introduccion

- [X] Aclarar definicion formal de problema
- [X] Aclarar ejemplo

## Meotodlogia

### Fuerza Bruta

- [X] Corregir justificacion de complejidad
- [X] Hacer que el pseudocodigo sea mas codigo y menos coloquial
- [X] Ejemplo: Agregar armado de casos, corregir solución optima

### BT

- [X] Corregir pseudocodigo
- [X] Corregir "la solucion optima": puede haber mas de una

### PD

- [X] Agregar chequeo de vecindad a la formulación recursiva y a la parte de correctitud.
- [X] Corregir el pseudocodigo

## Experimentación

### Metodos

- [] Corregir complejidades, tal vez estaría bueno explicar la variante cacheada en metodología.

### Control

- [] Explicar mejor como se arman las instancias aleatorias y por qué son "justas" para todas las técnicas.

### Podas

[] Buscar forma de que BT se vea en los graficos
**Pregunta** como hacemos si no hay espacio, sacamos cosas?
Nada, solamente aclarar en las caption con que se solapa BT.

#### Low M

[] Explicar como se generan las instancias
[] Buscar forma de que se vea BT en los graficos.

[] "Hay que mencionar que la magnitud del eje Y cambio con respecto al anterior"

#### Optimalidad - one to rule

- **pregunta si sera comun la variacion de la posicion para locales aleatorios**

- "por que un acceso a memoria es O(30)? al hacer cacheB[i] no hacen una pasada lineal, se accede directamente a esa posicion de memoria"
  Creo que no nos explicamos bien, y que habria que explicar mejor que la
  penalidad de ir a memoria termina siendo mas cara que O(30), ya que a pesar de
  que ir a memoria es "O(1)" es muy lento si no está en la cache lvl 1 y hay que
  ir a buscarlo a RAM. queremos ver que costo RAM <<< O(n) a partir de cierto n,
  y decimos que para n=30 no se cumple, sino que costo RAM > "O(30)".

Posible explicacion consensuada con juli: lo mismo de ram con O(n), pero es raro
que sea eso porque el no cacheado tambien accede al vector de vecinos. Pero puede
pasar que como el vector de vecinos se accede con mas frecuencia que el
precalculado, entonces siempre esta en la cache del procesador, mientras que el
otro tal vez se desaloja y se tiene que buscar de RAM.

Un buen punto: hacer crecer n de manera mas rapida, de 1 a 20 son todos iguales.
De esa forma correrian mas rapido los exp y sacariamos los n que no nos sirven del medio.

### Grupos

[] Explicar mejor grupos (literal lo que dice juli)
[] Aclarar que control es el dataset y no FB.
[] Explicar mas en detalle como se arman las instancias de grupos, para asi poder responder a la pregunta "el resto de los inputs se preserva? contagios y beneficio y cantidad de locales?"

### Complejidad

[] Aclarar que control es el dataset y no FB.
[] Hablar mas sobre los resultados de complejidad, quedan medio colgados. "Que tal pearson? dio bien? dio mal? que es un pearson alto, bajo, etc."

**Pregunta**: cual es un pearson bajo/alto para computacion?

## Conclusion

[X] Explicar cuando las matrices resultan ralas, y aclarar que una matriz rala es
aquella con muchos 0s.
[X] Agregar que se evaluaron distintos tipos de instancias, aleatorias, one-to-rule, grupos, etc.