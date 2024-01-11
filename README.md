# Batalla Naval Simulator

Este repositorio contiene un programa en C++ que simula el juego de la "Batalla Naval". El juego consiste en un tablero de 10x10 casilleros donde se posicionan 10 barcos de uno a cuatro casilleros, ya sea en forma horizontal o vertical. El objetivo es hundir todos los barcos a través de lanzamientos de "bombas" en posiciones específicas.

### Autores:
- **Bottini, Franco Nicolas**
- **Robledo, Valentin**

## Estrategias de Juego

### Estrategias de Encolamiento
El programa simula tres estrategias de encolamiento de las pilas de posiciones a las cuales disparar:

1. **Encolamiento Secuencial por Filas (SPF):** Encola las posiciones siguiendo un orden contiguo con respecto a las filas.
2. **Encolamiento Secuencial por Columnas (SPC):** Encola las posiciones siguiendo un orden contiguo con respecto a las columnas.
3. **Encolamiento Aleatorio (A):** Encola las posiciones siguiendo un orden completamente aleatorio.

### Algoritmos de Disparo
El programa también simula tres algoritmos de disparo:

1. **Sin Memoria (SM):** El algoritmo de disparo no tiene "memoria" de los lugares en los cuales ya disparó, permitiendo disparar dos o más veces en el mismo casillero.
2. **Con Memoria (CM):** El algoritmo de disparo tiene "memoria" de los lugares en los cuales ya disparó, evitando disparar más de una vez en el mismo casillero.
3. **Completo (C):** Además de tener "memoria", el algoritmo de disparo no dispara en los lugares adyacentes a un barco, cumpliendo con las reglas del juego.

## Resultados y Conclusiones
Se realizaron 10,000 simulaciones para cada combinación de estrategia de encolamiento y algoritmo de disparo. Los resultados se presentan en gráficos dentro del `informe.pdf`. Como conclusión, se observa que el encolamiento por filas y por columnas tiene un rendimiento similar. Además, el algoritmo de disparo completo es el más eficiente independientemente del método de encolamiento utilizado. La combinación más rentable es el encolamiento secuencial completo (por filas o por columnas).