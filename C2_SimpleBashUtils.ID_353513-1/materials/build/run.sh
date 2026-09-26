#!/bin/bash
cd ../..
docker build . -t school21/miniverter:1.0 -f materials/build/Dockerfile && \
docker run --rm school21/miniverter:1.0

