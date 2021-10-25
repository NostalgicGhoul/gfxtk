# gfxtk

## What is it?

gfxtk is a modern, cross-platform rendering library.

Supported graphics backends:

- Vulkan

Planned graphics backends (in order):

- Metal
- DX12
- GNM (end goal, will require Sony approval to get access)
- WebGPU

gfxtk will NOT support the following:

- OpenGL
- OpenGL ES
- WebGL

Much of the gfxtk API is inspired by Vulkan, WebGPU, and Metal (in that order). There are aspects of gfxtk that will 
look almost identical to each of those APIs. As an example, the `BindGroup` ideas were nearly ripped straight from the 
WebGPU spec as I liked how WebGPU handled that aspect of the API and agreed with much of the reasoning behind its 
implementation.

## Building

### Linux

Install the following required packages:

```shell
sudo apt-get install git cmake build-essential libx11-xcb-dev \
    libxkbcommon-dev libwayland-dev libxrandr-dev
```

## FAQ

### Why not *GL?

gfxtk will never support OpenGL, OpenGL ES, or WebGL. This is partly sad as it means
gfxtk will never run on PinePhone (without major sacrifices) and won't run on the 
Librem 5 until the open source driver is updated to support Vulkan (the proprietary 
driver already supports Vulkan). 

The reason for these APIs not getting support is due to two facts: 

1. Vulkan is the replacement of OpenGL _for me, the author_. 
2. While modern versions
   of OpenGL and OpenGL ES _do_ support most of what gfxtk does, systems that 
   support these versions _also_ support Vulkan. Making the effort to implement 
   these APIs wasted.
3. OpenGL ES 2.0 and OpenGL 2.1 are ancient. These are the APIs that are supported
   on machines with no support for Vulkan. As an example of how ancient these APIs 
   are, OpenGL ES 2.0 was released in July of 2003, making it 18 years old at the 
   time of writing this. These ancient APIs lack _many_ of the modern constructs and 
   techniques used in gfxtk and the modern APIs it supports.
