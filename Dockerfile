#image
FROM debian:bookworm

# command directory
WORKDIR /usr/src/irc_server

RUN apt-get -qq update\
    && apt-get -qq install -y g++ make\
    && apt-get clean

COPY . /usr/src/irc_server/

RUN chmod +x start.sh

CMD [ "./start.sh" ]