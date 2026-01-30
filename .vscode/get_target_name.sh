#!/bin/bash
# 根据源文件路径计算 CMake 目标名称

FILE_PATH="$1"
WORKSPACE="$2"

# 获取相对于 src 目录的路径
SRC_DIR="$WORKSPACE/src"
REL_PATH=$(realpath --relative-to="$SRC_DIR" "$FILE_PATH")

# 获取目录和文件名
DIR=$(dirname "$REL_PATH")
FILENAME=$(basename "$FILE_PATH")
FILENAME="${FILENAME%.*}"  # 移除扩展名（支持 .cc 和 .cpp）

# 如果在子目录中，添加目录前缀
if [ "$DIR" != "." ]; then
    # 将 / 替换为 _
    DIR_PREFIX=$(echo "$DIR" | tr '/' '_')
    TARGET="${DIR_PREFIX}_${FILENAME}"
else
    TARGET="$FILENAME"
fi

# 避免与 CMake 保留名称冲突
if [ "$TARGET" = "clean" ] || [ "$TARGET" = "test" ] || [ "$TARGET" = "install" ]; then
    TARGET="app_${TARGET}"
fi

echo "$TARGET"

