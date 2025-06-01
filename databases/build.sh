#!/usr/bin/env bash
#
# build.sh – compile any single‐source project that uses sqlite3.amalgamation
#
# Usage:
#   ./build.sh <source-filename>
#   ./build.sh (will prompt for filename)
#
# Assumptions:
#   1) You have a folder “sqlite/” in the same directory, containing:
#        sqlite3.c
#        sqlite3.h
#      (and maybe sqlite3ext.h if you need it)
#
#   2) If sqlite/sqlite3.o does not exist, this script will build it.
#      Otherwise, it just reuses the existing sqlite3.o.
#
#   3) All generated .o and .exe files live in this same directory.
#
#
# 1) Figure out what source file to compile:
if [ -z "$1" ]; then
  read -p "Enter the C source filename (with or without .c): " INPUT
else
  INPUT="$1"
fi

# 2) Normalize: if user gave “foo.c” or “foo”, turn it into SRC="foo.c"
if [[ "$INPUT" == *.c ]]; then
  SRC="$INPUT"
else
  SRC="$INPUT.c"
fi

# 3) Check that the source actually exists:
if [ ! -f "$SRC" ]; then
  echo "Error: source file “$SRC” not found."
  exit 1
fi

# 4) Derive base name and output names:
BASENAME="$(basename "$SRC" .c)"    # e.g. “members” from “members.c”
OBJ="$BASENAME.o"                   # e.g. members.o
TARGET="$BASENAME.exe"              # e.g. members.exe

# 5) Path to the SQLite amalgamation:
SQLITE_SRC_DIR="sqlite"
SQLITE_SRC="$SQLITE_SRC_DIR/sqlite3.c"
SQLITE_HDR="$SQLITE_SRC_DIR/sqlite3.h"
SQLITE_OBJ="$SQLITE_SRC_DIR/sqlite3.o"

# 6) Make sure sqlite3 source & header exist:
if [ ! -f "$SQLITE_SRC" ] || [ ! -f "$SQLITE_HDR" ]; then
  echo "Error: Cannot find sqlite3.c / sqlite3.h in “$SQLITE_SRC_DIR/”."
  exit 1
fi

# 7) Build sqlite3.o if needed:
if [ ! -f "$SQLITE_OBJ" ]; then
  echo "sqlite3.o not found. Building sqlite3.o..."
  gcc -O2 -g -fPIC -I"$SQLITE_SRC_DIR" -c "$SQLITE_SRC" -o "$SQLITE_OBJ"
  if [ $? -ne 0 ]; then
    echo "Error: failed to compile $SQLITE_SRC."
    exit 1
  fi
else
  echo "Using existing $SQLITE_OBJ"
fi

# 8) Compile your .c → .o
echo "Compiling $SRC → $OBJ ..."
gcc -O2 -g -I"$SQLITE_SRC_DIR" -c "$SRC" -o "$OBJ"
if [ $? -ne 0 ]; then
  echo "Error: failed to compile $SRC."
  exit 1
fi

# 9) Link your .o + sqlite3.o → .exe
echo "Linking $OBJ + $SQLITE_OBJ → $TARGET ..."
gcc "$OBJ" "$SQLITE_OBJ" -o "$TARGET"
if [ $? -ne 0 ]; then
  echo "Error: linking failed."
  exit 1
fi

echo "Build complete: ./$TARGET"
exit 0
