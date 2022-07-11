# Computer Graphics Project - 2021/2022

## Minecraft Clone

### Team members
Name and Surname | Personal Code |            Email            | Github Username
:---: |:-------------:|:---------------------------:| :---:
Daniele Ferrazzo |       x       |              x              | x
Lorenzo Fratus |       x       |              x              |        x
Luigi Fusco |   10601210    | luigi1.fusco@mail.polimi.it |        @luigifusco  

### Description
The project consists in an implementation of a voxel based game taking inspiration from the popular *Minecraft* franchise.
The project is developed in C++ using the Vulkan framework to handle graphics.

### Features
#### Randomly generated infinite terrain
The world is divided into chunks of size 64x64x256. Perlin noise is used to generate a height map, describing the level
of dirt and stone blocks. Trees and grass are then randomly generated. The water level is set, meaning that all blocks
generated below a certain threshold will be covered by water. New chunks are generated as the player moves through the world, and are kept in RAM.

#### View range
Only a small amount of all generated chunks are visible at a given time, based off their distance from the player.
As the player moves, chunks are queried for vertex buffer data, and the global vertex and index buffers are updated
accordingly. In order to support vertical synchronizations two buffers are alternated to avoid race conditions.

#### Support for transparency 
The surface of water is semitransparent. In order to achieve this effects and avoid problems with z-buffering,
solid blocks and water are rendered using two separate passes.

#### Block face culling
The procedure generating graphics data from chunks takes into account the visibility of block faces, generating only
faces which are at contact with a transparent block. The check is valid even across chunks. If a neighboring chunk is not yet generated
the corresponding faces are not generated. The generation of a new chunk triggers the update of neighboring chunks in order to avoid artifacts.

#### Working basic physics (collisions, gravity, jumping)
Collisions are detected using the AABB method. On collision with a block, the player is moved by the shortest distance
which would pop them out of the block. As a failsafe mechanism, if the operation fails a large number of times
the player is teleported up into the sky.

#### World editing
Currently only block deletion is supported. The block the player is pointing at is found using a ray casting algorithm,
which searches forward block by block until a breakable block is found. Breaking a block triggers an update of the chunk,
of its graphics data and the one of neighboring chunks in the case of a border block.

#### Custom vertex and fragment shaders
Blocks are drawn using textures. The BRDF model combines an Oren Nayar diffuse model with a Phong Specular model.
There are two global lights (the Sun and the Moon), which continuously rotate, giving the effect of a day/night cycle.
The sky color is simulated by changing the clear color at every new frame. At night, a spotlight is added, with position
corresponding to the head of the player and direction to their line of sight.

