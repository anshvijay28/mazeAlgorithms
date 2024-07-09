# mazeAlgorithms
Using a RayLib C++ wrapper to visualize maze generation/maze solving algorithms.

## Local Development
If you want to clone this repo and start developing on your local machine then follow these steps:

1. Clone the C++ RayLib starter kit [here](https://github.com/CapsCollective/raylib-cpp-starter/tree/main).

```
git clone https://github.com/CapsCollective/raylib-cpp-starter.git
```

2. Clone this repo
```
git clone https://github.com/anshvijay28/mazeAlgorithms.git
```
3. Replace the `/src` directory in the starter kit with the `/src` directory from this project. 

#### macOS & Linux
```
$ rm -rf raylib-cpp-starter/src
$ mv mazeAlgorithms/src raylib-cpp-starter
```

#### Windows
```
> rmdir /s /q raylib-cpp-starter\src
> move mazeAlgorithms\src raylib-cpp-starter
```
4. In the root directory of `raylib-cpp-starter` run:
#### macOS & Linux
```
$ make setup
$ make
```
#### Windows
```
> mingw32-make setup
> mingw32-make
```
5. Modify anything and everything in `/src`!
