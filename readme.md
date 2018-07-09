c_linux
=======

1. How to create a window using xlib.
2. How to close window with pressing escape key.
3. How to draw a line.
4. How to disable window from being resized.
5. How to move window center of screen.
6. How to draw text with xlib.
7. How to capture mouse left click.
8. How can I change window background color.
9. Mouse left button press and release.
10. Draw red line.
11. Draw pixel center of window.
12. Draw circle center of window.
13. Draw rectangle center of window.
14. Draw filled rectangle.
15. Draw pixel at mouse left button pressed location.
16. Draw pixel at mouse moved location.
17. Change window background on cursor enter / leave.
18. What buffer ?
19. How to draw an image with xlib ?
20. How to use OpenGL with Xlib.
21. How not to block while loop with xlib.
22. How to use socket without it blocking the while loop.
23. Some random half a pyramid.
24. Some random pyramid.
25. Random xlib grid.
26. Some button.
27. How to use glad with xlib.
28. How to draw a triangle using OpenGL.
29. Draw text using xlib.
30. Pipe and fork.
31. Draw rect using Opengl.
32. Use texture on triangle.
33. Rotate object in OpenGL.

TODO
====

1. Find cursor position, and draw a box at its location.
2. Draw a circle.
3. Create a child window.
4. Draw a rectangle.
5. Draw a triangle using OpenGL.
6. Create a button.
7. Create a table.
8. Create a grid system.
9. Render an image.
10. Play video.
11. Play music / sounds.
12. Make client / server something.
13. Create updater.
14. Create alert window. [YES] / [NO]
15. Create message window. [OK]
16. Change border color on pointer enter / leave.
17. Create / use some kind of canvas.
18. Distance between two points.
19. Walking animation.
20. Running animation.
21. Loading animation.
22. Obtain item by walkin over it.
23. Execute action by being near it.
24. Pick up item animation.
25. Character model.
26. Car Model.
27. House Model.
28. Create 100 random lines.
29. What are particles.
30. Create Ball With OpenGL.
31. Jumping animation.
32. Convert pointer position to 3D World Coordinates.
33. Download and image if does not exist.
34. C Web Server.
35. How to create ur own browser.
36. What is motion.
37. What is linked list.


MORE
====

Beej's Guide to Network Programming
-----------------------------------

http://beej.us/guide/bgnet/

Learn OpenGL Resources
-------------------------

https://learnopengl.com/

OpenGL Programming Guide
-------------------------

http://www.glprogramming.com/red/

Linear Math Library
-------------------

https://github.com/datenwolf/linmath.h

GL/GLES/EGL/GLX/WGL Loader-Generator 
-------------------------------------

https://github.com/Dav1dde/glad

Single-file public domain libraries
-------------------------------------

https://github.com/nothings/stb

Coding Math
-----------

https://www.youtube.com/watch?v=zm9bqSSiIdo&list=PL7wAPgl1JVvUEb0dIygHzO4698tmcwLk9

OpenGL Text Rendering
---------------------

https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01

OpenGL Tutorials
-----------------

https://gitlab.com/wikibooks-opengl/modern-tutorials

Mouse Picking with Ray Casting
--------------------------------------

http://antongerdelan.net/opengl/raycasting.html

socket
=======

```c
struct addrinfo {
  int ai_flags; /* AI_PASSIVE, AI_CANONNAME */
  int ai_family; /* AF_INET, AF_INET6, AF_UNSPEC */
  int ai_socktype; /* SOCK_STREAM, SOCK_DGRAM */
  int ai_protocol; /* use 0 for "any" */
  int size_t ai_addrlen; /* size of ai_addr in bytes */
  struct sockaddr *ai_addr; /* struct sockaddr _in or _in6 */
  char *ai_canonname; /* full canonical hostname */
  struct addrinfo *ai_next; /* linked list, next node */
};

struct sockaddr {
  unsigned short sa_family; /* address family, AF_... */
  char sa_data[14]; /* 14 bytes of protocol address */
};

struct sockaddr_in {
  short int sin_family; /* address family, AF_INET */
  unsigned short int sin_port; /* port number */
  struct in_addr sin_addr; /* internet address */
  unsigned char sin_zero[8]; /* same size as struct sockaddr */
};

struct in_addr {
  uint32_t s_addr; /* 32-bit int (4 bytes) */
};

struct sockaddr_in6 {
  u_int16_t sin6_family; /* address family, AF_INET6 */
  u_int16_t sin6_port; /* port number, network byte order */
  u_int32_t sin6_flowinfo; /* IPv6 flow information */
  struct in6_addr sin6_addr; /* IPv6 address */
  u_int32_t sin6_scope_id; /* scope id */
};

struct in6_addr { 
  unsigned char s6_addr[16]; /* IPv6 address */
};

struct sockaddr_storage {
  sa_family_t ss_family; /* address family */

  /* ignore rest ? */
};
```

MORE
------
```c

/* ip addresses, part deux */
struct sockaddr_in sa; /* IPv4 */
struct sockaddr_in6 sa6; /* IPv6 */

inet_pton(AF_INET, "127.0.0.1", &(sa.sin_addr)); /* IPv4 */
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); /* IPv6 */
/* PS: old ways (inet_addr(), inet_aton()) */
```

MORE
----

- IPv4
```c
char ip4[INET_ADDRSTRLEN]; /* space to hold the IPv4 str */
struct sockaddr_in sa; /* pretend this is loaded with somethign */

inet_ntop(AF_INET, &(sa.sin_addr), ip4, INSET_ADDRSTRLEN);

printf("The IPv4 address is: %s.\n", ip4);
```

- IPv6
```c
char ip6[INET6_ADDRSTRLEN]; /* space to hold the IPv6 str */
struct sockaddr_in6 sa6; /* pretend ... */

inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

printf("The IP6 address is: %s.\n", ip6);
```

MORE
------

```c
struct sockaddr_in sa;
struct sockaddr_in6 sa6;

sa.sin_addr.s_addr = INADDR_ANY; /* use IPv4 address */
sa6.sin6_addr = in6addr_any; /* use IPv6 address */

struct in6_addr ia6 = IN6ADDR_ANY_INIT;


- Instead of inet_aton() or inet_addr(), use inet_pton().
- Instead of inet_ntoa(), use inet_ntop().
- Instead of gethostbyname(), use the superior getaddrinfo().
- Instead of gethostbyaddr(), use the superior getnameinfo() (although gethostbyaddr() can still work with IPv6).
```
