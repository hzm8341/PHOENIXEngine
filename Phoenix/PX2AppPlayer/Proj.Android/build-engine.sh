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

# copy resources

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

chmod -R 777 $APPPLAY_MYAPP_ANDROID_ROOT/assets

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