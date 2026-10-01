FROM ubuntu:latest AS build

RUN apt-get update && apt-get install -y build-essential \
					 libsidplayfp-dev \
					 libgme-dev \
					 libmp3lame-dev \
					 libshout-dev \
					 pkg-config

WORKDIR /app

COPY ./src .

RUN make

CMD [ "/app/vgmstream" ]
