Cubesense
=========

Windows application for creating and visualizing 3D animations on an LED cube.

Developed by Ted Markson & Edmundas Balciunas

Development Notes:  

I decided that it became too difficult to continue developing it using Windows Forms application type. That was because of the way data had to be exchanged between UI and the rest of the program; also because Visual Studio was occasionally failing to parse through the code of application window, which required fixing broken parts by hand. In order to make somewhat convenient user interface I had to use third party libraries (such as ribbon bar and others from Codejock). Besides the UI there were issues with the rest of the program which I had found difficult to solve, such as occasional crashes, probably because of the bugs in parts of the program where data exchange between threads occur. Since I've started talking about it, it may be a good time to introduce you with the application structure (at least regarding threads).

First of all there is user interface which runs on separate thread, and that thread does nothing else but handles user interaction with program window.

Then there is another "main" thread. This thread has a loop which is timed as precisely as possible - it does a collection of things every 1/60 th of a second. In playback mode one of those things is increasing current frame pointer.

There is also a separate thread for OpenGL related tasks. Main thread sets an event every 1/60th of a second, which is registered by OpenGL thread. It indicates that it's time to redraw the scene. Good thing if Cubesense runs on fast enough PC and OpenGL does its job in time. In that case FPS will never be greater than 60 (which is enough, considering that this is how fast all eightCubed animations are supposed to be played). If not, well.. there is not much it can be done (except for new graphics engine, which i'll describe later), and at least OpenGL thread doesn't keep main thread waiting, and animation (even though it may not run that smooth) will appear to be played at correct speed.

One more separate thread is dedicated for communication with eightCubed hardware via USB. The infinite loop within that thread runs independently from other threads and is syncronized with eightCubed hardware. Everytime eightCubed requests for a new frame, it sends one. In theory it happens 60 times every second. But then there may be a slight difference between eightCubed crystal oscillator and Windows (which is not a real time operating system) timing mechanism. This is why USB communication is not driven synchronously with main thread's loop. It may happen that one of very many frames is displayed on eightCubed twice, or not all. But by many I mean very many. Which is absolutely unnoticeable and solves the problem of usb thread hanging and eightCubed not receiving new frame in time if main thread for some reason gets late by just a fraction of a second.

Scripts are also run on a separate thread, so everything else doesn't freeze, when the script is executing. I have plans for one more thread - it will be running specific type of scripts (not yet seen in Cubssense). Which is a good time introduce one of the new intended features to be implemented in the future. It's what we call real time scripts. These scripts will be written always in C. However it will be possible to compile them for both - PC and eightCubed. The advantage of these scripts is that they do not create pre-rendered animations which are the played-back on eightCubed. Rather they are executed in real time to create one frame every 1/60th of a second. Which enables use of random factor, microphone input, maybe even user input (to let users play games on eightCubed system), and so on.

Improvement on the graphics engine that I mentioned when I was talking about threads is rather straightforward. Until now I was using openGL to draw required number of spheres and to render a scene using standard 3D graphics techniques. It turned out that this quickly becomes rather resource consuming as the size of the cube grows. I've also noticed that, basically, all we need to draw every single time are the same spheres which all look like circles when projected onto a viewing plane. So I thought it could be done much faster if Cubesense code first calculates distances from viewing point to each of the spheres, then sorts them in ascending order and starts drawing circles (instead of spheres) with the furthest away LED (circle) being drawn first and the closest one - last. This way, issue of hiding LEDs which are further away would be solved automatically. And drawing circles rather than spheres should be a very good thing for performance.

After this brief introduction, going back to the issues with current version, I was thinking about switching to a WPF framework and doing everything in managed C#. As far as user interface is concerned there are components like AvalonEdit and AvalonDock available which would allow to achieve similar user experience. But then I am not a professional Windows application programmer (more a hardware programmer), and there may be better suited technologies for this job. What are your ideas on this? How are you thinking you'll be working on such software - continuing from where it is now or starting from scratch? In any case I could help you with that, as much as my time lets me (which is currently rather limited though). What features do you expect from final software?

Everything that I said related to eightCubed hardware could easily be adapted to different hardware (as long as it's powerful enough).
