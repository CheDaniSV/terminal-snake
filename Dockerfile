FROM ubuntu:24.04

RUN apt-get update && apt-get install -y g++ g++-mingw-w64-x86-64 make

COPY . /app

WORKDIR /app

CMD ["bash", "-c", "make && ./snake"]