# Hiearchal Animation
## Project Description
![map](https://github.com/user-attachments/assets/9a016f92-9b14-4e58-a5a7-be115fba2fd3)


The project was originally built utilising Directx11  utlising the legacy [DirectX SDK](https://www.microsoft.com/en-gb/download/details.aspx?id=6812) it is has now suggested to utilise the modern Windows SDK instead. Instead of implementing the newer SDK for DirectX11 I have decided to learn DirectX12 to update this project. There are more details contained within the respository archiving my learning of this updated SDK [found here](https://github.com/MoAgilah/Introduction-to-Game-Programming-with-DirectX12).\
The project itself demonstrates the following 3D rendering techniques:
- Height map rendering
- An model animation made up of multiple smaller components.
- Relative velocity application for firing a bullet.
- Skeletal animation of Robot model.
- Rudimentary collision checks to allow the plane to shoot the robot.

On the update of the project to a DirectX12 project, I intend to add the following:
- [ ] Shader implementation to colour the scene.
- [ ] Shadow modelling.
- [ ] Real time collision checks.
## Project Controls

For all Camera states:
| Key    | Response |
| -------- | ------- |
| w  | toggle wireframe    |
| c | change camera state     |

The following camera states are available:
- Map
- Plane
- Gun
- Robot

Whilst in CameraState::Map:
| Key    | Response |
| -------- | ------- |
| q  | zoom camera in    |
| a | zoom camera out     |

Whilst in CameraState::Plane || CameraState::Gun:
| Key    | Response |
| -------- | ------- |
| q  | pitch upwards    |
| a | pitch downwards     |
| p  | yaw and roll left    |
| o | yaw and roll right     |
| l  | loop de loop    |
| r | barrell roll right     |
| space bar | fire gun     |

Whilst in CameraState::Robot:
| Key    | Response |
| -------- | ------- |
| 1  | change to the idle animation    |
| 2 | change to the attack animation     |
| 3  | change to the dieing animation    |
| f | held down to iterate animation frame by frame     |


