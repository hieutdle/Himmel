#!/bin/bash

# Start the Docker service
sudo systemctl start docker

# Update the permissions for Docker socket
sudo chmod 666 /var/run/docker.sock