# Square Dodger

Square Dodger es un juego de esquivar obstáculos desarrollado en C++ utilizando la biblioteca SFML.

## Requisitos Previos

Necesitas instalar **SFML 3** y **CMake** para compilar este proyecto.

## Guías de Instalación y Compilación por Sistema Operativo

Selecciona tu sistema operativo:
- [macOS](#macos)
- [Linux (Ubuntu/Debian)](#linux-ubuntudebian)
- [Windows](#windows)

---

## macOS

### 1. Instalar dependencias

```bash
brew install sfml
brew install cmake
```

### 2. Compilar el proyecto

```bash
# Navegar al directorio del proyecto
cd square_dodger

# Configurar CMake
cmake -S . -B build

# Compilar
cd build
make

# Copiar assets
cp -r ../assets .
```

### 3. Ejecutar el juego

```bash
./square_dodger
```

---

## Linux (Ubuntu/Debian)

### 1. Instalar dependencias

```bash
sudo apt-get update
sudo apt-get install libsfml-dev cmake g++
```

### 2. Compilar el proyecto

```bash
# Navegar al directorio del proyecto
cd square_dodger

# Configurar CMake
cmake -S . -B build

# Compilar
cd build
make

# Copiar assets
cp -r ../assets .
```

### 3. Ejecutar el juego

```bash
./square_dodger
```

---

## Windows

### 1. Instalar dependencias

#### Opción A: Usando MSYS2 (Recomendado)

1. Descarga e instala [MSYS2](https://www.msys2.org/)

2. Abre **MSYS2 MinGW 64-bit** y ejecuta:
   ```bash
   pacman -S mingw-w64-x86_64-sfml
   pacman -S mingw-w64-x86_64-cmake
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-make
   ```

### 2. Compilar el proyecto

#### Con MSYS2 MinGW 64-bit (PowerShell):

```powershell
# Navegar al directorio del proyecto
cd square_dodger

# Agregar MinGW al PATH (ajusta la ruta si es necesaria)
$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

# Configurar CMake con MinGW
"C:\Program Files\CMake\bin\cmake.exe" -G "MinGW Makefiles" -S . -B build

# Compilar
cd build
C:\msys64\mingw64\bin\mingw32-make.exe

# Copiar assets
cd build
cp -r ../assets .
```

#### Alternativa con CMD:

```cmd
cd square_dodger
set PATH=C:\msys64\mingw64\bin;%PATH%
"C:\Program Files\CMake\bin\cmake.exe" -G "MinGW Makefiles" -S . -B build
cd build
mingw32-make.exe
xcopy /E /I ..\assets assets
```

### 3. Ejecutar el juego

```powershell
.\square_dodger.exe
```

**Nota:** Asegúrate de que la carpeta `assets` esté en el mismo directorio que el ejecutable.

---

## Controles

- **A / D**: Mover Izquierda / Derecha
- **Espacio**: Saltar
- **Q**: Agacharse
- **R**: Reiniciar juego (en Game Over o Victoria)

---

## Solución de Problemas

### Windows: Error "cmake no se reconoce"
- Asegúrate de agregar CMake al PATH o usa la ruta completa: `"C:\Program Files\CMake\bin\cmake.exe"`

### Windows: Conflicto entre Visual Studio y MinGW
- Si tienes ambos instalados, limpia el directorio build y especifica el generador:
  ```powershell
  Remove-Item -Recurse -Force build\*
  cmake -G "MinGW Makefiles" -S . -B build
  ```

### "Failed to load font" al ejecutar
- Verifica que la carpeta `assets` esté en el mismo directorio que el ejecutable
- En Windows: `Copy-Item -Recurse assets build\`
- En Linux/macOS: `cp -r assets build/`
