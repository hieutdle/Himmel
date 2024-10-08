FROM mcr.microsoft.com/devcontainers/base:noble

RUN apt-get update --fix-missing \
    && apt-get -y --no-install-recommends install ca-certificates curl wget gnupg netcat-openbsd make \
    && apt-get update