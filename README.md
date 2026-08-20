# cpppkg

**cppkg** is a CMake package manager which generate CMake files to import git
repositories via `FetchContent`

## Build

### Prerequisite

- [cmake](https://cmake.org)

### Compilation

```bash
cmake -B build && cmake --build build --parallel $(($(nproc) - 1))

# or

./build.sh
```

## Usage

### Configuration

Packages must be defined in 'cpppkg.json'; the configuration file must follow
the schema:

```json
{
    "{{declareName}}": {
        "user":       "{{gitUser}}",
        "repository": "{{gitRepository}}",
        "tag":        "{{gitTag}}"
    },
    [...]
}
```

### Integration

Update your CMakeLists file:

```cmake
include(${CMAKE_CURRENT_SOURCE_DIR}/.cpppkg/Declare.cmake)

# Build target
...

include(${CMAKE_CURRENT_SOURCE_DIR}/.cpppkg/Link.cmake)
```

### Commands

`installl`

Generate the CMake files for the packages defined in the configuration file;
package/s with already generated files will be skipped unless the '--force'
option is provided.

`list`

Print the list of installed packages.
