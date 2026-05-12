# Hierarchical Animation

A modular **C++ DirectX 11 animation system** demonstrating both hierarchical rigid-body animation and skeletal joint-based animation. The project explores transform hierarchies, scene graph propagation, forward kinematics, animation state systems, and lightweight animation blending in real time.

The project contains two main demonstrations:
- A **plane** built from animated rigid components using hierarchical transforms.
- A **robot** driven by a joint-based skeletal hierarchy with animation state switching and blending.

---

## 🎥 Preview

| Plane | Robot |
|-------|--------|
| ![Plane](https://github.com/MoAgilah/Hierarchical-Animation/blob/master/Preview/Gif/Plane.gif?raw=true) | ![Robot](https://github.com/MoAgilah/Hierarchical-Animation/blob/master/Preview/Gif/Robot.gif?raw=true) |

---

## ⚙️ Key Features

- Hierarchical transformation system using local and world matrices
- Parent–child animation for rigid-body objects
- Unskinned skeletal animation using joint-driven rigid parts
- Forward kinematics across the bone hierarchy
- Animation state switching and lightweight blending
- Procedural component animation (e.g. propeller rotation)
- Socket-based firing from animated gun barrels
- Scene graph propagation and deterministic transform updates
- Multiple camera modes for scene inspection
- Separation between animation systems and runtime scaffolding

---

## ✈️ Plane — Hierarchical Animation

The plane demonstrates hierarchical rigid-body animation through modular parent–child relationships between components such as the fuselage, propeller, turret, and gun barrel.

### Highlights

- Continuous procedural propeller animation
- Turret and gun rotation relative to the plane body
- Projectile spawning from the animated gun barrel socket
- Deterministic transform propagation and gameplay updates

---

## 🤖 Robot — Skeletal Animation

The robot demonstrates an unskinned skeletal animation system where rigid body parts follow a joint hierarchy using forward kinematics.

### Highlights

- Joint-driven modular body parts
- Idle, attack, and death animation states
- Lightweight animation blending and pose interpolation
- Frame-by-frame animation inspection
- Separation between animation data, pose evaluation, and rendering

---

## 🧱 Architecture

The project is structured around reusable animation systems rather than hard-coded rendering behaviour. Local transforms are evaluated first and then propagated through the hierarchy to produce final world transforms.

Gameplay systems such as firing use sockets and component transforms so interactions remain attached to animated parts.

```text
Hierarchy/     → Animation, skeletal logic, hierarchical model code
Shared/        → Provided runtime framework for rendering and input
*.sln          → Visual Studio solution and project files
```

The `Shared/` framework was provided as university scaffolding for rendering, input, and visualisation. The animation systems inside `Hierarchy/` were independently implemented.

---

## 🛠 Technologies

- C++
- DirectX 11
- Visual Studio
- Windows SDK
- Real-time animation systems
- Forward kinematics

---

## 🚀 Build & Run

### Requirements

- Visual Studio 2019 or 2022
- Windows 10/11 SDK
- DirectX 11-compatible environment

### Steps

1. Clone the repository.
2. Open the Visual Studio solution file.
3. Set the configuration to **x64 → Debug** or **Release**.
4. Build and run the project.

A standalone executable is also available in the repository release/download section.

---

## 🔭 Future Work

- GPU skinning with vertex shader bone blending
- Inverse kinematics for procedural pose control
- Improved animation blending and layered animation masks
- Advanced debug visualisation tools
- Integration with gameplay and collision systems
- DirectX 12 rendering backend exploration

---

## 🙏 Acknowledgements

- The `Shared/` runtime framework was provided as university course scaffolding.
- Hierarchical and skeletal animation systems were independently implemented by the author.
- DirectX documentation and course materials were referenced during development.

---

## 👤 Author

**Mohamed Agilah**  
🎓 Games Programmer & AI Developer  
🌐 https://moagilah.com/  
📧 agilahmohamed@gmail.com
