## 🐍 Snake game in terminal
<p>
	<!-- <img alt="Build and release workflow status" src="https://github.com/CheDaniSV/terminal-snake/actions/workflows/build-and-release.yml/badge.svg"> -->
	<!-- <img alt="Docker deploy workflow status" src="https://github.com/CheDaniSV/terminal-snake/actions/workflows/docker-deploy.yml/badge.svg"> -->
	<img alt="Commits since last release"  src="https://img.shields.io/github/commits-since/CheDaniSV/terminal-snake/latest">
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/CheDaniSV/terminal-snake">
</p>

- ANSI terminals **only**
- Supports Windows & Linux
- Has 4 gamemodes:
	- CLASSIC - snake can't collide with the walls or itself 
	- CLASSIC_SPEEDUP - higher the score faster the game
	- NOWALLS - no collisions with the walls
	- NOWALLS_INVINCIBLE - no collisions at all. You can't die

### Build yourself
- Run one of the following commands to install dependencies:
	- `pacman -S make base-devel`
	- `sudo apt install make build-essential`
	- or use other package manager
- Build:
	- run `make` to build executable for your platform

### Run in Docker 
- `docker pull chedanisv/terminal-snake:latest`
- `docker run --rm -it chedanisv/terminal-snake`