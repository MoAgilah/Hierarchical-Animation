# Hierarchical Animation

This project demonstrates two different animation systems commonly used in games — **hierarchical (rigid-body)** animation and **skeletal (joint-based)** animation — implemented from scratch in C++.  

It includes:
- A **plane** model built with hierarchical rigid parts and functional propeller/gun animations.
- A **robot** model using a joint-based skeleton (unskinned) with animation blending between different motion clips.
---
## 🎥 Preview

| **Plane** | **Robot** |
|------------|------------|
| ![Plane](https://github.com/MoAgilah/Hierarchical-Animation/blob/master/Preview/Gif/Plane.gif?raw=true) | ![Robot](https://github.com/MoAgilah/Hierarchical-Animation/blob/master/Preview/Gif/Robot.gif?raw=true) |


*(Visualization of skeletal model animations, hierarchical object composition, and interaction)*

---

## 🎮 Overview

The goal of this project is to explore how transform hierarchies and skeletal rigs can be used to animate objects and characters procedurally or via keyframed data.

**Key Features**
- Hierarchical transformation system (local/world matrices)
- Animation controllers and blending
- Forward kinematics (FK)
- Procedural rotation (e.g., spinning propeller)
- Socket-based firing from moving parts
- Scene-graph propagation of transforms

---

## ✈️ Plane — Hierarchical Rigid Animation & Firing System

The plane demonstrates **hierarchical animation**, where each component of the model is a rigid part connected through a **parent–child transform tree**.

### Features
- **Modular construction:** fuselage (root), propeller, turret, and gun barrel linked hierarchically.
- **Procedural animation:** propeller spins continuously; turret and gun rotate relative to the fuselage.
- **Barrel-accurate firing:** bullets spawn from the **gun barrel’s world transform**, ensuring projectiles always fire directly from the barrel tip regardless of rotation or movement.
- **Scene-graph update:** transforms are propagated down the hierarchy each frame.

### Technical Notes
- Clean separation between **local** and **world** transformations.
- Use of **mount points/sockets** for gameplay elements (bullets, VFX, sound).
- Deterministic update order: evaluate → propagate → spawn → render.

### Learned Concepts
- TRS (Translate, Rotate, Scale) matrix composition.
- Parenting and world-space transform propagation.
- Attaching gameplay logic to animated components.

---

## 🤖 Robot — Skeletal (Unskinned) Animation & Blending

The robot showcases a **skeletal animation system** without mesh skinning — each rigid body part follows its corresponding bone directly.  

This allows complex, multi-joint movement while keeping the model lightweight and modular.

### Features
- **Joint hierarchy:** bones drive rigid mesh parts through a forward-kinematic chain.
- **Clip player:** keyframed animations (e.g., idle, walk, gestures) with a lightweight player supporting looping and playback speed.
- **Animation blending:** smooth transitions between clips (e.g., idle ↔ walk), and support for partial-body overlays (upper-body gestures layered over locomotion).
- **Quaternion blending:** prevents rotational artifacts and maintains stable motion.

### Technical Notes
- Forward Kinematics (FK) evaluated per-frame across the bone graph.
- Animation layers and blend masks allow partial control of certain joints.
- Quaternion normalization and consistent TRS update order.
- Debug visualization for bone axes and named sockets.

### Learned Concepts
- Implementation of skeletal systems without vertex skinning.
- Pose interpolation and per-joint blending.
- Data separation between animation, rendering, and gameplay.

---

## 🧩 Technical Highlights

- **Socket-based gameplay:** Bullets, particles, and VFX read socket transforms directly from the animation system.
- **Scene graph abstraction:** Animation, rendering, and gameplay remain loosely coupled.
- **Stable transformations:** Consistent use of quaternions, normalized rotations, and proper FK propagation.
- **Debug tools:** On-screen bone/skeleton visualization for troubleshooting motion artifacts.

---

## ⚙️ Challenges & Solutions

| Challenge | Solution |
|------------|-----------|
| Preventing gimbal lock | Used quaternions for all rotation blending |
| Animation popping | Implemented short (0.2–0.3s) cross-fades between clips |
| Hierarchical drift | Added per-frame debug visualization of world matrices |
| Propeller rotation vs. turret rotation conflicts | Separated animation controllers and propagated transforms deterministically |

---

## 🧠 Key Takeaways

- A **hierarchical system** provides precision for rigid body components like vehicles or turrets.  
- A **skeletal system (unskinned)** supports character-like articulation without complex deformation math.  
- Both systems integrate cleanly with gameplay through **transform sockets** and **scene graphs**.

---
## 📦 Download & Run
You can download the latest standalone executable here:

👉 [Download Standalone Executable](https://github.com/MoAgilah/Hierarchical-Animation/raw/master/bin/HierarchyAnimation.zip)

1. **Extract** the `.zip` file to any folder.  
2. Open the extracted folder.  
3. Run the executable:
   - **Windows:** `HierarchyAnimation.exe`  

> 💡 If you see a Windows SmartScreen prompt, click **More info → Run anyway** (the app is safe but not code-signed).

---

## 📁 Project Structure

```
Hierarchy/     → Animation, skeletal logic, hierarchical model code
Shared/        → Provided runtime framework (rendering, window, camera, input)
*.sln          → Visual Studio solution and props files
```

> The **`Shared/`** directory was provided by the course lecturer to all students.  
> It acts as scaffolding to support rendering, input, and demo execution. No internal modifications are expected.

---

## ⚙️ Features & Techniques

- Hierarchical / skeletal animation (parent–child transforms)
- Component-based modeling (e.g. limbs, joints, robot parts)
- Animation states: idle, attack, death, etc.
- Animation blending and state switching
- Relative transformations (rotation, scaling)
- Basic interaction logic (e.g. weapon firing, movement)
- Height‑map rendering (scene terrain)
- Multiple camera modes (map, plane, gun, robot)

---

## 🎮 Controls & Camera Modes

### Common
| Key | Action |
|-----|--------|
| W | Toggle wireframe mode |
| C | Change camera state |

### Camera States

#### Map
| Key | Action |
|-----|--------|
| Q | Zoom in |
| A | Zoom out |

#### Plane / Gun
| Key | Action |
|-----|--------|
| Q | Pitch up |
| A | Pitch down |
| O / P | Yaw / roll changes |
| L | Loop de loop |
| R | Barrel roll |
| Space | Fire weapon |

#### Robot
| Key | Action |
|-----|--------|
| 1 | Idle animation |
| 2 | Attack animation |
| 3 | Death animation |
| F (hold) | Advance animation frame by frame |

---

## 🧱 Building & Running

**Requirements**
- Visual Studio 2019 or 2022  
- Windows 10/11 SDK  
- DirectX 11 support (or equivalent)

**Steps**
1. Open the solution file `.sln`.  
2. Set build configuration to **x64** and either **Debug** or **Release**.  
3. Build and run (press **F5** in Visual Studio).

---

## 🔄 Integration & Reuse

You can extract or reuse the animation logic (in `Hierarchy/`) independently of the demo framework.

- Include headers and source for skeletal / hierarchical systems.
- Adapt to your own math / engine types.
- Drive animation updates and blending from your engine or update loop.
- Use the demo scaffolding (from `Shared/`) if you want quick visual verification.

---

## 🔭 Future / Enhancement Ideas

- GPU skinning (vertex shader bone blending)
- Animation blending / interpolation (smooth transitions)
- Inverse kinematics (IK)
- Morph target / blend shape support
- Improved interaction and collision detection
- Port to DirectX 12 and modern rendering pipeline
- Shadows, lighting, and more advanced shading

---

## 🙏 Acknowledgements

- **`Shared/`** scaffolding and demo runtime are courtesy of the course lecturer, provided to all students.
- The hierarchical animation logic was independently developed in the `Hierarchy/` folder.
- Course materials, DirectX documentation, and reference resources guided the implementation.

## 👤 Author
**Mohamed Agilah**  
🎓 Games Programmer & AI Developer  
🌐 [Portfolio Website](https://moagilah.com/)  
📧 Contact: agilahmohamed@gmail.com  

> *Project archived for educational and portfolio purposes (October 2025).*
