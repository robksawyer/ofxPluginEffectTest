# Open Frameworks Plugin FFGL Effect Test for OSX and Xcode

## Getting started

1. Download the dependencies listed below. Also verify that you are running a similar setup to the one listed in My System below.
2. Clone this repo using `git clone`.
3. Move the latest version of [robksawyer/ofFFGLPlugin/addons/ofxFFGLPlugin](https://github.com/robksawyer/ofFFGLPlugin) to `openframeworks_v0.X.X/addons/`
4. Move `ofxPluginEffectTest080` to `openframeworks_v0.X.X/apps/myApps/`.
5. Start hacking!

----------------------------------------------------------------------------------


## Getting started with Open Frameworks Project Generator

### Part 1
1. Download the dependencies listed below. Also verify that you are running a similar setup to the one listed in My System below.
2. Move the latest version of [robksawyer/ofFFGLPlugin/addons/ofxFFGLPlugin](https://github.com/robksawyer/ofFFGLPlugin) to `openframeworks_v0.X.X/addons/`
3. Open `Project Generator` and name your sketch. The project will be created in your openframeworks folder under `apps/myApps`.
4. Click "Addons:" and mark `ofxFFGLPlugin`, then click << Back
5. Now click Generate Project and close the app
6. Navigate to apps/myApps/YourProject/ and open YourProject.xcodeproj. Build and compile it to make sure it actualyl compiles. If it doesn't, you're going to have some issues later. 
> You'll notice that by default it creates apps, but we need a bundle. So now is when the customizing starts. 

7. Match the following project settings:
  > Project build settings
  - Architectures -> 32 bit intel (64-bit and Universal not currently supported.)
  - Wrapper extension -> bundle
  - Mach-o type -> Bundle
  - Warnings, deprecated functions -> No (There are lots of them!)

  [![Build Settings](http://s22.postimg.org/wm4f4vbd9/Screen_Shot_2015_04_11_at_6_39_54_PM.jpg)](http://s22.postimg.org/motebt3rl/Screen_Shot_2015_04_11_at_6_39_54_PM.png)
  
  > Project Build Phases, Run Script
  - change `@executable_path` with `@loader_path`
  - change “.app” extensions to “.bundle” where present
  - add `cp -rf "$TARGET_BUILD_DIR/$PRODUCT_NAME.bundle" /Applications/Resolume\ Arena\ 4.X.X/plugins/vfx` (or change path according to your Host App location and name)

  [![Run script](http://s13.postimg.org/cy04avio3/Screen_Shot_2015_04_11_at_6_22_21_PM.jpg)](http://s13.postimg.org/3q7vu6blz/Screen_Shot_2015_04_11_at_6_22_21_PM.png)

8. You should NOT have to touch the default settings, but confirm the following:
  > OpenFrameworks build settings:
  - Architectures -> 32 bit intel
  - Warnings, deprecated functions -> No (There are lots of them!)

9. Select the openFrameworksLib project in the openframeworks folder of the Project navigator. Ensure OpenFrameworks is the active scheme next to the Build (play) button in Xcode. Build OpenFrameworks, it should compile fine with no issues.

### Part 2

1. Select YourProject in the Project navigator and ensure YourProject Debug or Release is set as the active scheme next to the Build (play) button in Xcode.
2. Confirm `ofTex->texData.glType = GL_RGBA;` in `addons/ofxFFGLPlugin/src/ofxFFGLPlugin.cpp` is commented out.
3. Confirm `default: ;` is in the `addons/ofxFFGLPlugin/src/ofxFFGLPlugin.cpp` switch/case. This suppresses two warnings.
4. Confirm that the following is at the beginning of `addons/ofxFFGLPlugin/libs/FFGL/FFGL.h`:
``` 
#ifdef __APPLE__
#include <TargetConditionals.h>
#endif
at the beginning of FFGL.h

inf FFGLExtensions.h comment out
typedef unsigned int GLhandleARB;
and replace with
#if defined(__APPLE__)
typedef void *GLhandleARB;
#else
typedef unsigned int GLhandleARB;
#endif
then change the definition of GETProcAddress to
void *FFGLExtensions::GetProcAddress(char const *name)
(also in header file of course)

inf FFGLShader.h change as follows
#ifdef __APPLE__
    void * m_glProgram;
    void * m_glVertexShader;
    void * m_glFragmentShader;
    GLuint m_linkStatus;
#else
    GLenum m_glProgram;
    GLenum m_glVertexShader;
    GLenum m_glFragmentShader;
    GLuint m_linkStatus;
#endif
```

5. Confirm the following is between `ofSetupOpenGL` and `ofRunApp` in `addons/ofxFFGLPlugin/src/ofxFFGLWindow.cpp`.

```
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    /* Problem: glewInit failed, something is seriously wrong. */
    ofLogError("ofAppRunner") << "couldn't init GLEW: " << glewGetErrorString(err);
  }

  glDisable( GL_DEPTH_TEST );
```

6. Confirm that the following methods are in `addons/ofxFFGLPlugin/src/ofxFFGLWindow.cpp`.

```
int ofFFGLWindow::getHeight()
{
    return (int)windowSize.y;
}

int ofFFGLWindow::getWidth()
{
    return (int)windowSize.x;
}
```

7. Ensure that the following declarations are in the header of `addons/ofxFFGLPlugin/src/ofxFFGLWindow.h`.

```
int     getHeight();
int     getWidth();
```

8. The project should now build with no issues!

> After you build, the YourProject.bundle should be copied to Arena vfx plugins dir. You can now launch Arena. The plugin should be visible in the list (Name corresponds to the name listed in `src/main.cpp`. Select it and check that sample parameters are present and info is correct. Try to apply it to the webcam, it should work (try changing the repetitions parameter). If the plugin does not show up, copy it from bin directory of your project and check that you added the copy command (`cp -rf "$TARGET_BUILD_DIR/$PRODUCT_NAME.bundle" /Applications/Resolume\ Arena\ 4.2.0/plugins/vfx`) in the Run Script area of Build Phases.  

----------------------------------------------------------------------------------

##Dependencies

- [Open Frameworks (~v0.8.4)](http://openframeworks.cc/download/) - I've only test this with the stable build of v0.8.4.
- [ofxFFGLplugin](https://code.google.com/p/ofxffglplugin/) - There are some issues with the latest version that need to be patched. I'd advise using the updated version at [robksawyer/ofFFGLPlugin](https://github.com/robksawyer/ofFFGLPlugin).


##Tips

For FFGL development, it's important to have some understanding of GLSL shader language. A good book to get started with is [OpenGL Shading Language, Second Edition](http://wiki.labomedia.org/images/1/10/Orange_Book_-_OpenGL_Shading_Language_2nd_Edition.pdf), but there are several other sources on the Internet. The [OpenGL SuperBible](http://www.math.zju.edu.cn/ligangliu/forstudents/C++/OpenGL%20Super%20Bible.pdf) is helpful for understanding the whole OpenGL context.


##Resources

- Open Frameworks Documentation <http://openframeworks.cc/documentation/>
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