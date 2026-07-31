# Hierarchical Animation

A modern C++ graphics project exploring hierarchical transformations, keyframe animation and articulated model construction through a reusable parent–child scene hierarchy.

Hierarchical Animation investigates the mathematical and software engineering principles behind articulated animation by combining recursive transformation propagation, imported animation data and procedural component movement within a real-time DirectX application. Rather than focusing solely on rendering, the project explores how hierarchical structures, animation systems and scene management combine to produce complex animated behaviour.

The project focuses on graphics programming, animation systems and modular software design, demonstrating how articulated models and keyframe animation can be organised into clear, maintainable components while applying concepts commonly found in game engines and real-time visualisation software.

---

## The Engineering Problem

Animating complex objects involves significantly more than moving individual meshes. Articulated models require parent–child relationships so that movement applied to one component is inherited naturally by those attached beneath it, while still allowing every component to maintain its own independent local transformations.

Hierarchical Animation explores this challenge by implementing a reusable transformation hierarchy capable of supporting both procedurally animated mechanical objects and imported keyframe animation. The project investigates how recursive transformation propagation, animation interpolation and scene organisation can be combined within a maintainable C++ application while demonstrating the core principles underpinning modern animation systems.

---

## Simulation Architecture

<p align="center">
  <img width="700" alt="HierarchalAnimation" src="https://github.com/user-attachments/assets/8f84686c-cee2-47e4-9614-4382b76cac45" />
</p>

The application is organised into modular systems responsible for hierarchy construction, animation processing, scene management and rendering. Each subsystem performs a focused responsibility while contributing to the complete animation pipeline, allowing transformation management, animation evaluation and rendering to remain clearly separated.

---

## Engineering Goals

The project was designed to explore:

- Hierarchical transformations
- Parent–child scene graphs
- Keyframe animation
- Animation interpolation
- Animation blending
- Recursive matrix propagation
- Data-driven animation loading
- Real-time graphics programming
- Modular software organisation

Although demonstrated through an articulated aircraft and animated robot, the engineering concepts explored are applicable to graphics engines, simulation software and interactive real-time applications.

---

## Key Features

- Parent–child transformation hierarchy
- Recursive world matrix calculation
- Procedural aircraft animation
- Keyframe robot animation
- Animation blending between clips
- XML-based animation loading
- Multiple interactive camera modes
- Height-map terrain rendering
- Object-pooled projectile system
- Real-time DirectX rendering

---

## Technologies & Engineering Practices

### Development

- C++20
- DirectX 11
- DirectXMath
- HLSL
- TinyXML2
- Visual Studio 2022
- Git
- Git Submodules

### Engineering Practices

- Hierarchical Scene Graphs
- Keyframe Animation
- Animation Blending
- Recursive Algorithms
- Object-Oriented Design
- Separation of Concerns
- Data-Driven Design
- Real-Time Rendering
- Matrix Mathematics
- Modular Software Design

---

## Architecture Highlights

- Recursive parent–child transformation propagation
- Local and world transformation separation
- Shared hierarchy supporting procedural and keyframe animation
- Animation parsing separated from playback
- Pose evaluation independent of rendering
- Named component lookup for articulated models
- Reusable animation controller supporting multiple clips
- Gameplay systems driven by hierarchy world transforms

---

## Engineering Outcome

Hierarchical Animation demonstrates how the mathematical principles behind articulated animation can be translated into a structured C++ graphics application. By combining recursive transformation hierarchies, imported keyframe animation and procedural component movement, the project explores scene graphs, animation systems and graphics programming while maintaining a modular software architecture.

Rather than functioning as a complete game engine, the project serves as a practical investigation into hierarchical animation, demonstrating experience with transformation mathematics, animation pipelines and the engineering considerations involved in building maintainable real-time graphics systems.

---
