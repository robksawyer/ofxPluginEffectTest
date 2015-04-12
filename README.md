# Open Frameworks Plugin FFGL Effect Test for OSX and Xcode

## Getting started

1. Download the dependencies listed below.
2. Clone this repo using `git clone`.
3. Move the latest version of [robksawyer/ofFFGLPlugin/addons/ofxFFGLPlugin](https://github.com/robksawyer/ofFFGLPlugin) to `openframeworks_v0.8.4/addons/`
4. Move `ofxPluginEffectTest080` to `openframeworks_v0.X.X/apps/myApps/`.
5. Start hacking!


##Dependencies

- [Open Frameworks (~v0.8.4)](http://openframeworks.cc/download/) - I've only test this with the stable build of v0.8.4.
- [ofxFFGLplugin](https://code.google.com/p/ofxffglplugin/) - There are some issues with the latest version that need to be patched. I'd advise using the updated version at [robksawyer/ofFFGLPlugin](https://github.com/robksawyer/ofFFGLPlugin).


##Tips

For FFGL development, it's important to have some understanding of GLSL shader language. A good book to get started with is [OpenGL Shading Language, Second Edition](http://wiki.labomedia.org/images/1/10/Orange_Book_-_OpenGL_Shading_Language_2nd_Edition.pdf), but there are several other sources on the Internet. The [OpenGL SuperBible](http://www.math.zju.edu.cn/ligangliu/forstudents/C++/OpenGL%20Super%20Bible.pdf) is helpful for understanding the whole OpenGL context.



##Resources


- Forum post [ofxFFGL with Xcode5 and OF080](http://forum.openframeworks.cc/t/ofxffgl-with-xcode5-and-of080/14031/28) on <forum.openframeworks.cc>. - This is basically where most of the project came from. Thanks should go to davidemania.
- [FFGL SDK](http://freeframe.sourceforge.net/) - The SDK includes 4 demo plugins, but don't expect to be able to compile them. I didn't have any luck.
- The [Resolume forum](http://resolume.com/forum/) has a pretty good list of 3rd-party FFGL plugins and some links to GLSL shaders.
- [Matias Wilkman](http://matiaswilkman.blogspot.co.at/search/label/ffgl) has some nice examples at [assembla.com](https://www.assembla.com/code/ffgl/subversion/nodes/14/trunk/Source/FFGLPlugins).
- [Mastering openFrameworks: Creative Coding Demystified](http://www.amazon.com/Mastering-openFrameworks-Creative-Coding-Demystified/dp/1849518041)

##My System

All of the testing that I've completed is done on a 2014 Macbook Pro Retina running the latest version of Mavericks. I'm also using Xcode 6.3. As a host I'm testing the plugins with [Resolume Arena 4.2.0](http://resolume.com/blog/11850/resolume-4-2-released-smoother-and-faster).


## Revisions

### Version 1.0.1
- Decided that adding `FFGL` folder to `/Applications/Resolume X.X.X/plugins/vfx/` was not very good for deployment, so I added a new Copy Phase under Build Phases in Xcode and had it copy the data folder into the bundle's Resources folder. I then had to modify the path in `testApp.cpp` so it would link to the new data.

### Version 1.0
- This is the base version that was pulled from the work of davidemania over at the OpenFrameworks forum <http://forum.openframeworks.cc/t/ofxffgl-with-xcode5-and-of080/14031>. 