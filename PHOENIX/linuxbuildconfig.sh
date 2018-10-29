# install opengl
sudo apt-get install freeglut3-dev

# cp fmod
sudo cp -fr ./ThirdPartiesLibs/FMOD /usr/local/lib/
sudo chmod 777 /usr/local/lib/FMOD

# for x86
#sudo cp -f /usr/local/lib/FMOD/linux/lib/x86/libfmod.so.9 /usr/local/lib/
# for x64
sudo cp -f /usr/local/lib/FMOD/linux/lib/x86_64/libfmod.so.9 /usr/local/lib/