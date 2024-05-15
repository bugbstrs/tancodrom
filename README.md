# ?
`Tancodrom` is a team project currently in development for the SMMG3D 2023-2024 (**S**isteme **M**oderne de **M**odelare **G**rafica **3D**) course held at Transilvania University of Brasov's [Faculty of Mathematics and Computer Science](https://mateinfo.unitbv.ro) (study programme: Computer Science).

# 📜 Table of contents
- [🧑‍🤝‍🧑‍ Team members](#🧑‍🤝‍🧑‍-team-members)
- [📎 Basic description](#📎-basic-description)
- [🔌 Main features](#🔌-main-features)
- [💡 Possible extensions](#💡-possible-extensions-of-the-main-features)
- [🔨 Building the project](#🔨-building-the-project)
  - [🪟 Windows](#🪟-windows)
    - [🧱 Base requirements](#🧱-base-requirements)
    - [🕹️ Installing `vcpkg` (Windows)](#🕹️-installing-vcpkg-on-windows)
  - [🐧 Fedora 40](#🐧-fedora-40)
    - [💿 Installing dependencies](#💿-installing-dependencies)
      - [⚠️ Mentions](#⚠️-mentions)
      - [💿 vcpkg install dependencies](#💿-vcpkg-install-dependencies)
      - [💿 Project base dependencies](#💿-project-base-dependencies)
      - [💿 `glfw3` dependencies](#💿-glfw3-dependencies)
      - [💿 `glew` dependencies](#💿-glew-dependencies)
      - [💿 `ALSA` dependencies](#💿-alsa-dependencies)
      - [💿 `SFML` dependencies](#💿-sfml-dependencies)
      - [💿 Visual Studio and WSL development dependencies](#💿-visual-studio-and-wsl-development-dependencies)
    - [🕹️ Installing vcpkg on Fedora 40](#🕹️-installing-vcpkg-on-fedora-40)
- [ℹ️ Other project info](#ℹ️-project-info)

# 🧑‍🤝‍🧑‍ Team members
- Teglas Dennis-Vlăduț • [github](https://github.com/tdenniss) • [dennis.teglas@student.unitbv.ro](mailto:dennis.teglas@student.unitbv.ro)
- Stoica David-Ioan • [github](https://github.com/stoica-david) • [david.stoica@student.unitbv.ro](mailto:david.stoica@student.unitbv.ro)
- Tufeanu Andrei-Ionuț • [github](https://github.com/andreitufeanu) • [andrei.tufeanu@student.unitbv.ro](mailto:andrei.tufeanu@student.unitbv.ro)
- Sas Vlad-Ștefan • [github](https://github.com/vlsts) • [me@svs.pm](mailto:me@svs.pm) • [pgp key](https://keys.openpgp.org/search?q=ED82B2B95B3BEC7FEFC59C956E2186ECD0848BCA) (commits signed with this key until `cd6312f5`, from that point commits are signed with a SSH key)

# 📎 Basic description
Simulation of a tank and helicopter tanker field on a battlefield, with clouds, having day and night cycles.

# 🔌 Main features
- 3D scene to simulate the field
- Day / Night cycles
- Animations for the various components such as:
  - Propeller rotation
  - Tank & Helicopter movement
- Tank / Helicopter control
- Dynamic camera
- Shadows and lights for the various objects
- Specific textures for each object
- Terrain

# 💡 Possible extensions of the main features
- Collisions
- Projectile shooting
- SFX / Background music
- Cinema mode
- Tank / Helicopter particles

# 🔨 Building the project
## 🪟 Windows
### 🧱 Base requirements
- Microsoft Visual C++ `>= C++23` (or GCC if building on Fedora)
- `vcpkg`
- CMake `>= 3.20`
- ninja `>= 1.12`

### 🕹️ Installing vcpkg on Windows

- Clone [this](https://github.com/microsoft/vcpkg.git) repository wherever you would like to have vcpkg installed
- Open a terminal
  - `cd` into the vcpkg folder
  - run the bootstrap script (`bootstrap-vcpkg.bat`)
- Set the following environment variables
  - `VCPKG_ROOT` to wherever your vcpkg folder is located
  - Change `Path` and add `%VCPKG_ROOT%` to it
- Close all of your Visual Studio instances and also any opened terminals
- Open a terminal and run `vcpkg integrate install`

## 🐧 Fedora 40

### 💿 Installing dependencies
#### ⚠️ Mentions
This project works on a standard Fedora Workstation 40 installation. The required packages were derived from a WSL Fedora 40 Container though and some might already be installed on your system. Trying to run this app on a WSL Fedora container with the packages will most likely fail.

#### 💿 vcpkg install dependencies
```console
sudo dnf install git nano curl zip unzip tar
```

#### 💿 Project base dependencies
```console
sudo dnf install cmake gcc gcc-c++ ninja-build
```

#### 💿 glfw3 dependencies
```console
sudo dnf install libXinerama-devel libXcursor-devel mesa-libGLU-devel pkgconf-pkg-config xorg-x11-server-Xorg libXrandr-devel
```

#### 💿 glew dependencies
```console
sudo dnf install libXmu-devel libXi-devel mesa-libGL-devel
```

#### 💿 ALSA dependencies
```console
sudo dnf install autoconf libtool
```

#### 💿 SFML dependencies
```console
sudo dnf install systemd-devel libX11-devel libXrandr-devel libXcursor-devel mesa-libGL-devel
```

#### 💿 Visual Studio and WSL development dependencies
```console
sudo dnf install rsync procps-ng zip unzip ninja-build gdb make
```

### 🕹️ Installing vcpkg on Fedora 40
- Clone [this](https://github.com/microsoft/vcpkg.git) repository wherever you would like to have vcpkg installed
- Open a terminal
  - `cd` into the vcpkg folder
  - run the bootstrap script (`./bootstrap-vcpkg.sh -disableMetrics`)
- Create a script with the following content to set the required environment variables (`sudo nano /etc/profile.d/vcpkg_env.sh`)
```bash
export VCPKG_ROOT=/your/vcpkg/path/
export PATH=$PATH:$VCPKG_ROOT
```
- Refresh your terminal

# ℹ️ Project info
- Deadline: 17th of May
- Project coordinator / Professor: [Sebastian Ichim](https://github.com/ichimv)