<div align="center">
  
# 🎮 So Long

**Un juego 2D minimalista desarrollado en C usando MLX42**

[![42](https://img.shields.io/badge/42-Project-000000?style=flat-square&logo=42)]()
[![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)]()
[![MLX42](https://img.shields.io/badge/MLX42-Graphics-FF6B6B?style=flat-square)]()

</div>

## 📋 Descripción

**So Long** es un juego 2D estilo arcade donde el jugador debe recolectar todos los elementos del mapa y encontrar la salida. Desarrollado como parte del curriculum de 42, este proyecto enseña conceptos fundamentales de programación gráfica, manejo de eventos y estructuras de datos.

### ✨ Características

- 🎯 **Gameplay simple pero adictivo** - Recoge todos los coleccionables y escapa
- 🗺️ **Mapas personalizables** - Formato `.ber` fácil de editar
- ⌨️ **Controles intuitivos** - WASD o flechas para movimiento
- 🎨 **Gráficos pixel art** - Estética retro y minimalista
- 📊 **Contador de movimientos** - Rastrea tu eficiencia
- ✅ **Validación de mapas** - Verifica que el mapa sea jugable

## 🚀 Instalación

### Dependencias

Asegúrate de tener instalado:
- **GCC** o **Clang**
- **Make**
- **CMake** (≥ 3.18)
- **GLFW** (≥ 3.3)

#### En macOS:
```bash
# Con Homebrew
brew install glfw cmake

# Con 42Homebrew
bash -c "$(curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh)"
```

#### En Linux (Ubuntu/Debian):
```bash
sudo apt update
sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev cmake
```

### Compilación

```bash
# Clona el repositorio
git clone [tu-repo-url] so_long
cd so_long

# Compila el proyecto
make

# O si prefieres compilar manualmente MLX42:
cmake -B MLX42/build MLX42
cmake --build MLX42/build -j4
make
```

## 🎮 Uso

```bash
# Ejecutar el juego
./so_long maps/map_medium.ber

# Ejemplos con diferentes mapas
./so_long maps/map_small.ber    # Mapa pequeño para principiantes
./so_long maps/map_big.ber      # Mapa desafiante
```

### 🎯 Objetivo del Juego

1. **Mueve** al jugador (🎮) por el mapa
2. **Recolecta** todos los elementos (💎)
3. **Encuentra** la salida (🚪)
4. **Completa** el nivel con el menor número de movimientos

### ⌨️ Controles

| Tecla | Acción |
|-------|--------|
| `W` / `↑` | Mover arriba |
| `A` / `←` | Mover izquierda |
| `S` / `↓` | Mover abajo |
| `D` / `→` | Mover derecha |
| `ESC` | Salir del juego |

## 🗂️ Estructura del Proyecto

```
so_long/
├── 📁 srcs/               # Código fuente principal
│   ├── main.c            # Punto de entrada
│   ├── init.c            # Inicialización del juego
│   ├── map_parser.c      # Análisis de mapas
│   ├── map_checker.c     # Validación de mapas
│   ├── map_utils.c       # Utilidades de mapas
│   ├── render.c          # Sistema de renderizado
│   ├── player.c          # Lógica del jugador
│   ├── utils.c           # Funciones auxiliares
│   └── error.c           # Manejo de errores
├── 📁 includes/          # Archivos de cabecera
│   └── so_long.h        # Definiciones principales
├── 📁 maps/              # Mapas del juego
│   ├── map_small.ber    # Mapa pequeño
│   ├── map_medium.ber   # Mapa mediano
│   └── map_big.ber      # Mapa grande
├── 📁 textures/          # Sprites del juego
│   ├── player.png       # Sprite del jugador
│   ├── wall.png         # Sprite de pared
│   ├── floor.png        # Sprite de suelo
│   ├── collectible.png  # Sprite de coleccionable
│   └── exit.png         # Sprite de salida
├── 📁 Libft/             # Biblioteca personal de C
├── 📁 GNL/               # Get Next Line para lectura de archivos
├── 📁 MLX42/             # Biblioteca gráfica
└── Makefile             # Sistema de compilación
```

## 🛠️ Tecnologías Utilizadas

- ![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c&logoColor=white) **Lenguaje C** - Programación principal
- ![MLX42](https://img.shields.io/badge/MLX42-FF6B6B?style=flat) **MLX42** - Biblioteca gráfica para renderizado
- ![GLFW](https://img.shields.io/badge/GLFW-0F1419?style=flat) **GLFW** - Gestión de ventanas y eventos
- ![OpenGL](https://img.shields.io/badge/OpenGL-5586A4?style=flat&logo=opengl&logoColor=white) **OpenGL** - Renderizado de gráficos

## 🗺️ Formato de Mapas

Los mapas usan el formato `.ber` con estos caracteres:

| Carácter | Elemento |
|----------|----------|
| `1` | Pared |
| `0` | Espacio vacío |
| `P` | Posición inicial del jugador |
| `E` | Salida |
| `C` | Coleccionable |

### Ejemplo de mapa válido:
```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

### Reglas de validación:
- ✅ El mapa debe estar rodeado por paredes (`1`)
- ✅ Debe contener exactamente 1 jugador (`P`)
- ✅ Debe contener exactamente 1 salida (`E`)
- ✅ Debe contener al menos 1 coleccionable (`C`)
- ✅ Debe existir un camino válido desde el jugador hasta la salida
- ✅ Todos los coleccionables deben ser alcanzables

## 🧪 Testing

```bash
# Verificar memory leaks
make val

# Test con diferentes mapas
./so_long maps/map_small.ber
./so_long maps/map_medium.ber
./so_long maps/map_big.ber
```

## 📝 Notas de Desarrollo

Este proyecto implementa:
- **Algoritmo Flood Fill** para validación de mapas
- **Sistema de eventos** para entrada del usuario
- **Renderizado eficiente** con MLX42
- **Gestión de memoria** sin memory leaks
- **Manejo de errores** robusto

## 📄 Licencia

Este proyecto fue desarrollado como parte del curriculum de 42. Consulta las normas de tu campus respecto al uso y distribución del código.

---

<div align="center">

**Hecho con ❤️ por [Juan Fernández](https://github.com/jjfernaa)**

</div>
