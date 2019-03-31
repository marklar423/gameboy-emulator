# Gameboy Emulator

This is a Gameboy emulator written in C. 

Currently, GB games that use the [MBC1](http://gbdev.gg8.se/wiki/articles/Memory_Bank_Controllers) cart type are supported
(e.g. Dr Mario and Tetris). Support for more cart types and GBC games are planned for the future.

# Dependencies

* **[GLFW](https://www.glfw.org/)**: used to render the frames and receive input.
* **[inih](https://github.com/benhoyt/inih)**: used to parse config files
* **[libsoundio](http://libsound.io/)**: used to output audio

# Platforms

Currently the project only compiles on Windows, however support for other platforms can be easily added. 
The only Windows-specific functionality used are mutexes (to ensure the audio buffers are thread-safe) and the WinMain function.
