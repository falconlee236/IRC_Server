# IRC_Server
IRC Webserver based RFC1459


### docker 접속 방법
```bash
docker build --rm -t irc_server .
docker run -p 3000:3000 irc_server
```
### docker 실행중인거 삭제 방법
```bash
docker rm -f $(docker ps -qa)
```

`docker ps -qa`는 현재 실행하는 모든 컨테이너의 id를 출력