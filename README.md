# IRC_Server
IRC Webserver based RFC1459


## docker 명령어 정리
### docker image build
```bash
docker build --rm -t irc_server .
```

### docker image run
```bash
docker run -d -p 3000:3000 irc_server
```
d를 붙이면 컨테이너를 백그라운드로 실행한다.


### docker container stop
```bash
docker stop $(container name)
```

### docker container restart
```bash
docker restart $(container name)
```

### docker 실행중인거 삭제 방법
```bash
docker rm -f $(docker ps -qa)
```

`docker ps -qa`는 현재 실행하는 모든 컨테이너의 id를 출력

### docker image 전체 삭제
```bash
docker rmi -f $(docker ps -qa)
```

### docker dangling image 전체 삭제 (none 뜨는 이미지)
```bash
docker image prune
```

### docker image 확인
```bash
docker images
```