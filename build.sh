do_clean=false
do_run=false
do_tests=false

targetName=""

while [[ $# -gt 0 ]]; do
    case $1 in
        -c)
            do_clean=true
            shift
            ;;
        -r)
            do_run=true
            shift
            ;;
        -test)
            do_tests=true
            shift
            ;;
        -target)
            shift
            if [[ $# -gt 0 ]]; then
                targetName="$1"
                shift
            else
                echo "Error: -target requires a target name argument."
                exit 1
            fi
            ;;
        *)
            echo "Unknown option: $1"
            exit 1
            ;;
    esac
done

if $do_clean; then
    echo "Cleaning entire build directory..."
    rm -rf build
fi

echo "Configuring cmake..."
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
if [ $? -ne 0 ]; then
    echo "cmake generation failed."
    exit 1
fi

echo "Building the project..."
if [[ -z "$targetName" ]]; then
    cmake --build build -j8 -v
else
    cmake --build build --target $targetName -j8 -v
fi
if [ $? -ne 0 ]; then
    echo "cmake build failed."
    exit 1
fi
echo "Build completed successfully."

if $do_run; then
    echo "Running the application..."
    if [ -f build/bin/test_bed ]; then
        (cd build/bin && ./test_bed)
        if [ $? -ne 0 ]; then
            echo "Application run failed."
            exit 1
        fi
    else
        echo "Executable not found: build/bin/test_bed"
        exit 1
    fi
fi

if $do_tests; then
    echo "Running tests..."
    (cd build && ctest --output-on-failure)
fi
