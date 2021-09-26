#!/bin/bash

if [ -z $1 ]
then
  echo "you forgot to enter command_name"
  exit 1;
fi

if [ -z $2 ]
then
  echo "you forgot to enter user_name"
  exit 1;
fi

mkdir build
cd build
cmake ../
make
cp ./c++/wallparer_cpp /usr/local/bin/$1
mkdir -p /home/$2/.wallparers/pictures
chown -R $2:$2 /home/$2/.wallparers