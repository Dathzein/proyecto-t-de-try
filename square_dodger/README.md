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

#### Con PowerShell (recomendado)

> Tip: abre PowerShell en la raíz del repo, o navega directo a `square_dodger/`.

```powershell
# Navegar al directorio del proyecto
cd .\square_dodger

# Agregar MinGW al PATH (ajusta la ruta si es necesaria)
$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"

# (Opcional) Si "cmake" no se reconoce, usa la ruta completa así:
# & "C:\Program Files\CMake\bin\cmake.exe" -G "MinGW Makefiles" -S . -B build

# Configurar CMake con MinGW
cmake -G "MinGW Makefiles" -S . -B build

# Compilar
cmake --build build

# Assets:
# El proyecto copia automáticamente `assets/` al directorio del ejecutable (post-build).
# Si por alguna razón no se copian, puedes hacerlo manualmente:
# Copy-Item -Recurse -Force .\assets .\build\assets
```

#### Alternativa con CMD:

```cmd
cd square_dodger
set PATH=C:\msys64\mingw64\bin;%PATH%
REM Si cmake no está en PATH, usa la ruta completa:
"C:\Program Files\CMake\bin\cmake.exe" -G "MinGW Makefiles" -S . -B build
cd build
mingw32-make.exe
xcopy /E /I ..\assets assets
```

### 3. Ejecutar el juego

```powershell
# Importante: agrega MinGW al PATH para que encuentre las DLLs de SFML
$env:PATH = "C:\msys64\mingw64\bin;$env:PATH"
.\build\square_dodger.exe
```

**Nota:** Asegúrate de que la carpeta `assets` esté en el mismo directorio que el ejecutable (normalmente `build/assets`).

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
- En PowerShell, para ejecutar un `.exe` con espacios en la ruta, usa el operador `&`:
  ```powershell
  & "C:\Program Files\CMake\bin\cmake.exe" --build build
  ```

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

### Windows: no abre la ventana / error por DLLs de SFML

- Si usas SFML desde MSYS2, agrega `C:\msys64\mingw64\bin` al `PATH` antes de ejecutar:
  ```powershell
  $env:PATH = "C:\msys64\mingw64\bin;$env:PATH"
  .\build\square_dodger.exe
  ```
