FROM alpine:latest

COPY ./snake /app/snake

WORKDIR /app

CMD ["sh", "-c", "./snake"]