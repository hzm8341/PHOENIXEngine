# install opengl
apt-get install freeglut3-dev

# cp fmod
cp -fr ./ThirdPartiesLibs/FMOD /usr/local/lib/
chmod 777 /usr/local/lib/FMOD

# for x86
cp -f /usr/local/lib/FMOD/linux/lib/x86/libfmod.so.9 /usr/local/lib/
# for x64
#cp -f /usr/local/lib/FMOD/linux/lib/x86_64/libfmod.so.9 /usr/local/lib/