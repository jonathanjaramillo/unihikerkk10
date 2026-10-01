# unihikerk10

Workspace for firmware projects on the DFRobot UNIHIKER K10 (ESP32-S3). Each
project is its own git repo, registered here as a submodule; the shared
reference material lives once at this level.

## Shared reference material (read these before guessing at hardware)

- `hardware/UnihikerK10Schematic.pdf` — the K10 schematic.
- `unihiker-docs/` — vendor hardware/API docs (submodule, upstream: UNIHIKER/unihiker-docs).
  K10 docs are under `unihiker-docs/docs/K10/`.
- `framework-arduinounihiker/` — vendor Arduino framework source (submodule,
  upstream: DFRobot/framework-arduinounihiker). Reference only: builds get the
  framework from PlatformIO (`~/.platformio/packages/`), not from this folder.
  Do not edit.

## Shared drivers

`libs/` holds drivers for the K10's external devices, shared across projects. They are
plain files tracked in this repo (not submodules). Each is a PlatformIO library with its
own `library.json`, README and `examples/`.

- `libs/k10-gamecontroller/` — I2C game controller (joystick + A/B/C/D/OK buttons).

A project uses them with `lib_extra_dirs = ../libs` in its `platformio.ini`. Only the
libraries a project actually includes are linked. Put new reusable device drivers here;
keep project-specific code (algorithms, app logic) in the project. Note that a project
cloned on its own, without this repo, won't find these libraries.

`esp-doom` and `esp32-SfM` predate `libs/` and still carry their own copies of the game
controller driver.

## Projects

- `esp-doom/` — Doom port for the K10.
- `esp32-SfM/` — structure-from-motion / visual odometry experiments.

Each project has its own README and git history. Commit inside the project, then
bump the submodule pointer here.

## Adding a project

1. Create a folder here, `git init`, and build with PlatformIO
   (`platform = https://github.com/DFRobot/platform-unihiker.git`, `board = unihiker_k10`,
   `lib_extra_dirs = ../libs`).
2. Don't copy the framework, docs, schematic or shared drivers into the project; link to
   `../hardware`, `../unihiker-docs` and `../libs` from its README/notes if needed.
3. Push the project to its own remote, then `git submodule add <url> <folder>` here.

## Cloning

`git clone --recursive <this repo>` (or `git submodule update --init` afterwards).
The `unihiker-docs` and `framework-arduinounihiker` submodules are large (~650 MB each);
add `--depth 1` / `--shallow-submodules` if you only need the latest files.
