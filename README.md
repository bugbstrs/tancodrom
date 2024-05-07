# ?
`Tancodrom` is a team project currently in development for the SMMG3D 2023-2024 (**S**isteme **M**oderne de **M**odelare **G**rafica **3D**) course held at Transilvania University of Brasov's [Faculty of Mathematics and Computer Science](https://mateinfo.unitbv.ro) (study programme: Computer Science).

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

# 🔨 Build requirements
- `MSVC` / Visual Studio (this project uses the 2023 latest draft)
- `vcpkg` + the following packages:
  - `glfw3` • (`vcpkg install glfw3`)
  - `glm` • (`vcpkg install glm`)
  - `glew` • (`vcpkg install glew`)

## 🕹️ Installing `vcpkg`

- Clone [this](https://github.com/microsoft/vcpkg.git) repository wherever you would like to have vcpkg installed
- Open a terminal
  - `cd` into the vcpkg folder
  - run the bootstrap script (`bootstrap-vcpkg.bat`)
- Set the following environment variables
  - `VCPKG_ROOT` to wherever your vcpkg folder is located
  - Change `Path` and add `%VCPKG_ROOT%` to it
- Close all of your Visual Studio instances and also any opened terminals
- Open a terminal and run `vcpkg integrate install`

# ℹ️ Project info
- Deadline: 17th of May
- Project coordinator / Professor: [Sebastian Ichim](https://github.com/ichimv)