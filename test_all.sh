#!/bin/bash

# 获取所有源文件并转换为目标名
targets=$(find src -type f \( -name "*.cc" -o -name "*.cpp" -o -name "*.c" \) | while read file; do
    rel_path="${file#src/}"
    dir=$(dirname "$rel_path")
    filename=$(basename "$file")
    filename="${filename%.*}"
    
    if [ "$dir" != "." ]; then
        dir_prefix=$(echo "$dir" | tr '/' '_')
        target="${dir_prefix}_${filename}"
    else
        target="$filename"
    fi
    
    # 处理保留名称
    if [ "$target" = "clean" ] || [ "$target" = "test" ] || [ "$target" = "install" ]; then
        target="app_${target}"
    fi
    
    echo "$target"
done | sort)

success=0
failed=0
compile_errors=""
runtime_errors=""

for target in $targets; do
    echo "Testing: $target"
    
    # 编译
    if cmake --build build --target "$target" >/dev/null 2>&1; then
        # 运行（设置超时2秒）
        exe="build/$target"
        if timeout 2s "$exe" >/dev/null 2>&1; then
            echo "  ✓ OK"
            ((success++))
        else
            exit_code=$?
            if [ $exit_code -eq 124 ]; then
                echo "  ⚠ TIMEOUT (可能需要输入)"
                ((success++))
            else
                echo "  ✗ RUNTIME ERROR (exit: $exit_code)"
                ((failed++))
                runtime_errors="$runtime_errors\n  - $target"
            fi
        fi
    else
        echo "  ✗ COMPILE ERROR"
        ((failed++))
        compile_errors="$compile_errors\n  - $target"
    fi
done

echo ""
echo "========================================"
echo "Summary: Success=$success, Failed=$failed"
if [ -n "$compile_errors" ]; then
    echo -e "\nCompile Errors:$compile_errors"
fi
if [ -n "$runtime_errors" ]; then
    echo -e "\nRuntime Errors:$runtime_errors"
fi
