# Hierarchical Animation

A C++ project implementing hierarchical (skeletal) animation, model component assembly, and basic interaction in a DirectX environment.  
Originally built with **DirectX 11** (legacy SDK); later iterations aim to shift toward **DirectX 12 / modern Windows SDK**.

---

## 🎥 Preview

| **Plane** | **Robot** |
|------------|------------|
| ![Plane](https://github.com/MoAgilah/Hierarchical-Animation/blob/master/Preview/Gif/Plane.gif?raw=true) | ![Robot](https://github.com/MoAgilah/Hierarchical-Animation/blob/master/Preview/Gif/Robot.gif?raw=true) |


*(Visualization of skeletal model animations, hierarchical object composition, and interaction)*

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
