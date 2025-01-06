# Final Project Proposal

## Group Members:

Qiuyu (Leo) Ye

# Intentions:

A statement of the problem you are solving and/or a high level description of the project.
I want to be able to render the mandelbrot set in an image file using multithreading and/or distributed computing

# Intended usage:

A description as to how the project will be used (describe the user interface).
Make run that takes parameters for how detailed the rendering is

# Technical Details:

A description of your technical design. This should include:

How you will be using the topics covered in class in the project.
Allocating memory
Working with files
I plan to have an image file and manipulate the data in the file to draw the rendered mandelbrot set
Processes (fork, exec etc.)
Forks to split the areas rendered for each process
Pipes (named and unnamed)
using other pipes to communicate data with other computers and split the work

How you are breaking down the project and who is responsible for which parts.
just me

What data structures you will be using and how.
Arrays to organize things

What algorithms and /or data structures you will be using, and how.
I plan to use a simple escape time algorithm for the mandelbrot set.

# Intended pacing:

A timeline with expected completion dates of parts of the project.

1/10 - Get a working version that can render the mandelbrot set into an image file without any optimizations
1/14 - Use forks to split the work and write into separate parts of the file
1/20 - try to implement distributed computing along with forks to speed up the work
1/21 (8AM) - everything commited including video
extra time: work on the colors in the picture and also take parameters for details / zoom
