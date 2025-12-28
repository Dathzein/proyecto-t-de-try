# Square Dodger

Square Dodger es un juego de esquivar obstáculos desarrollado en C++ utilizando la biblioteca SFML.

## Requisitos Previos

Necesitas instalar **SFML 3** y **CMake** para compilar este proyecto.

### macOS
```bash
brew install sfml
brew install cmake
```

### Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install libsfml-dev cmake g++
```

### Windows
1. Descarga SFML 3 desde [sfml-dev.org](https://www.sfml-dev.org).
2. Instala CMake desde [cmake.org](https://cmake.org).
3. Configura tu compilador (MinGW o Visual Studio).

## Compilación y Ejecución

Sigue estos pasos en tu terminal:

1. Clona el repositorio y entra en la carpeta:
   ```bash
   cd square_dodger
   ```

2. Crea una carpeta de compilación:
   ```bash
   mkdir build && cd build
   ```

3. Generar los archivos de construcción con CMake:
   ```bash
   cmake ..
   ```

4. Compilar el juego:
   ```bash
   make
   ```

5. Copiar los assets (fuentes/imágenes) a la carpeta del ejecutable:
   ```bash
   cp -r ../assets .
   ```

6. Ejecutar el juego:
   ```bash
   ./square_dodger
   ```

## Controles
- **A / D**: Mover Izquierda / Derecha
- **Espacio**: Saltar
- **Q**: Agacharse
- **R**: Reiniciar juego (en Game Over o Victoria)
