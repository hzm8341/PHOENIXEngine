# build.sh

# set params
NDK_ROOT_LOCAL=/cygdrive/d/Android/ndk
ENGINE_ROOT_LOCAL=/cygdrive/e/DuoDuoYiShan/Phoenix/trunk/Phoenix
APPPLAY_MYAPP_BIN_ROOT_LOCAL=/cygdrive/e/DuoDuoYiShan/Phoenix/trunk/Bin
APPPLAY_MYAPP_DATAFROM=Data

if [ $NDK_ROOT"xyz" != "xyz" ]; then
	echo "use global definition of NDK_ROOT: $NDK_ROOT"
	NDK_ROOT_LOCAL=$NDK_ROOT
fi

if [ $PX2_ROOT"xyz" != "xyz" ]; then
	echo "use global definition of PX2_ROOT: $PX2_ROOT"
	ENGINE_ROOT_LOCAL=$PX2_ROOT
fi

if [ $APPPLAY_MYAPP_BIN_ROOT"xyz" != "xyz" ]; then
	echo "use global definition of APPPLAY_MYAPP_BIN_ROOT: $APPPLAY_MYAPP_BIN_ROOT"
	APPPLAY_MYAPP_BIN_ROOT_LOCAL=$APPPLAY_MYAPP_BIN_ROOT
fi

#project params
PROJECT_NAME=Block
PROJECT_ROOT=$ENGINE_ROOT_LOCAL/Projects/Client/$PROJECT_NAME

#appplay params
APPPLAY_MYAPP_ANDROID_ROOT=$ENGINE_ROOT_LOCAL/PX2AppPlayer/Proj.Android

#clear and make dir
if [ -d $APPPLAY_MYAPP_ANDROID_ROOT/assets ]; then
	rm -rf $APPPLAY_MYAPP_ANDROID_ROOT/assets
fi
mkdir $APPPLAY_MYAPP_ANDROID_ROOT/assets
mkdir $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data
mkdir $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/engine
mkdir $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/engine_mtls
mkdir $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/$PROJECT_NAME

# copy resources

# boost.lua boost.xml version.xml versionList.dat
cp -rf $APPPLAY_MYAPP_BIN_ROOT_LOCAL/$APPPLAY_MYAPP_DATAFROM/boost.xml $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data
# cp -rf $APPPLAY_MYAPP_BIN_ROOT_LOCAL/$APPPLAY_MYAPP_DATAFROM/version.xml $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data
# cp -rf $APPPLAY_MYAPP_BIN_ROOT_LOCAL/$APPPLAY_MYAPP_DATAFROM/versionList.dat $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data

# engine
for file in $APPPLAY_MYAPP_BIN_ROOT_LOCAL/$APPPLAY_MYAPP_DATAFROM/engine/*
do
if [ -d $file ]; then
cp -rf $file $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/engine
fi
if [ -f $file ]; then
cp $file $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/engine
fi
done

# engine_mtls
for file in $APPPLAY_MYAPP_BIN_ROOT_LOCAL/$APPPLAY_MYAPP_DATAFROM/engine_mtls/*
do
if [ -d $file ]; then
cp -rf $file $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/engine_mtls
fi
if [ -f $file ]; then
cp $file $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/engine_mtls
fi
done

# projects
for file in $APPPLAY_MYAPP_BIN_ROOT_LOCAL/$APPPLAY_MYAPP_DATAFROM/$PROJECT_NAME/*
do
if [ -d $file ]; then
cp -rf $file $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/$PROJECT_NAME
fi
if [ -f $file ]; then
cp $file $APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/$PROJECT_NAME
fi
done

chmod -R 777 $APPPLAY_MYAPP_ANDROID_ROOT/assets
chmod -R 777 $APPPLAY_MYAPP_ANDROID_ROOT/obj/local/armeabi

# build
echo "start build"

export NDK_MODULE_PATH=$ENGINE_ROOT_LOCAL\
:$ENGINE_ROOT_LOCAL/PX2Engine/\
:$ENGINE_ROOT_LOCAL/ThirdPartiesLibs/\
:$APPPLAY_MYAPP_ANDROID_ROOT/\
:$ENGINE_ROOT_LOCAL/Projects/\
:$ENGINE_ROOT_LOCAL/Projects/Client/\

$NDK_ROOT_LOCAL/ndk-build -C $APPPLAY_MYAPP_ANDROID_ROOT

echo "end build"

echo "begin copy so"

for file in $ENGINE_ROOT_LOCAL/ThirdPartiesLibs/vlc/libandroid/armeabi/*
do
if [ -d $file ]; then
cp -rf $file $APPPLAY_MYAPP_ANDROID_ROOT/libs/armeabi
fi
if [ -f $file ]; then
cp $file $APPPLAY_MYAPP_ANDROID_ROOT/libs/armeabi
fi
done

for file in $ENGINE_ROOT_LOCAL/ThirdPartiesLibs/Voice/BaiDu/speech/libs/armeabi/*
do
if [ -d $file ]; then
cp -rf $file $APPPLAY_MYAPP_ANDROID_ROOT/libs/armeabi
fi
if [ -f $file ]; then
cp $file $APPPLAY_MYAPP_ANDROID_ROOT/libs/armeabi
fi
done

for file in $ENGINE_ROOT_LOCAL/ThirdPartiesLibs/Voice/BaiDu/tts/libs/armeabi/*
do
if [ -d $file ]; then
cp -rf $file $APPPLAY_MYAPP_ANDROID_ROOT/libs/armeabi
fi
if [ -f $file ]; then
cp $file $APPPLAY_MYAPP_ANDROID_ROOT/libs/armeabi
fi
done

echo "end copy so"

#PROJECT_SO_FILENAME=$APPPLAY_MYAPP_ANDROID_ROOT
#PROJECT_SO_FILENAME=$APPPLAY_MYAPP_ANDROID_ROOT/"libs/armeabi/lib"$PROJECT_NAME".so"
#PROJECT_SO_FILEPATH_DST0=$APPPLAY_MYAPP_BIN_ROOT_LOCAL/$APPPLAY_MYAPP_DATAFROM/$PROJECT_NAME
#PROJECT_SO_FILEPATH_DST1=$APPPLAY_MYAPP_ANDROID_ROOT/assets/Data/

#cp $PROJECT_SO_FILENAME $PROJECT_SO_FILEPATH_DST0
#cp $PROJECT_SO_FILENAME $PROJECT_SO_FILEPATH_DST1