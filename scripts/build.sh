#!/bin/bash
#
# Copyright (C) 2014 Neil McGill
#
# This game is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This game is distributed in the hope that it will be fun,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this game; if not, write to the Free
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

. ./scripts/common.sh

case `uname` in
    *MING*|*MSYS*)
        for i in \
            $(which sdl2-config) \
            /mingw/bin/sdl2-config \
            /mingw64/bin/sdl2-config
        do
            if [ -x $i ]
            then
                SDL2_CONFIG=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which sdl2-config) \
            /opt/local/bin/sdl2-config \
            /usr/bin/sdl2-config
        do
            if [ -x $i ]
            then
                SDL2_CONFIG=$i
                break
            fi
        done
    ;;
esac

ubuntu_help_full()
{
    log_warn "For ubuntu, install:"
    log_warn "  apt install -y build-essential"
    log_warn "  apt install -y vim"
    log_warn "  apt install -y g++"
    log_warn "  apt install -y libsdl2-dev libsdl2-2.0-0"
    log_warn "  apt install -y libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0"
    log_warn "  apt install -y libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0"
    log_warn "  apt install -y libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0"
    log_warn "  apt install -y python3 python3-dev python3-pip"
    log_warn "  apt install -y git"
    log_warn "  apt install -y ssh"
    log_warn "  apt install -y xutils-dev"
}

sdl_help()
{
    log_warn "Is SDL2 installed? (not SDL1) If not:"

    case `uname` in
    *MING*|*MSYS*)
        log_warn "Installed already:"
        pacman -Ss | grep '^mingw64/' | grep SDL2 | sed 's/^mingw64.//g' | grep installed
        log_err "Cannot find SDL2"
        exit 1
        ;;
    *Darwin*)
        log_warn "Install MAC ports then install:"
        log_warn "  sudo port install libsdl2"
        log_warn "  sudo port install libsdl2_mixer"
        log_warn "  sudo port install libsdl2_ttf"
        ;;
    *)
        ubuntu_help_full
        ;;
    esac
}

SDL2_SCORE=0

if [ "$SDL2_CONFIG" != "" ]; then
    SDL2_INC_PATH=`$SDL2_CONFIG --cflags | sed -e 's/.*-I\([a-zA-Z\/_0-9:\.]*\) .*/\1/g' -e 's/\-.*//g'`

    if [[ "$SDL2_INC_PATH" != "" ]]; then
        find $SDL2_INC_PATH | grep -q SDL_mixer.h
        if [ $? -eq 0 ]; then
            SDL2_SCORE=`expr $SDL2_SCORE + 1`
            SDL2_MIXER=`find $SDL2_INC_PATH -name SDL_mixer.h`
        fi

        find $SDL2_INC_PATH | grep -q SDL_ttf.h
        if [ $? -eq 0 ]; then
            SDL2_SCORE=`expr $SDL2_SCORE + 1`
            SDL2_TTF=`find $SDL2_INC_PATH -name SDL_ttf.h`
        fi
    fi
fi

log_info "SDL2 config                : $SDL2_CONFIG"
log_info "SDL2 version               : "`$SDL2_CONFIG --version`
log_info "SDL2 include path          : $SDL2_INC_PATH"
log_info "SDL2 mixer.h               : $SDL2_MIXER"
log_info "SDL2 ttf.h                 : $SDL2_TTF"
#log_info "SDL2 found                 : $SDL2_SCORE"

if [[ $SDL2_SCORE != "2" ]]; then
    log_err "I need SDL2, SDL2 mixer and SDL2 ttf installed"
    sdl_help
    exit 1
fi

#
# Gives warings at runtime on MACOS
#
SDL_LIBS=`$SDL2_CONFIG --libs`
if [ $? -ne 0 ]
then
    log_err "Please install SDL2."
    sdl_help
    exit 1
fi

C_FLAGS=`$SDL2_CONFIG --cflags`
if [ $? -ne 0 ]
then
    log_err "Please install SDL2."
    sdl_help
    exit 1
fi

#
# -funwind-tables and -rdynamic for backtrace info on linux.
# But it seemed to help little.
#
LDLIBS="$SDL_LIBS"
LDLIBS="$LDLIBS -lSDL2_mixer"
LDLIBS="$LDLIBS -lSDL2_ttf"

case `uname` in
    *MING*|*MSYS*)
        for i in \
            $(which python3-config) \
            /mingw/bin/python3-config \
            /mingw64/bin/python3-config
        do
            if [ -x $i ]
            then
                Python3_CONFIG=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which python3-config) \
            /usr/local/bin/python3-config \
            /usr/bin/python3-config
        do
            if [ -x $i ]
            then
                Python3_CONFIG=$i
                break
            fi
        done
    ;;
esac

case `uname` in
    *MING*|*MSYS*)
        for i in \
            $(which python3) \
            /mingw/bin/python3 \
            /mingw64/bin/python3
        do
            if [ -x $i ]
            then
                Python3=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which python3) \
            /opt/local/bin/python3 \
            /usr/bin/python3
        do
            if [ -x $i ]
            then
                Python3=$i
                break
            fi
        done
    ;;
esac

case `uname` in
    *MING*|*MSYS*)
        for i in \
            $(which python-config) \
            /mingw/bin/python-config \
            /mingw64/bin/python-config
        do
            if [ -x $i ]
            then
                Python2_CONFIG=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which python-config) \
            /usr/local/bin/python-config \
            /usr/bin/python-config
        do
            if [ -x $i ]
            then
                Python2_CONFIG=$i
                break
            fi
        done
    ;;
esac

case `uname` in
    *MING*|*MSYS*)
        for i in \
            $(which python) \
            /mingw/bin/python \
            /mingw64/bin/python
        do
            if [ -x $i ]
            then
                Python2=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which python) \
            /usr/local/bin/python \
            /usr/bin/python
        do
            if [ -x $i ]
            then
                Python2=$i
                break
            fi
        done
    ;;
esac

python_help()
{
    log_warn "Is python3 installed ?"

    case `uname` in
    *MING*|*MSYS*)
        log_warn "Installed already:"
        pacman -Ss | grep '^mingw64/' | grep python3 | sed 's/^mingw64.//g' | grep installed
        log_err "Cannot find python3"
        exit 1
        ;;
    *Darwin*)
        log_warn "Install MAC ports then install:"
        log_warn "   sudo port install python3*"
        ;;
    *)
        ubuntu_help_full
        ;;
    esac
}

Python2_SCORE=0
Python3_SCORE=0

if [ "$Python2_CONFIG" != "" ]; then
    Python2_INC_PATH=`$Python2_CONFIG --cflags | sed -e 's/.*-I\([a-zA-Z\/_0-9:\.]*\) .*/\1/g' -e 's/\-.*//g'`

    if [[ "$Python2_INC_PATH" != "" ]]; then
        find $Python2_INC_PATH | grep -q Python.h
        if [ $? -eq 0 ]; then
            Python2_SCORE=`expr $Python2_SCORE + 1`
        fi
    fi
fi

if [ "$Python3_CONFIG" != "" ]; then
    Python3_INC_PATH=`$Python3_CONFIG --cflags | sed -e 's/.*-I\([a-zA-Z\/_0-9:\.]*\) .*/\1/g' -e 's/\-.*//g'`

    if [[ "$Python3_INC_PATH" != "" ]]; then
        find $Python3_INC_PATH | grep -q Python.h
        if [ $? -eq 0 ]; then
            Python3_SCORE=`expr $Python3_SCORE + 1`
        fi
    fi
fi

if [ "$Python2_CONFIG" != "" ]; then
    log_info "Default Python             : $Python2"
    log_info "Default Python config      : $Python2_CONFIG"
    log_info "Default Python exec        : "`$Python2_CONFIG --exec-prefix`
    log_info "Default Python include path: $Python2_INC_PATH"
    #log_info "Default Python found       : $Python2_SCORE"
fi

if [[ "$Python3_CONFIG" != "" ]]; then
    log_info "Python3                    : $Python3"
    log_info "Python3 config             : $Python3_CONFIG"
    log_info "Python3 exec               : "`$Python3_CONFIG --exec-prefix`
    log_info "Python3 include path       : $Python3_INC_PATH"
    #log_info "Python3 found              : $Python3_SCORE"
fi

USE_Python2=0
USE_Python3=0

if [[ $Python2_SCORE = "0" ]]; then
    if [[ $Python3_SCORE = "0" ]]; then
        log_err "I need Python3"
        python_help
        exit 1
    else
        Python_CONFIG=$Python3_CONFIG
        Python=$Python3
        USE_Python3=1
    fi
elif [[ $Python3_SCORE = "0" ]]; then
    if [[ $Python2_SCORE = "0" ]]; then
        log_err "I need Python3"
        python_help
        exit 1
    else
#        Python_CONFIG=$Python2_CONFIG
#        Python=$Python2
#        USE_Python2=1
        log_err "I need Python3"
        python_help
        exit 1
    fi
else
    if [[ $Python3_SCORE -ge $Python2_SCORE ]]; then
#        log_info "Prefer Python3"
        Python_CONFIG=$Python3_CONFIG
        Python=$Python3
        USE_Python3=1
    else
        log_err "I need Python3"
        python_help
        exit 1
#        log_info "Prefer Python2"
#        Python_CONFIG=$Python2_CONFIG
#        Python=$Python2
#        USE_Python2=1
    fi
fi

PYTHONVERSION=$($Python --version | sed -e 's/Python //g' -e 's/\.[0-9]*$//g')
echo "PYTHONVERSION=$PYTHONVERSION" > windows/python.version.sh

log_info "Python lib version         : $PYTHONVERSION"

cat windows/windows.xml.tmpl | \
    sed -e "s/PYTHONVERSION/$PYTHONVERSION/g" \
        -e "s/GAME_VERSION/$VERSION/g" \
    > windows/windows.xml

/bin/rm -f data/zorbash-hiscore.txt data/zorbash-config.txt

#
# Make the makefile
#
cd src

rm -f Makefile
cat Makefile.base | sed '/DO NOT DELETE/,$d' > Makefile.tmp
mv Makefile.tmp Makefile

case `uname` in
    *MING*|*MSYS*)
        ../makedepend *.cpp -p .o/ 2>/dev/null

        if [ $? -ne 0 ]; then
            ../third-party/makedepend *.cpp -p .o/ 2>/dev/null
        fi
        ;;
    *)
        makedepend *.cpp -p .o/ 2>/dev/null
        ;;
esac

if [ $? -ne 0 ]; then

    log_warn "Is makedepend installed? If not:"
    log_warn "  For ubuntu do: sudo apt-get install xutils-dev"
    log_warn "  For MAC    do: sudo port install makedepend"
    log_warn "  For MingW  do: look in third-party for Win32 binary"

    case `uname` in
        *MING*|*MSYS*)
            echo
            log_warn "If you still can't find it, I have the source in third-party"
            log_warn "  cd third-party"
            log_warn "  tar xvf makedepend-1.0.5.tar.gz"
            log_warn "  cd makedepend-1.0.5"
            log_warn "  ./configure"
            ;;
    esac

    log_warn "Hit enter to continue; I'll ignore this error."
    log_warn "It's not essential. Rebuilds will be slower is all."
    read dummy

    makedepend *.cpp -p .o/ 2>/dev/null
fi

cd ..

#
# 3.8 added --embed for -lpython
#
Python_LIBS=`$Python_CONFIG --ldflags --embed 2>/dev/null`
if [ $? -ne 0 ]; then
    Python_LIBS=`$Python_CONFIG --ldflags`
    if [ $? -ne 0 ]; then
        log_err "Please install Python 3. $Python_CONFIG failed."
        exit 1
    fi
fi

#
# Filter some junk out of the python config that can cause link errors
#
C_FLAGS="$C_FLAGS `$Python_CONFIG --cflags | \
           tr ' ' '\n' | \
           grep -v specs                | \
           grep -v debug-prefix         | \
           grep -v O3                   | \
           grep -v O2                   | \
           grep -v Os                   | \
           grep -v wrapv                | \
           grep -v strict-proto         | \
           grep -v no-strict-aliasing   | \
           tr '\n' ' '                  | \
           sed 's/\-arch i386/ /g'      \
           `"
#
# -funwind-tables and -rdynamic for backtrace info on linux.
# But it seemed to help little.
#
LDLIBS="$LDLIBS $Python_LIBS"

#
# for backtraces, but it doesn't help much
#
case `uname` in
    *MSYS*)
        log_err "compile for ming64, not msys"
        exit 1
        ;;
    *MING*)
        PATH=/mingw64/bin:$PATH

        EXE=".exe"
        # gcc only
        C_FLAGS="$C_FLAGS -mwin32 "
        C_FLAGS+="$C_FLAGS -I/mingw64/x86_64-w64-mingw32/include "

        #
        # Does not seem to work
        #
        # https://stackoverflow.com/questions/156510/increase-stack-size-on-windows-gcc
        # C_FLAGS+="$LDLIBS -Wl,--stack,128777216 "
        #

        LDLIBS="$LDLIBS -L/mingw64/x86_64-w64-mingw32/lib/"
        LDLIBS=`echo $LDLIBS | sed -e 's/-lmingw32 //g'`
        LDLIBS="$LDLIBS -funwind-tables"
        #LDLIBS="$LDLIBS -static"
        LDLIBS="$LDLIBS -static-libstdc++"
        LDLIBS="$LDLIBS -static-libgcc"
        LDLIBS="$LDLIBS -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic"
        LDLIBS="$LDLIBS -lopengl32"
        LDLIBS="$LDLIBS -lpthread"
        LDLIBS="$LDLIBS /mingw64/lib/libSDL2_mixer.a"
        LDLIBS="$LDLIBS /mingw64/lib/libSDL2_ttf.a"

        #
        # Except it does not work and does not generate pdb files for clang
        #
        #C_FLAGS+="-gcodeview"
        #C_FLAGS=`echo $C_FLAGS | sed -e 's/-mwin32 //g'`
        # And use this later
        # echo "CC=clang++.exe # AUTOGEN" >> .Makefile

        #
        # For symbol decode StackTrace that doesn't really work without
        # visual studio. sigh
        #
        LDLIBS="$LDLIBS -L/mingw64/lib/binutils -lbfd -lintl -ldbghelp -liberty -lz"
        ;;
    *Darwin*)
        EXE=""
        LDLIBS="$LDLIBS -funwind-tables"
        LDLIBS="$LDLIBS -rdynamic"
        LDLIBS="$LDLIBS -Wl,-framework,Opengl"
        DSYM="dsymutil ../zorbash"
        #
        # Can't get this to work
        #
        if [[ $OPT_DEV2 != "" ]]; then
            C_FLAGS+=" -fsanitize=address -fno-omit-frame-pointer"
            LDFLAGS+=" -fsanitize=address"
        fi
        ;;
    *)
        EXE=""
        LDLIBS="$LDLIBS -funwind-tables"
        LDLIBS="$LDLIBS -lGL"
        if [[ $OPT_DEV2 != "" ]]; then
            C_FLAGS+=" -fsanitize=address -fno-omit-frame-pointer"
            LDFLAGS+=" -fsanitize=address"
        fi
        ;;
esac

GCC_WARN=""

#
# Better to leave off for production
#
WERROR=""
if [[ $OPT_DEV1 != "" ]]; then
    WERROR="-Werror"
fi

PYTHONPATH=$($Python -c "import os, sys; print(os.pathsep.join(x for x in sys.path if x))")
C_FLAGS="$C_FLAGS -DVERSION=\\\"$VERSION\\\""
C_FLAGS="$C_FLAGS -DPYTHONVERSION=\\\"$PYTHONVERSION\\\""

log_info "PYTHONVERSION              : $PYTHONVERSION"
log_info "PYTHONPATH                 : $PYTHONPATH"
log_info "VERSION (game)             : $VERSION"

cd src

if [[ $OPT_DEV1 != "" ]]; then
    echo "COMPILER_FLAGS=$WERROR $C_FLAGS -g -ggdb3 # AUTOGEN" > .Makefile
else
    echo "COMPILER_FLAGS=$WERROR $C_FLAGS -g -ggdb3 -O3 # AUTOGEN" > .Makefile
fi

echo "    " >> .Makefile
echo "CLANG_COMPILER_WARNINGS=-Wall $GCC_WARN -std=c++1z -stdlib=libc++ # AUTOGEN" >> .Makefile
echo "    " >> .Makefile
echo "LDFLAGS=$LDFLAGS" >> .Makefile

if [[ $OPT_DEV2 != "" ]]; then
    GCC_STACK_CHECK="-fstack-check -fstack-protector-all -D_FORTIFY_SOURCE=2"
    GCC_STACK_CHECK="-fstack-check -fstack-protector-all"
else
    GCC_STACK_CHECK=
fi

# c++2a for bitfield initialization in classes
echo "GCC_COMPILER_WARNINGS=-x c++ -Wall $GCC_WARN -std=c++2a -ffast-math $GCC_STACK_CHECK # AUTOGEN" >> .Makefile
# std++17 is not yet supported on my mac, henze c++1z
`g++ --version >/dev/null 2>/dev/null`
if [ $? -eq 0 ]
then
    echo "COMPILER_WARNINGS=\$(CLANG_COMPILER_WARNINGS) # AUTOGEN" >> .Makefile
    echo "COMPILER_WARNINGS=\$(GCC_COMPILER_WARNINGS) # AUTOGEN" >> .Makefile
    echo "# CC=clang++ # AUTOGEN" >> .Makefile
    echo "CC=g++ # AUTOGEN" >> .Makefile
    # -mp- is the mac ports version
    #echo "CC=/opt/local/bin/g++-mp-6 # AUTOGEN" >> .Makefile
else
    `clang++ --version >/dev/null 2>/dev/null`
    if [ $? -eq 0 ]
    then
        echo "COMPILER_WARNINGS=\$(GCC_COMPILER_WARNINGS) # AUTOGEN" >> .Makefile
        echo "COMPILER_WARNINGS=\$(CLANG_COMPILER_WARNINGS) # AUTOGEN" >> .Makefile
        echo "CC=clang++ # AUTOGEN" >> .Makefile
        echo "# CC=g++ # AUTOGEN" >> .Makefile
    fi
fi

case `uname` in
    *MING*)
        echo "CC=/mingw64/bin/x86_64-w64-mingw32-g++.exe # AUTOGEN" >> .Makefile
        #
        # To resolve WinMain, add these at the end again
        #
        LDLIBS="$LDLIBS -lmingw32 -lSDL2main -lSDL2 -mwindows /mingw64/lib/libSDL2main.a -L/mingw64/lib -lSDL2main -lSDL2"
        # clang
    ;;
esac

echo "    " >> .Makefile
echo "EXE=$EXE # AUTOGEN" >> .Makefile
echo "DSYM=$DSYM # AUTOGEN" >> .Makefile
echo "LDLIBS=$LDLIBS # AUTOGEN" >> .Makefile
echo "CFLAGS=\$(COMPILER_FLAGS) \$(COMPILER_WARNINGS) # AUTOGEN" >> .Makefile

cat Makefile | grep -v AUTOGEN | grep -v "^    $" >> .Makefile

if [ -s .Makefile ]
then
    mv .Makefile Makefile
    if [ ! -f Makefile ]
    then
        log_err "No makefile?!"
        exit 1
    fi
else
    log_err "Makefile create fail?!"
    exit 1
fi

log_info "Cleaning"
make clobber | sed 's/^/  /g'

CORES=""

case `uname` in
    *Darwin*)
        CORES=`/usr/sbin/system_profiler -detailLevel full SPHardwareDataType  | grep Cores | sed 's/.*: //g'`
    ;;
    *inux*)
        CORES=`cat /proc/cpuinfo | grep "cpu cores" | wc -l`
    ;;
    MSYS*)
        CORES=`cat /proc/cpuinfo | grep "cpu cores" | wc -l`
    ;;
esac

if [ "$CORES" != "" ]
then
    log_info "Compiling ($CORES cpus)"

    CORES="-j $CORES"
else
    log_info "Compiling"
fi

cd ..
echo make $CORES $* all
make $CORES $* all

if [ $? -eq 0 ]
then
    case `uname` in
        *MING*)
            log_info "Run:"
            echo "  export PYTHONPATH=/mingw64/lib/python${PYTHONVERSION}/:/mingw64/lib/python${PYTHONVERSION}/lib-dynload:/mingw64/lib/python${PYTHONVERSION}/site-packages"
            echo "  export PYTHONHOME=/mingw64/bin"
            echo "  ./zorbash.exe"
            ;;
        *)
            log_info "Run:"
            echo "  ./zorbash"
            ;;
    esac

    rm -f Makefile.bak
else
    cd ..
    log_die "Build failed"
    sdl_help
    exit 1
fi

cd ..
exit 0