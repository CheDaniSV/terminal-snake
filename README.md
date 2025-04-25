## 🐍 Snake game in terminal
<p>
	<!-- <img alt="Build and release workflow status" src="https://github.com/CheDaniSV/terminal-snake/actions/workflows/build-and-release.yml/badge.svg"> -->
	<!-- <img alt="Docker deploy workflow status" src="https://github.com/CheDaniSV/terminal-snake/actions/workflows/docker-deploy.yml/badge.svg"> -->
	<img alt="Commits since last release"  src="https://img.shields.io/github/commits-since/CheDaniSV/terminal-snake/latest">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/CheDaniSV/terminal-snake">
</p>

- ANSI terminals only
- Supports Windows & Linux
- Has 4 gamemodes:
	- CLASSIC - snake can't collide with the walls or itself 
	- CLASSIC_SPEEDUP - higher the score faster the game
	- NOWALLS - no collisions with the walls
	- NOWALLS_INVINCIBLE - no collisions at all. You can't die

### Building yourself
Use make tool to build the game yourself.
- To install make run one of the following commands:
	- `pacman -S make`
	- `sudo apt install make`
- To build: 
	- run `make` to build executable for your platform
	- run `make clean` to delete build file

### Running with Docker (why not 👾):
1. Pull the docker image: `docker pull chedanisv/ubuntu-snake:<version>`
2. Run the docker container: `docker run --rm -it chedanisv/ubuntu-snake:<version>`